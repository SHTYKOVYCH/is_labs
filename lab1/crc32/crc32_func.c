#include <string.h>
#include <stdio.h>
#include <immintrin.h>

#include "./crc32_func.h"
#include "./crc32_table.h"

#ifndef NUM_OF_BYTES
#define NUM_OF_BYTES 1
#endif

#ifndef MODE
#define MODE 0
#endif

unsigned long compute_crc(char* str) {

    unsigned long sum = 0xFFFFFFFF;

    unsigned strLen = strlen(str);
    
#if MODE==0
#if NUM_OF_BYTES==1
    // One byte tabular
    for (int i = 0; i < strLen; ++i) {
        sum = crc32_tab_byte[(sum ^ str[i]) & 0xff] ^ (sum >> 8);
    }
#elif NUM_OF_BYTES==2
    // Two bytes tabular
    if (strLen & 1) {
        sum = crc32_tab_byte[(sum ^ str[0]) & 0xff] ^ (sum >> 8);
        str += 1;
    }

    strLen >>= 1;

    unsigned short* strS = (unsigned short*)str;

    for (unsigned i = 0; i < strLen; ++i) {
        sum ^= strS[i];
        sum = crc32_tab_byte[sum & 0xff | 0x100] ^ crc32_tab_byte[(sum >> 8) & 0xff] ^ (sum >> 16);
    }
#elif NUM_OF_BYTES==4
    // four byte tabular
    if (strLen & 0x3) {
        if (strLen & 0x1) {
            sum = crc32_tab_byte[(sum ^ str[0]) & 0xff] ^ (sum >> 8);
            str += 1;
        }

        if (strLen & 0x2) {
            sum = crc32_tab_byte[(sum ^ str[0]) & 0xff] ^ (sum >> 8);
            sum = crc32_tab_byte[(sum ^ str[1]) & 0xff] ^ (sum >> 8);
            str += 2;
        }
    }

    unsigned int* strI = (unsigned int*)str;
    strLen >>= 2;

    for (unsigned i = 0; i < strLen; ++i) {
        sum ^= strI[i];
        sum = crc32_tab_byte[sum & 0xff | 0x300] ^ crc32_tab_byte[(sum >> 8) & 0xff | 0x200] ^ crc32_tab_byte[(sum >> 16) & 0xff | 0x100] ^ crc32_tab_byte[(sum >> 24) & 0xff];
    }
#endif
#else
#if NUM_OF_BYTES==1
    // One byte tabular
    for (int i = 0; i < strLen; ++i) {
        sum = _mm_crc32_u8(sum, str[i]);
    }
#elif NUM_OF_BYTES==2
    // Two bytes tabular
    if (strLen & 1) {
        sum = _mm_crc32_u8(sum, str[0]);
        str += 1;
    }

    strLen >>= 1;

    unsigned short* strS = (unsigned short*)str;

    for (unsigned i = 0; i < strLen; ++i) {
        sum = _mm_crc32_u16(sum, strS[i]);
    }
#elif NUM_OF_BYTES==4
    // four byte tabular
    if (strLen & 0x3) {
        if (strLen & 0x1) {
            sum = _mm_crc32_u8(sum, str[0]);
            str += 1;
        }

        if (strLen & 0x2) {
            sum = _mm_crc32_u16(sum, ((unsigned short*)str)[0]);
            str += 2;
        }
    }

    unsigned int* strI = (unsigned int*)str;
    strLen >>= 2;

    for (unsigned i = 0; i < strLen; ++i) {
        sum = _mm_crc32_u32(sum, strI[i]);
    }
#endif
#endif

    return sum ^ 0xFFFFFFFF;
}
