#include "start.h"
#include "syscalls.h"

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
