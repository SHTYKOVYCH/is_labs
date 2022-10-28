#include <string.h>

#include "./crc32_func.h"

#define CRC_POLYNOM 0xEDB88320

unsigned long compute_crc(char* str) {
    unsigned long sum = 0xFFFFFFFF;

    unsigned strLen = strlen(str);

    for (int i = 0; i < strLen; ++i) {
        sum ^= str[i];
        for (int j = 0; j < 8; ++j) {
            sum = sum & 1? (sum >> 1) ^ CRC_POLYNOM : sum >> 1; 
        }
    }

    return sum ^ 0xFFFFFFFF;
}
