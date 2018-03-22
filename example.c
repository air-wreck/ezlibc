/* example.c

some nice examples of how to use some stuff from the library

you can build with "make example" */

#include <stdio.h>
#include "src/math.h"

int
main()
{
  /* using the ez_sin() function from the math library */
  double a = ez_sin(-65.82, 0.00001);
  printf("%.10f\n", a);
  return 0;
}
