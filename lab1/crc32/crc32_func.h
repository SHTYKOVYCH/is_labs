#ifndef CRC32_FUNC
#define CRC32_FUNC

extern unsigned long crc_table[ 255 ];

unsigned long compute_crc(char* str);
unsigned long int crc_byte( unsigned long input);
void computeTable();

#endif
