CC = gcc

all: example lib/ezlibc-math.so lib/ezlibc-io.so lib/ezlibc.so

example: example.c src/io.c
		cc example.c src/math.c src/io.c -o example -m32 -g

libs: src/io.c src/math.c
		cc -fPIC -shared -o lib/ezlibc-math.so src/math.c
		cc -fPIC -shared -o lib/ezlibc-io.so src/io.c -m32
		cc -fPIC -shared -o lib/ezlibc.so src/math.c src/io.c -m32

tests: src/io.c tests/io-driver/ez_print.c
		# here, we use *.out just so that it's easier to make a .gitignore rule
		cc tests/io-driver/ez_print.c src/io.c -o tests/io-driver/ez_print.out -m32
		cc tests/io-driver/ez_str_print.c src/io.c -o tests/io-driver/ez_str_print.out -m32
		cc tests/io-driver/ez_int_print.c src/io.c -o tests/io-driver/ez_int_print.out -m32
		cc tests/io-driver/ez_str10_to_int.c src/io.c -o tests/io-driver/ez_str10_to_int.out -m32
