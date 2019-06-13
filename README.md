# ezlibc

A C library written by Eric Zheng!

This is not supposed to be a POSIX-compliant C Standard Library or anything. This is just a learning exercise for a high school student. Currently, there is a decent basic math library (featuring "high precision" floating point calculations!) and a very rudimentary IO library.

Right now, I have no clue where this project is headed, so the structure is a little haphazard. Basically, the C source goes in `src/`, the compiled stuff goes in `lib/`, and the unit tests go in `tests/`.

Ultimately, this is supposed to become a little library that can be used to write basic programs in C without needing to use a "real" C library. Feel free to contribute stuff if so inclined.

## getting started
All you need to use this library is a plain old C compiler. If you want to run the unit tests, Python will also be necessary. Once you have those, you can just clone and run the init script (which really just makes a target directory for the compiler); for example:

```sh
git clone https://github.com/air-wreck/ezlibc.git
cd ezlibc
./init.sh
```

It might be somewhat important to note that whatever C compiler you choose, it must understand GCC extended inline `__asm__` syntax for the IO library to compile correctly. If you only plan on compiling the math library, that won't be a problem.

## usage
Once you build the library, all the compiled stuff is in `lib/`. As shown in the example, you'll want to `#include` the appropriate header files (always `src/start.h`, and then others if you need them) from within your `*.c` file. You can then compile your code with a few compiler flags:

| Flag                    | Purpose |
|:----------------------- |:------- |
| `-L.`                   | Look for library files in the local directory |
| `-l:lib/ezlibc.so`      | Link against the shared main library |
| `-l:lib/ezlibc-start.o` | Link against the static start routine |
| `-nostdlib`             | Do not link against `libc` (use our own library instead) |

Optionally, you can also use `-stc=c89` for stricter Standard conformance, and `-Wall` is usually a decent idea.

So, a sort of minimal working example of usage of this project could look like (assuming you've cloned, set up, and built everything):

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
gcc -L. -l:lib/ezlibc.so -l:lib/ezlibc-start.o -nostdlib hello.c -o hello
./hello
```

Note that the `ez_*` and `EZ_*` namespaces are reserved by this library.

## building
You might not want to trust any makefiles I wrote, but it seems to work. You can build the library with:

```sh
make libs
```

And the library plus additional usage example with:

```sh
make example
```

`Important!` This library can be built for a few different systems and architectures: Linux (both x86 and x86_64) and OS X/BSD (x86 only). *If you do not specify any special flags for the makefile, it will default to 32-bit Linux!* Here's a handy table of how you should build the library for different architectures:

|           | 32-bit                  | 64-bit                  |
|:---------:|:----------------------- |:----------------------- |
| **Linux** | `make libs`             | `make libs ARCH=-D_x64` |
| **OS X**  | `make libs ARCH=-D_OSX` | unsupported             |

Note that while building the library for 64-bit OS X is unsupported right now, you can still use it on 64-bit OS X. You'll just need to tell gcc `-m32` (compile for 32-bit architectures) when using the library.

## testing
Unit tests are currently being done in Python, because that's pretty nice. To run a specific test (like the `math` library), just run the test file from the project root:

```sh
python tests/test-math.py -v
```

Note that the IO tests rely on separately compiled binaries that provide wrappers around the original C functions, since the C is written for 32-bit x86 but I'm running Python in 64-bit and it's a headache to get those to work together directly. So, before you run the IO tests, you might want to build the latest `tests/io-driver/` test programs:

```sh
make tests
```

## comments

#### math
Right now, I'm prioritizing readability/understandableness (I don't think that's a word) over raw speed/efficiency, but I might go back and write more efficient stuff later. As such, the code is being written purely in "portable" C89 -- no architecture-specific processor instructions like Intel's `fsin`.

Update August 2018: I have fixed the compounding error issue. The library routines should now do arbitrary precision floating point arithmetic (up to machine double floating-point precision, so I guess not really arbitrary). There are some fishy things with big numbers, but I think they have more to do with machine precision limitations than algorithmic limitations.

Also, I need to figure out how all those special values (`nan`, `+inf`, `-inf`) actually work.

I think I want to write a `qmath.c` library sometime for imprecise (but faster) arithmetic. This is because a lot of the really fun approximations (Chebyshev polynomials, Stirling's approximation, minimax fitting, etc.) don't fit too well with this whole "user-specified precision" thing.

#### io
The IO code is supposed to work on OS X and Linux (both 32-bit x86). You can choose which one using compiler flags (defaults to Linux). The assembly is simple enough that it will probably work fine on BSD, but don't take my word for it. To make things more convenient, I will probably implement a subset of `printf`.

#### start
As I later found out, one issue with doing away with `libc` is that we need to define the `_start` routine ourselves. In order to keep the user code more like "regular" C code (i.e. using `int main()`), I decided to write a small, statically-linked start routine, found in `start.c`. Currently, `argc` and `argv` are only working on Linux. There is code for OS X/BSD, but testing on that platform isn't a high priority.

#### syscalls
It might logically make more sense to distribute the syscall wrappers between the relevant files (for example, keeping `write` and `read` in `src/io.c` and `exit` in `src/start.c`), but since I have so few syscall wrappers right now, I've decided to consolidate them into one `src/syscalls.c` file for organization.

#### mem
`malloc` has finally been written, but only for 32-bit Linux, and the implementation is very poor. I think I'm going to make the implementation more refined when I get around to it.

