all: bruteforce

bruteforce: 
	gcc ../crc32/crc32_func.c bruteforce.c

test: a.out
	../crc32/encript_password.exe 12345 | ./a.out
