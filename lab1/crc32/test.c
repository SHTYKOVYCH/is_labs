#include <stdio.h>
#include <string.h>

int main() {
    unsigned char* str = "12345";
    unsigned strLen = strlen(str);


    for (int i = 0; i < strLen; ++i) {
        printf("%x ", str[i]);
    }

    printf("\n");

    for (int i = 0; i < (strLen >> 1); ++i) {
        printf("%x ", ((unsigned short*)str)[i]);
    }
}
