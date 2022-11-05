bruteforce_one:
	gcc -include ../crc32/one_byte.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_two:
	gcc -include ../crc32/two_bytes.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_four:
	gcc -include ../crc32/four_bytes.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_one_opt:
	gcc -O3 -include ../crc32/one_byte.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_two_opt:
	gcc -O3 -include ../crc32/two_bytes.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_four_opt:
	gcc -O3 -include ../crc32/four_bytes.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_one_proc:
	gcc -include ../crc32/one_byte.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_two_proc:
	gcc -include ../crc32/two_bytes.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_four_proc:
	gcc -include ../crc32/four_bytes.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_one_opt_proc:
	gcc -O3 -include ../crc32/one_byte.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_two_opt_proc:
	gcc -O3 -include ../crc32/two_bytes.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

bruteforce_four_opt_proc:
	gcc -O3 -include ../crc32/four_bytes.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -march=native

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

