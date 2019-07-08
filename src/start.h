/* ezlibc/start.h

implement a custom C environment (really just an entry point) to avoid
dependence on linking against libc */

#ifndef EZ_START_
#define EZ_START_

int
main();

#ifdef _x64
void
ez_wrap_exit(int status);
#endif

#endif
