# ezlibc

A C library written by Eric Zheng!

This is not supposed to be a POSIX-compliant C Standard Library or anything. Something of that scope is way beyond me. Basically, I was learning Taylor series and stuff in calc and thought that it would be cool to make custom implementations of some common math functions. Then I realized that I could simultaneously brush up on my assembly by writing some low-level IO. Then this happened.

Right now, I have no clue where this project is headed, so the structure is a little haphazard. Basically, the C source goes in `src/`, the compiled stuff goes in `lib/`, and the unit tests go in `tests/`. I have absolutely no clue what's going on with the makefile.

Ultimately, this is supposed to become a little library that can be used to write basic programs in C without needing a "real" C library like `glibc`. For example, I will have to get around to writing custom IO functions instead of just using nice things like `printf()`. Feel free to contribute stuff if so inclined. Or just watch me fail from the sidelines. Whatever suits you.

### building
Yeah, as stated earlier, I have no clue what's going on with the makefile. I don't even know why vim won't give me stupid tab indents there. Anyway, you can build the example with:

```
make example
```

And the entire library with:

```
make libs
```

### testing
Unit tests are currently being done in Python, because that's pretty nice. To run a specific test (like the `math` library), just run the test file from the project root:

```
python tests/test-math.py -v
```

Although apparently `ctypes`'s behavior varies from OS to OS? It seems to work on macOS, so whatever.

### comments

#### math
Right now, I'm prioritizing readability/understandableness (I don't think that's a word) over raw speed/efficiency, but I might go back and write more efficient stuff later. As such, the code is being written purely in "portable" C -- no architecture-specific processor instructions like Intel's `fsin`.

Another thing -- a lot of the floating-point functions contain an `err` parameter to signify the maximum permissible error for the result. However, I still need to figure out how to deal with compounded error when one function calls another. So please don't try to use these functions for any sort of high-precision arithmetic. Actually, it's probably not a good idea to use this library for anything at all except for fun.

Also, I need to figure out how all those special values (`nan`, `+inf`, `-inf`) actually work.

#### io
Obviously, IO without the nice C Standard Library is going to have to get a little dirty with the kernel. The IO code targets the BSD-like syscall interface of macOS (for 32-bit x86 architecture). It makes use of GCC inline assembly syntax. Help porting to other OSs would be appreciated.
