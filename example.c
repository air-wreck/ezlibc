/* example.c

some nice examples of how to use some stuff from the library

you can build with "make example" */

#include "src/math.h"
#include "src/io.h"

int
main()
{
  /* using the ez_sin() function from the math library */
  ez_str_print("the sine of -65.82 is: ");
  double a = ez_sin(-65.82, 0.00001);
  ez_f_print(a, 9);
  ez_print("\n", 1);

  /* using the ez_print() function to write a string to stdout */
  const char *msg = "Hello World!\n";
  int len = 13;
  ez_print(msg, len);

  /* printing a signed integer with ez_int_print() */
  ez_int_print(1000);
  ez_print("\n", 1);

  /* printing a floating point number with ez_f_print() */
  ez_f_print(1234.56789, 7);
  ez_print("\n", 1);

  /* getting a character from stdin with ez_getchar() */
  ez_str_print("enter a character: ");
  char b = ez_getchar();
  ez_str_print("you entered: ");
  ez_print(&b, 1);
  ez_print("\n", 1);

  /* prematurely exiting with ez_exit() */
  ez_exit(0);

  return 0;
}
