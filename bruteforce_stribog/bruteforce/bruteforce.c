#include <stdio.h>
#include <string.h>

#include "../crc32/crc32_func.h"
#include "../bruteforce_funcs/bruteforce_funcs.h"

#define MAX_PASSWORD_LENGTH 10

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
