#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "../crc32/crc32_func.h"

#define MAX_PASSWORD_LENGTH 10
#define NUM_OF_THREADS 16

#define false 0
#define true 1
#define bool char

void initPossiblePassword(char* password, int maxLen) {
     for (int i = 0; i < maxLen; ++i) {
        password[i] = 32;
    }
}

int checkPasswordArray(char* password, int maxLen) {
    for (int i = maxLen - 1; i > -1; --i) {
        if (password[i] != 32) {
            return 0;
        }
    }

    return 1;
}

void incPassword(unsigned char* password, int maxLen) {
    password[maxLen - 1] += 1;

    for (int i = maxLen - 1; i > -1; --i) {
        if (password[i] == 127) {
            password[i] = 32;

            if (i > 0) {
                password[i - 1] += 1;
            }
        } else {
            break;
        }
    } 
}

struct password_thread {
    pthread_mutex_t* possiblePassword_mutex;
    pthread_mutex_t* stdout_mutex;
    pthread_mutex_t* passwordFound_mutex;

    bool* passwordFound;
    char* foundedPassword;

    char* possiblePassword;
    int* maxPasswordLength;

    unsigned long* searchedSum;
};

void* password_thread(void* threadArgs) {
    struct password_thread* args = threadArgs;
    
    char localPossiblePassword[MAX_PASSWORD_LENGTH];
    int localMaxLen;

    while (true) {
        pthread_mutex_lock(args->passwordFound_mutex);

        if (*(args->passwordFound)) {
            pthread_mutex_unlock(args->passwordFound_mutex);
            return NULL;
        }

        pthread_mutex_unlock(args->passwordFound_mutex);

        pthread_mutex_lock(args->possiblePassword_mutex);

        if (!checkPasswordArray(args->possiblePassword, *(args->maxPasswordLength))) {
            strcpy(localPossiblePassword, args->possiblePassword);

            localMaxLen = *(args->maxPasswordLength);

            incPassword(args->possiblePassword, *(args->maxPasswordLength));
        } else {
            *(args->maxPasswordLength) += 1;

            if (*(args->maxPasswordLength) == MAX_PASSWORD_LENGTH) {
                return NULL;
            }

            initPossiblePassword(args->possiblePassword, *(args->maxPasswordLength));

            strcpy(localPossiblePassword, args->possiblePassword);

            localMaxLen = *(args->maxPasswordLength);

            incPassword(args->possiblePassword, *(args->maxPasswordLength));
        }

        pthread_mutex_unlock(args->possiblePassword_mutex);

//        pthread_mutex_lock(args->stdout_mutex);

//        printf("\r%d %s", localMaxLen, localPossiblePassword);

//        pthread_mutex_unlock(args->stdout_mutex);

        unsigned long sum = compute_crc(localPossiblePassword);

        if (sum == *(args->searchedSum)) {
            break;
        }
    }

    pthread_mutex_lock(args->passwordFound_mutex);
    
    *(args->passwordFound) = true;
    strcpy(args->foundedPassword, localPossiblePassword);

    pthread_mutex_unlock(args->passwordFound_mutex);

    return NULL;
}

int main() {
    unsigned long password;

    scanf("%lx", &password);

    char possiblePassword[MAX_PASSWORD_LENGTH + 1] = {0};
    int maxLength = 0;

    char passwordFound = false;
    char foundedPassword[MAX_PASSWORD_LENGTH];

    pthread_mutex_t possiblePassword_mutex,
                    stdout_mutex,
                    password_found_mutex;

    pthread_mutex_init(&possiblePassword_mutex, NULL);
    pthread_mutex_init(&stdout_mutex, NULL);
    pthread_mutex_init(&password_found_mutex, NULL);

    pthread_t threads[NUM_OF_THREADS];

    struct password_thread passwordThreads[NUM_OF_THREADS];

    for (int i = 0; i < NUM_OF_THREADS; ++i) {
        passwordThreads[i].possiblePassword_mutex = &possiblePassword_mutex;
        passwordThreads[i].stdout_mutex = &stdout_mutex;
        passwordThreads[i].passwordFound_mutex = &password_found_mutex;

        passwordThreads[i].possiblePassword = possiblePassword;
        passwordThreads[i].maxPasswordLength = &maxLength;

        passwordThreads[i].passwordFound = &passwordFound;
        passwordThreads[i].foundedPassword = foundedPassword;
        
        passwordThreads[i].searchedSum = &password;
    }

    for (int i = 0; i < NUM_OF_THREADS; ++i) {
        pthread_create(&(threads[i]), NULL, password_thread, &(passwordThreads[i]));
    }

    while (!passwordFound) {};

    printf("\n%s\n", foundedPassword);

    return 0;
}
