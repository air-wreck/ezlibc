CC = gcc

example: example.c src/math.c src/io.c
		cc example.c src/math.c src/io.c -o example -m32 -g

libs: src/io.c src/math.c
		cc -fPIC -shared -o lib/ezlibc-math.so src/math.c
		cc -fPIC -shared -o lib/ezlibc-io.so src/io.c -m32
		cc -fPIC -shared -o lib/ezlic.so src/math.c src/io.c -m32
