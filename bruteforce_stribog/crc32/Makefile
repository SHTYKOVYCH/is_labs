all: crc32

crc32: 
	gcc -include gost_3411_2012_calc.h gost_3411_2012_calc.c stribog.c -o encript_password.exe

test: encript_password.exe
	./encript_password.exe -s 12345
