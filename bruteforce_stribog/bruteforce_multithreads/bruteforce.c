#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "../bruteforce_funcs/bruteforce_funcs.h"

#include "gost_3411_2012_calc.h"

#define MAX_PASSWORD_LENGTH 10

#ifndef NUM_OF_THREADS
    #define NUM_OF_THREADS 2
#endif

#define false 0
#define true 1
#define bool char

#ifdef mutex

#define locker              pthread_mutex_t
#define locker_lock         pthread_mutex_lock
#define locker_unlock       pthread_mutex_unlock
#define locker_init         pthread_mutex_init

#else

#define locker              pthread_spinlock_t
#define locker_lock         pthread_spin_lock
#define locker_unlock       pthread_spin_unlock
#define locker_init         pthread_spin_init

#endif

#ifndef testNum 
    #define testNum 3
#endif

struct password_thread {
    int threadId;
    locker* possiblePassword_mutex;
    locker* stdout_mutex;
    locker* passwordFound_mutex;

    bool* passwordFound;
    char* foundedPassword;

    char* possiblePassword;
    int* maxPasswordLength;

    vect* searchedSum;
};

void incPasswordButFirs(unsigned char* password, int maxLen) {
    password[maxLen - 1] += 1;

    for (int i = maxLen - 1; i > maxLen - testNum; --i) {
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

int checkPasswordArray5(char* password, int maxLen) {
    for (int i = maxLen - 1; i > maxLen - testNum; --i) {
        if (password[i] != 32) {
            return 0;
        }
    }

    return 1;
}

TGOSTHashContext* compute_crc(char* str, TGOSTHashContext* CTX) {
    GOSTHashInit(CTX);
    GOSTHashUpdate(CTX, str, strlen(str));
    GOSTHashFinal(CTX);
    
    return CTX;
}

char* check5Digits(unsigned char* basePassword, uint8_t* searchedSum, struct password_thread* thread) {
    int maxPasswordLength = strlen(basePassword);
    
    TGOSTHashContext CTX;

    do {
        TGOSTHashContext* sum = compute_crc(basePassword, &CTX);
        
        bool test = false;
        
        for(int i = 0; i < 64; i++) {
            test = sum->hash[i] == searchedSum[i];
            if (!test) {
                break;
            }
        }

        if (test) {
            return basePassword;
        }
        
        
        locker_lock(thread->passwordFound_mutex);

        if (*(thread->passwordFound)) {
            locker_unlock(thread->passwordFound_mutex);
            return NULL;
        }

        locker_unlock(thread->passwordFound_mutex);

        if (maxPasswordLength > (testNum - 1)) {
            incPasswordButFirs(basePassword, maxPasswordLength);

            if (checkPasswordArray5(basePassword, maxPasswordLength)) {
                break;
            }
        } else {
            incPassword(basePassword, maxPasswordLength);

            if (checkPasswordArray(basePassword, maxPasswordLength)) {
                break;
            }  
        }
    } while (true);

    return NULL;
}

char* inc5password(char* password, int maxLen) {
    password[maxLen - testNum] += 1;

    for (int i = maxLen - testNum; i > -1; --i) {
        if (password[i] == 127) {
            password[i] = 32;

            if (i > 0) {
                password[i - 1] += 1;
            }
        } else {
            break;
        }
    }

    return password;
}

void* password_thread(void* threadArgs) {
    struct password_thread* args = threadArgs;

    char localPossiblePassword[MAX_PASSWORD_LENGTH] = {0};

    while (true) {
        locker_lock(args->passwordFound_mutex);

        if (*(args->passwordFound)) {
            locker_unlock(args->passwordFound_mutex);
            return NULL;
        }

        locker_unlock(args->passwordFound_mutex);

        locker_lock(args->possiblePassword_mutex);

        if (*(args->maxPasswordLength) == MAX_PASSWORD_LENGTH) {
            locker_unlock(args->possiblePassword_mutex);
            return NULL;
        }

        if (checkPasswordArray(args->possiblePassword, *(args->maxPasswordLength))) {
            *(args->maxPasswordLength) += 1;

            if (*(args->maxPasswordLength) == MAX_PASSWORD_LENGTH) {
                locker_unlock(args->possiblePassword_mutex);
                return NULL;
            }

            initPossiblePassword(args->possiblePassword, *(args->maxPasswordLength));
        }

        strcpy(localPossiblePassword, args->possiblePassword);

        if (*(args->maxPasswordLength) > testNum - 1) {
            inc5password(args->possiblePassword, *(args->maxPasswordLength));
        }

        locker_unlock(args->possiblePassword_mutex);

        //printf("thread id: %d; thread base password: |%s|\n", args->threadId, localPossiblePassword);
        if (check5Digits(localPossiblePassword, *(args->searchedSum), args)) {
            break;
        }
    }

    locker_lock(args->passwordFound_mutex);

    *(args->passwordFound) = true;
    strcpy(args->foundedPassword, localPossiblePassword);

    locker_unlock(args->passwordFound_mutex);

    return NULL;
}

int main() {
    vect password;

    for (int i = 0; i < 64; ++i) {
        scanf("%2x", &(password[i]));
    }
    
    char possiblePassword[MAX_PASSWORD_LENGTH] = {0};
    int maxLength = 0;

    char passwordFound = false;
    char foundedPassword[MAX_PASSWORD_LENGTH];

    locker possiblePassword_mutex,
           stdout_mutex,
           password_found_mutex;

    locker_init(&possiblePassword_mutex, NULL);
    locker_init(&stdout_mutex, NULL);
    locker_init(&password_found_mutex, NULL);

    pthread_t threads[NUM_OF_THREADS];

    struct password_thread passwordThreads[NUM_OF_THREADS];

    for (int i = 0; i < NUM_OF_THREADS; ++i) {
        passwordThreads[i].threadId = i;
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

    for (int i = 0; i < NUM_OF_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("\n%s\n", foundedPassword);

    return 0;
}
