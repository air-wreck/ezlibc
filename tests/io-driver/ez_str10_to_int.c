#include "../../src/io.h"

int
main(int argc, char **argv)
{
  char *num = argv[1];

  /* we need to print because of issues with returning a weird exit status
     from main() */
  return ez_int_print(ez_str10_to_int(num));
}
