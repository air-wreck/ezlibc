CC = gcc

example: example.c src/math.c
		cc example.c src/math.c -o example

libs: src/io.c src/math.c
		cc -fPIC -shared -o lib/ezlibc-math.so src/math.c
		cc -fPIC -shared -o lib/ezlibc-io.so src/io.c
		cc -fPIC -shared -o lib/ezlic.so src/math.c src/io.c
