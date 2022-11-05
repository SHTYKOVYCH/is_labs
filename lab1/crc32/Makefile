all: crc32

crc32_one: 
	gcc -include one_byte.h crc32_func.c crc32.c -o encript_password.exe -march=native -mavx2 -mbmi2 -mpopcnt -mfma -mcx16 -mtune=znver1

crc32_two: 
	gcc -include two_bytes.h crc32_func.c crc32.c -o encript_password.exe -march=native -mavx2 -mbmi2 -mpopcnt -mfma -mcx16 -mtune=znver1

crc32_four: 
	gcc -include four_bytes.h crc32_func.c crc32.c -o encript_password.exe -march=native -mavx2 -mbmi2 -mpopcnt -mfma -mcx16 -mtune=znver1

crc32: 
	gcc crc32_func.c crc32.c -o encript_password.exe -march=native -mavx2 -mbmi2 -mpopcnt -mfma -mcx16 -mtune=znver1

test: encript_password.exe
	./encript_password.exe 12345
