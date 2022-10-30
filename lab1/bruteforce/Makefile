all: bruteforce

bruteforce: 
	gcc -O3 ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c

test1: a.out
	../crc32/encript_password.exe 1 | ./a.out

test2: a.out
	../crc32/encript_password.exe 12 | ./a.out

test3: a.out
	../crc32/encript_password.exe 123 | ./a.out

test4: a.out
	../crc32/encript_password.exe 1234 | ./a.out

test5: a.out
	../crc32/encript_password.exe 12345 | ./a.out

test6: a.out
	../crc32/encript_password.exe 123456 | ./a.out

