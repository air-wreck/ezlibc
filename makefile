CC = gcc

all: example lib/ezlibc-math.so lib/ezlibc-io.so lib/ezlibc.so lib/ezlibc-start.o

example: example.c lib/ezlibc.so lib/ezlibc-start.o
		cc -nostdlib -m32 example.c -L. -l:lib/ezlibc.so -l:lib/ezlibc-start.o -o example

libs: src/io.h src/math.h src/start.h src/io.c src/math.c src/start.c
		cc -std=c89 -Wall -fPIC -shared -m64 -o lib/ezlibc-math64.so src/math.c
		cc -std=c89 -Wall -fPIC -shared -m32 -o lib/ezlibc-math.so src/math.c
		cc -std=c89 -Wall -fPIC -shared -m32 -o lib/ezlibc-io.so src/io.c
		cc -std=c89 -Wall -fPIC -shared -m32 -o lib/ezlibc.so src/math.c src/io.c
		cc -std=c89 -Wall -m32 -c -o lib/ezlibc-start.o src/start.c

# fix these later
tests: src/io.c tests/io-driver/ez_print.c
		# here, we use *.out just so that it's easier to make a .gitignore rule
		cc tests/io-driver/ez_print.c src/io.c -o tests/io-driver/ez_print.out -m32
		cc tests/io-driver/ez_str_print.c src/io.c -o tests/io-driver/ez_str_print.out -m32
		cc tests/io-driver/ez_int_print.c src/io.c -o tests/io-driver/ez_int_print.out -m32
		cc tests/io-driver/ez_str10_to_int.c src/io.c -o tests/io-driver/ez_str10_to_int.out -m32
