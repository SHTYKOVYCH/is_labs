bruteforce_mutex_one: 
	gcc $(foo) -I../crc32/ -include ../crc32/gost_3411_2012_calc.h ../crc32/gost_3411_2012_calc.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread -march=native

test1: a.out
	../crc32/encript_password.exe -s 1 | ./a.out

test2: a.out
	../crc32/encript_password.exe -s 12 | ./a.out

test3: a.out
	../crc32/encript_password.exe -s 123 | ./a.out

test4: a.out
	../crc32/encript_password.exe -s 1234 | ./a.out

test5: a.out
	../crc32/encript_password.exe -s 12345 | ./a.out

test6: a.out
	../crc32/encript_password.exe -s 123456 | ./a.out

test7: a.out
	../crc32/encript_password.exe -s 1234567 | ./a.out

test8: a.out
	../crc32/encript_password.exe -s 12345678 | ./a.out

test_et:
	../crc32/encript_password.exe -s M[!BK\(9eraA1 | ./a.out
