#include <stdio.h>
#include <string.h>

#include "../crc32/crc32_func.h"

#define MAX_PASSWORD_LENGTH 10

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
        }
    } 
}

int main() {
    unsigned long password;

    scanf("%lx", &password);

    char possiblePassword[MAX_PASSWORD_LENGTH + 1] = {0};

    for (int maxLen = 1; maxLen < MAX_PASSWORD_LENGTH + 1; ++maxLen) {
        for (int i = 0; i < maxLen; ++i) {
            possiblePassword[i] = 32;
        } 

        do {
            unsigned long sum = compute_crc(possiblePassword);

            if (sum == password) {
                printf("\n%s\n", possiblePassword);
                goto password_found;
            }
            
            incPassword(possiblePassword, maxLen);
            //printf("\r%d %s", maxLen, possiblePassword);
        } while (!checkPasswordArray(possiblePassword, maxLen));
    }
    password_found:

    return 0;
}
