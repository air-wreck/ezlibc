#include "../../src/io.h"

int
main(int argc, char **argv)
{
  char *msg = argv[1];
  return ez_str_print(msg);
}
