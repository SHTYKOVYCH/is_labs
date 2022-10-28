#include <stdio.h>
#include <string.h>

#include "./crc32_func.h"

int main(int argc, char* argv[]) {
    char message[4096] = {0};

    if (argc != 1) {
        strcpy(message, argv[1]);
    } else {
        scanf("%s", message);
    }
    
    printf("%lx\n", compute_crc(message));

    return 0;
}
