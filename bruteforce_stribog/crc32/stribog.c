#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "gost_3411_2012_calc.h"

#define FILE_BUFFER_SIZE 4096
#define DEFAULT_HASH_SIZE 512

TGOSTHashContext *CTX;

static void
HashPrint(TGOSTHashContext *CTX)
{
    int i;
    for(i = 0; i < 64; i++)
        printf("%02x", CTX->hash[i]);
    printf("\n");
}

static void
GetHashString(const char *str, int hash_size)
{
    uint8_t *buffer;
    buffer = malloc(strlen(str));
    memcpy(buffer, str, strlen(str));
    GOSTHashInit(CTX);
    GOSTHashUpdate(CTX, buffer, strlen(str));
    GOSTHashFinal(CTX);
    HashPrint(CTX);
}

int main(int argc, char *argv[])
{
    CTX = (TGOSTHashContext*)(malloc(sizeof(TGOSTHashContext)));

    int hash_size = DEFAULT_HASH_SIZE;
    int opt;
    while ((opt = getopt(argc, argv, "htf:s:d:")) != -1)
    {
        switch (opt)
        {
            case 's':
                GetHashString(optarg, hash_size);
            break;
        }
    }
    return 0;
}
