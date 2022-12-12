bruteforce_mutex_one: 
	gcc  -include mutex.h -include ../crc32/one_byte.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread -march=native

bruteforce_mutex_two: 
	gcc  -include mutex.h -include ../crc32/two_bytes.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread -march=native

bruteforce_mutex_four: 
	gcc  -include mutex.h -include ../crc32/four_bytes.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread -march=native

bruteforce_mutex_one_proc: 
	gcc  -include mutex.h -include ../crc32/one_byte.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread -march=native

bruteforce_mutex_two_proc: 
	gcc  -include mutex.h -include ../crc32/two_bytes.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread -march=native

bruteforce_mutex_four_proc: 
	gcc  -include mutex.h -include ../crc32/four_bytes.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread -march=native



bruteforce_spinlock_one: 
	gcc  -include spinlock.h -include ../crc32/one_byte.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread

bruteforce_spinlock_two: 
	gcc  -include spinlock.h -include ../crc32/two_bytes.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread

bruteforce_spinlock_four: 
	gcc  -include spinlock.h -include ../crc32/four_bytes.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread

bruteforce_spinlock_one_proc: 
	gcc  -include spinlock.h -include ../crc32/one_byte.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread -march=native

bruteforce_spinlock_two_proc: 
	gcc  -include spinlock.h -include ../crc32/two_bytes.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread -march=native

bruteforce_spinlock_four_proc: 
	gcc  -include spinlock.h -include ../crc32/four_bytes.h -include ../crc32/proc_type.h ../crc32/crc32_func.c ../bruteforce_funcs/bruteforce_funcs.c bruteforce.c -lpthread -march=native

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

test7: a.out
	../crc32/encript_password.exe 1234567 | ./a.out

test8: a.out
	../crc32/encript_password.exe 12345678 | ./a.out

