#include "start.h"
#include "syscalls.h"

/* _start must be implemented in assembly */
#ifdef _x64  /** 64-bit **/

#else  /** 32-bit **/
/*__asm__ (
  ".global _start;"
  "_start:;"
  " "
); */
#endif

void
ez_exit(status)
{
  ez_sys_exit(status);
}

void
_start()
{
  /* implement argc and argv in assembly later */
  int status = main();
  ez_exit(status);
}
