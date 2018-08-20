#include "start.h"
#include "io.h"

void
_start()
{
  /* implement argc and argv in assembly later */
  int status = main();
  ez_exit(status);
}
