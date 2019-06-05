/* example.c

some nice examples of how to use some stuff from the library

you can build this file with:
gcc -std=c89 -m32 -Wall -nostdlib example.c src/io.c src/start.c -o example

it is probably better to build the library first and then link against that,
however:
make example
./example */

#include "src/start.h"
#include "src/io.h"

int
main(int argc, char **argv)
{
  /* show that argc and argv work as expected */
  const char *msg = "argc is: ";
  int len = 9;
  ez_print(msg, len);
  ez_int_print(argc);
  ez_str_print("\n");
  
  msg = "argv[0] is: ";
  len = 12;
  ez_print(msg, len);
  ez_str_print(argv[0]);
  ez_str_print("\n");

  /* getting a character from stdin with ez_getchar() */
  ez_str_print("enter a character: ");
  char b = ez_getchar();
  ez_getchar();  /* take care of trailing newline */
  ez_str_print("you entered: ");
  ez_print(&b, 1);
  ez_str_print("\n");

  return 0;
}
