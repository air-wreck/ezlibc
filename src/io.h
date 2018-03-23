/* ezlibc/io.h

basic input and output */

#ifndef EZ_IO_
#define EZ_IO_

/* printing to stdout

   parameters:
   const char *msg: pointer to the char buffer
   int len: number of chars to print

   returns:
   int len: number of chars written */
int
ez_print(const char *msg, int len);

/* print an int to stdout

   parameters:
   int n: (signed) integer to print

   returns:
   int len: number bytes written to stdout */
int
ez_int_print(int n);

/* print a double to stdout

   parameters:
   double n: double to print
             assumed to fit within an int
   int places: decimal places to print
               0 <= places <= 9

   returns:
   int len: number bytes written to stdout

   error:
   -1 signals that an error occured */
int
ez_f_print(double n, int places);

/* print a string to stdout

   parameters:
   const char *msg: null-terminated string to write

   returns:
   int len: number bytes written to stdout */
int
ez_str_print(const char *msg);

/* get char from stdin, automatically disposing of
   trailing newline (maybe fix later with better
   implementation)

   returns:
   char c: char from stdin */
char
ez_getchar();

/* exit process

   parameters:
   int status: exit status */
void
ez_exit(int status);

#endif
