#include "../../src/io.h"

int
main(int argc, char **argv)
{
  /* this basic test program will do no error checking */
  char *msg = argv[1];
  char *len_as_str = argv[2];

  return ez_print(msg, ez_str10_to_int(len_as_str));
}
