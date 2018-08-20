/* example.c

some nice examples of how to use some stuff from the library

you can build with "make example" */

#include "src/io.h"

int
main()
{
  /* using the ez_print() function to write a string to stdout */
  const char *msg = "Hello World!\n";
  int len = 13;
  ez_print(msg, len);

  /* getting a character from stdin with ez_getchar() */
  ez_str_print("enter a character: ");
  char b = ez_getchar();
  ez_getchar();  /* take care of trailing newline */
  ez_str_print("you entered: ");
  ez_print(&b, 1);
  ez_str_print("\n");

  /* get a string from stding with ez_n_getstr() */
  ez_str_print("enter a string of at most length 9: ");
  char str[10] = {0};
  int str_len = ez_n_getstr(str, 9);
  ez_str_print("you entered: ");
  if (str_len < 9) {
    ez_print(str, str_len - 1);
  } else {
    ez_print(str, str_len);
  }
  ez_str_print("\n");

  /* prematurely exiting with ez_exit() */
  ez_exit(0);

  return 0;
}
