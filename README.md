# ezlibc

A C library written by Eric Zheng!

This is not supposed to be a POSIX-compliant C Standard Library or anything. Something of that scope is way beyond me. Basically, I was learning Taylor series and stuff in calc and thought that it would be cool to make custom implementations of some common math functions. Then I realized that I could simultaneously brush up on my assembly by writing some low-level IO. Then this happened.

Currently, there is a decent basic math library (featuring arbitrary precision floating point calculations!) and a very rudimentary IO library.

Right now, I have no clue where this project is headed, so the structure is a little haphazard. Basically, the C source goes in `src/`, the compiled stuff goes in `lib/`, and the unit tests go in `tests/`. I have absolutely no clue what's going on with the makefile.

Ultimately, this is supposed to become a little library that can be used to write basic programs in C without needing a "real" C library like `glibc`. For example, I will have to get around to writing custom IO functions instead of just using nice things like `printf()`. Feel free to contribute stuff if so inclined. Or just watch me fail from the sidelines. Whatever suits you.

### getting started
All you need to use this library is a plain old C compiler. If you want to run the unit tests, Python will also be necessary. Once you have those, you can just clone and run the init script (which really just makes a target directory for the compiler); for example:

```sh
git clone https://github.com/air-wreck/ezlibc.git
cd ezlibc
./init.sh
```

It might be somewhat important to note that whatever C compiler you choose, it must understand GCC inline `__asm__` syntax for the IO library to compile correctly. If you only plan on compiling the math library, that won't be a problem.

### building
Yeah, as stated earlier, I have no clue what's going on with the makefile. I don't even know why vim won't give me stupid tab indents there. Anyway, you can build the example with:

```sh
make example
```

And the entire library with:

```sh
make libs
```

However, I personally wouldn't trust any makefiles I wrote. You can directly build, for example, the math library with:

```sh
gcc -std=c89 -fPIC -shared -o lib/ezlibc-math.so src/math.c
```

Note that you'll need to compile the IO library with `-m32`. If you want to compile IO for OS X, you'll need to specify `-D_OSX` (otherwise, it defaults to Linux).

### testing
Unit tests are currently being done in Python, because that's pretty nice. To run a specific test (like the `math` library), just run the test file from the project root:

```sh
python tests/test-math.py -v
```

Although apparently `ctypes`'s behavior varies from OS to OS? It seems to work on macOS, so whatever.

Note that the IO tests rely on separately compiled binaries that provide wrappers around the original C functions, since the C is written for 32-bit x86 but I'm running Python in 64-bit and it's a headache to get those to work together directly. So, before you run the IO tests, you might want to build the latest `tests/io-driver/` test programs:

```sh
make tests
```

### comments

#### math
Right now, I'm prioritizing readability/understandableness (I don't think that's a word) over raw speed/efficiency, but I might go back and write more efficient stuff later. As such, the code is being written purely in "portable" C89 -- no architecture-specific processor instructions like Intel's `fsin`.

Update August 2018: I have fixed the compounding error issue. The library routines should now do arbitrary precision floating point arithmetic. There are some fishy things with big numbers, but I think they have more to do with machine precision limitations than algorithmic limitations.

Also, I need to figure out how all those special values (`nan`, `+inf`, `-inf`) actually work.

#### io
The IO code is supposed to work on OS X and Linux (both 32-bit x86). You can choose which one using compiler flags (defaults to Linux). The assembly is simple enough that it will probably work fine on BSD, but don't take my word for it.

#### mem?
I think I want to offer more advanced IO and other functionality in the future (maybe even expand math to include linalg routines!), but a key step that needs to be taken before that is writing good memory management functions (think `memcpy()`, etc.). I think I'll have to start by writing a `malloc()` implementation, but a project like that will have to wait until I have more free time (read: done with college apps).
