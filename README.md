# ezlibc

A C library written by Eric Zheng!

This is not supposed to be a POSIX-compliant C Standard Library or anything. Something of that scope is way beyond me. Basically, I was learning Taylor series and stuff in calc and thought that it would be cool to make custom implementations of some common math functions. Then I realized that I could simultaneously learn a bit of assembly by writing some low-level IO. Then this happened. (It's basically a learning exercise for a high school student.)

Currently, there is a decent basic math library (featuring arbitrary precision floating point calculations!) and a very rudimentary IO library.

Right now, I have no clue where this project is headed, so the structure is a little haphazard. Basically, the C source goes in `src/`, the compiled stuff goes in `lib/`, and the unit tests go in `tests/`.

Ultimately, this is supposed to become a little library that can be used to write basic programs in C without needing to use a "real" C library. Feel free to contribute stuff if so inclined.

### getting started
All you need to use this library is a plain old C compiler. If you want to run the unit tests, Python will also be necessary. Once you have those, you can just clone and run the init script (which really just makes a target directory for the compiler); for example:

```sh
git clone https://github.com/air-wreck/ezlibc.git
cd ezlibc
./init.sh
```

It might be somewhat important to note that whatever C compiler you choose, it must understand GCC extended inline `__asm__` syntax for the IO library to compile correctly. If you only plan on compiling the math library, that won't be a problem.

### usage
Once you build the library, all the compiled stuff is in `lib/`. As shown in the example, you'll want to `#include` the appropriate header files (always `src/start.h`, and then others if you need them) from within your `*.c` file. You can then compile your code with a few compiler flags:

| Flag                    | Purpose |
|:----------------------- |:------- |
| `-m32`                  | Compile for 32-bit target architecture |
| `-L.`                   | Look for library files in the local directory |
| `-l:lib/ezlibc.so`      | Link against the shared main library |
| `-l:lib/ezlibc-start.o` | Link against the static start routine |
| `-nostdlib`             | Do not link against `libc` (use our own library instead) |

Optionally, you can also use `-stc=c89` for stricter Standard conformance, and `-Wall` is usually a decent idea.

This will allow you to access the entire library (and drop the usage of `libc` entirely). However, if all you're interested in is the math library, the `lib/ezlibc-math.so` file is pretty much standalone. Also (only for math), there is a 64-bit version available as `lib/ezlibc-math64.so`. If you need the rest of the library, you're stuck in 32-bit mode.

So, a sort of working minimal example of usage of this project could look like (assuming you've cloned, set up, and built everything):

```C
/* hello.c */
#include "src/start.h"
#include "src/io.h"

int main() {
  const char *msg = "Hello World!\n";
  ez_str_print(msg);
  return 0;
}
```

```sh
gcc -m32 -L. -l:lib/ezlibc.so -l:lib/ezlibc-start.o -nostdlib hello.c -o hello
./hello
```

### building
The makefile is ugly, but it works. You can build the example with:

```sh
make example
```

And the entire library with:

```sh
make libs
```

If you don't trust any makefiles I wrote (possibly a wise choice), you can directly build, for example, the math library with:

```sh
gcc -std=c89 -fPIC -shared -o lib/ezlibc-math.so src/math.c
```

Note that you'll need to compile all non-math libraries with `-m32`. If you want to compile IO for OS X, you'll need to specify `-D_OSX` (otherwise, it defaults to Linux). Note that the OS X option is not automatically included in the makefile yet, so you'll need to manually specify it.

### testing
Unit tests are currently being done in Python, because that's pretty nice. To run a specific test (like the `math` library), just run the test file from the project root:

```sh
python tests/test-math.py -v
```

Note that the IO tests rely on separately compiled binaries that provide wrappers around the original C functions, since the C is written for 32-bit x86 but I'm running Python in 64-bit and it's a headache to get those to work together directly. So, before you run the IO tests, you might want to build the latest `tests/io-driver/` test programs:

```sh
make tests
```

### comments

#### math
Right now, I'm prioritizing readability/understandableness (I don't think that's a word) over raw speed/efficiency, but I might go back and write more efficient stuff later. As such, the code is being written purely in "portable" C89 -- no architecture-specific processor instructions like Intel's `fsin`.

Update August 2018: I have fixed the compounding error issue. The library routines should now do arbitrary precision floating point arithmetic (up to machine double floating-point precision, so I guess not really arbitrary). There are some fishy things with big numbers, but I think they have more to do with machine precision limitations than algorithmic limitations.

Also, I need to figure out how all those special values (`nan`, `+inf`, `-inf`) actually work.

#### io
The IO code is supposed to work on OS X and Linux (both 32-bit x86). You can choose which one using compiler flags (defaults to Linux). The assembly is simple enough that it will probably work fine on BSD, but don't take my word for it.

#### start
As I later found out, one issue with doing away with `libc` is that we need to define the `_start` routine ourselves. In order to keep the user code more like "regular" C code (i.e. using `int main()`), I decided to write a small, statically-linked start routine, found in `start.c`. I haven't gotten around to implementing `argc` and `argv` yet.

#### mem?
I think I want to offer more advanced IO and other functionality in the future (maybe even expand math to include linalg routines!), but a key step that needs to be taken before that is writing good memory management functions (think `memcpy()`, etc.). I think I'll have to start by writing a `malloc()` implementation, but a project like that will have to wait until I have more free time (read: done with college apps).
