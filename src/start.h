/* ezlibc/start.h

implement a custom C environment (really just an entry point) to avoid
dependence on linking against libc */

#ifndef EZ_START_
#define EZ_START_

int
main();

void
ez_exit(int status);

#endif
