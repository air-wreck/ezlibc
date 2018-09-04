/* ezlibc/math.h

basic math functions with pretty slow implementations */

#ifndef EZ_MATH_
#define EZ_MATH_

/* IEEE 754 defines the following special double-precision values */
/* #define EZ_NAN  0x7FF7FFFFFFFFFFFF */
#define EZ_NAN (0.0 / 0.0)
#define EZ_P_INF 0x7FF0000000000000
#define EZ_N_INF 0xFFF0000000000000

/* define basic mathematical constants as macros */
#define EZ_E   2.718281828459045
#define EZ_PI  3.141592653589793
#define EZ_2PI 6.283185307179586

/* absolute value of an integer

   parameters:
   int x: argument to |x|

   returns:
   int res: the value of |x| */
int
ez_int_abs(int x);

/* absolute value of a double

   parameters:
   double x: the argument of |x|

   returns:
   double res: the value of |x| */
double
ez_f_abs(double x);

/* modulus of a floating point number

   parameters:
   double a: the first parameter to a mod b
   double b: the second parameter to a mod b

   result:
   double res: the value of a mod b

   error:
   will return EZ_NAN if b == 0 */
double
ez_f_mod(double a, double b);

/* rounds a double to an int

   parameters:
   double x: the double to round

   returns:
   int res: the rounded int */
int
ez_round(double x);

/* round down

   parameters:
   double x: the double to round

   returns:
   int res: the rounded down int */
int
ez_floor(double x);

/* round up

   parameters:
   double x: the double to round

   returns:
   int res: the rounded up int */
int
ez_ceil(double x);

/* a simple iterative factorial implementation

   parameters:
   int x: the argument of x!

   returns:
   int res: the value of x!

   error:
   will return EZ_NAN if x < 0 */
int
ez_fact(int x);

/* combinations of r elements from a set of n; the binomial coefficients

   parameters:
   int n: the size of the parent set
   int r: the number of elements to choose for each combination

   returns:
   int res: the value of nCr(n, r) */
int
ez_nCr(int n, int r);

/* permutations of r elements from a set of n

   parameters:
   int n: the size of the parent set
   int r: the number of elements to choose for each permutation

   returns:
   int res: the value of nPr(n, r) */
int
ez_nPr(int n, int r);

/* a natural logarithm function

   parameters:
   double x: the argument to ln(x)
   double err: the maximum permissible error

   returns:
   double res: the value of ln(x), to within err

   error:
   will return EZ_NAN if x <= 0 */
double
ez_ln(double x, double err);

/* a general logarithm function base b

   parameters:
   double base: log_{base}
   double x: argument
   double err: maximum error allowed

   returns:
   double res: the value of log_{base} (x)

   error:
   will return EZ_NAN if base < 0 or x < 0 */
double
ez_log_b(double base, double x, double err);

/* a general exponential for integral exponents

   parameters:
   double base: the base for exponentiation
   int exp: the exponent

   returns:
   double res: the value of base^exp */
double
ez_int_exp_b(double base, int exp);

/* natural exponential function

   parameters:
   double x: argument to e^x
   double err: maximum error allowed

   returns:
   double res: the value of e^x */
double
ez_exp(double x, double err);

/* a general exponentiation function for double bases and exponents

   parameters:
   double base: the base for exponentiation
   double exp: the exponent
   double err: the maximum permissible error

   returns:
   double res: the value of base^exp, to within err

   error:
   will return EZ_NAN if base < 0
   only ez_int_exp_b will accept negative bases */
double
ez_exp_b(double base, double exp, double err);

/* a naive sine implementation using a Taylor polynomial

   parameters:
   double x: the angle argument to sin(x), in radians
   double err: the maximum permissible error for the result

   returns:
   double res: the value of sin(x), accurate to at least err */
double
ez_sin(double x, double err);

/* cosine

   parameters:
   double x: the argument to cos(x), radians
   double err: maximum allowable error

   returns:
   double res: the value of cos(x) */
double
ez_cos(double x, double err);

/* tangent

   parameters:
   double x: the argument to tan(x), radians
   double err: the error

   returns:
   double res: the value of tan(x)

   error:
   will return EZ_NAN if |x - pi/2| < err (once phase shifted) */
double
ez_tan(double x, double err);

/* inverse sine

   parameters:
   double x: the argument to asin(x)
   double err: the allowable error

   returns:
   double res: the value of asin(x)

   error:
   will return EZ_NAN if x is not in [-1, 1] */
double
ez_asin(double x, double err);

/* inverse cosine

   parameters:
   double x: the argument to acos(x)
   double err: the allowable error

   returns:
   double res: the value of acos(x)

   error:
   will return EZ_NAN if x is not in [-1, 1] */
double
ez_acos(double x, double err);

/* inverse tangent

   parameters:
   double x: the argument to atan(x)
   double err: the allowable error

   returns:
   double res: the value of atan(x) */
double
ez_atan(double x, double err);

/* square root

   parameters:
   double x: arg to sqrt(x)
   double err: max permissible error

   returns:
   double res: the value of sqrt(x)

   error:
   will return EZ_NAN if x < 0 */
double
ez_sqrt(double x, double err);

#endif
