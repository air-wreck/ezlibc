#include "../../src/io.h"

int
main(int argc, char **argv)
{
  char *num = argv[1];
  return ez_int_print(ez_str10_to_int(num));
}
