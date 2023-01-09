#include "bruteforce_funcs.h"

void initPossiblePassword(char* password, int maxLen) {
    password[maxLen - 1] = 32;
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


