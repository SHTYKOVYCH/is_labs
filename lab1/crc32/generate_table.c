#include <stdio.h>
#include <limits.h>

#include "./crc32_table.h"

#define CRC_POLYNOM     0xEDB88320
#define MAX_NUM         UCHAR_MAX + 1
#define NUM_OF_BYTES    8
#define NUM_IN_ROW      8

int main() {
    for (unsigned long i = 0; i < MAX_NUM;) {
        printf("\t");
        for (unsigned long j = 0; j < NUM_IN_ROW; ++j, ++i) {
            unsigned long sum = 0;
            // for one byte table init
            // sum ^= i;
            //
            //for (int k = 0; k < NUM_OF_BYTES; ++k) {
            //    sum = sum & 1 ? (sum >> 1) ^ CRC_POLYNOM : sum >> 1;
            //}


            // for two bytes table init
            sum = crc32_tab_byte[i + 6*256];
            sum = (sum >> 8) ^ crc32_tab_byte[sum & 0xff];

            printf("0x%lx, ", sum);
        }
        printf("\n");
    }

}
