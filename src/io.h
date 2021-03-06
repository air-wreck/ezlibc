/* ezlibc/io.h

basic input and output */

#ifndef EZ_IO_
#define EZ_IO_

/* define the NULL constant to be 0
   we'll just hope that this holds true for our platforms */
#define EZ_NULL 0

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

/* get char from stdin
   does not dispose of trailing newline

   returns:
   char c: char from stdin */
char
ez_getchar();

/* get string from stdin

   parameters:
   char *buf: byte buffer for string
              should be at least len+1 bytes long
   int len: length of string
            this does not include the NULL

   returns:
   int n: number of bytes written to *buf */
int
ez_n_getstr(char *buf, int len);

/* convert a base ten string representation to an integer

   parameters:
   const char *str10: base ten string, with optional sign

   returns:
   int num: integer represented by string

   error:
   returns -1 on error */
int
ez_str10_to_int(const char *str10);

#endif
