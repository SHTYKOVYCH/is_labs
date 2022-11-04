all: crc32

crc32: 
	gcc crc32_func.c crc32.c -o encript_password.exe -march=native -mavx2 -mbmi2 -mpopcnt -mfma -mcx16 -mtune=znver1

test: encript_password.exe
	./encript_password.exe 12345
