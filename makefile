# C copmiler
CC = gcc

# architecture (pass -D_x64 for 64-bit or -D_OSX for OS X)
ARCH = -m32

# flags for linking against library
LIBFLAGS = -nostdlib -L. -l:lib/ezlibc.so -l:lib/ezlibc-start.o

# flags for compiling library
CFLAGS = -std=c89 -Wall -fPIC -shared


# builds everything
all: example libs

# removes the library files
rm:
	rm lib/*

# builds the included example.c file
example: example.c libs
		$(CC) example.c $(ARCH) $(LIBFLAGS) -o example

# builds JUST the library files
libs: src/io.h src/math.h src/start.h src/syscalls.h src/qmath.h src/stats.h src/io.c src/math.c src/start.c src/syscalls.c src/qmath.c src/stats.c
		$(CC) $(ARCH) $(CFLAGS) -o lib/ezlibc-math.so src/math.c
		$(CC) $(ARCH) $(CFLAGS) -o lib/ezlibc-qmath.so src/qmath.c src/math.c
		$(CC) $(ARCH) $(CFLAGS) -o lib/ezlibc-stats.so src/stats.c src/math.c
		$(CC) $(ARCH) $(CFLAGS) -o lib/ezlibc.so src/syscalls.c src/math.c src/io.c src/qmath.c src/stats.c
		$(CC) $(ARCH) $(CFLAGS) -c -o lib/ezlibc-start.o src/start.c

# fix these later
tests: src/io.c tests/io-driver/ez_print.c
		# here, we use *.out just so that it's easier to make a .gitignore rule
		cc tests/io-driver/ez_print.c src/io.c -o tests/io-driver/ez_print.out -m32
		cc tests/io-driver/ez_str_print.c src/io.c -o tests/io-driver/ez_str_print.out -m32
		cc tests/io-driver/ez_int_print.c src/io.c -o tests/io-driver/ez_int_print.out -m32
		cc tests/io-driver/ez_str10_to_int.c src/io.c -o tests/io-driver/ez_str10_to_int.out -m32
