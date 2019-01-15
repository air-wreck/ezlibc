/* ezlibc/qmath.h

basic math functions with pretty fast implementations,
but no guaranteed precision */

/* a fast (Newton) square root

   parameters:
   double x: the argument to sqrt(x)

   returns:
   double res: the approximate value of sqrt(x)

   error:
   will return EZ_NAN if x < 0 */
double
ez_qsqrt(double x);

/* a fast (Chebyshev polynomial) sine

   parameters:
   double x: the argument to sin(x), in radians

   returns:
   double res: the value of sin(x) */
double
ez_qsin(double x);

/* a fast cosine

   parameters:
   double x: the argument to cos(x), in radians

   returns:
   double res: the value of cos(x) */
double
ez_qcos(double x);

/* a fast tangent

   parameters:
   double x: the argument to tan(x), in radians

   returns:
   double res: the value of tan(x)

   error:
   should return EZ_NAN at asymptotes of tangent */
double
ez_qtan(double x);

/* a fast natural logarithm

   parameters:
   double x: the argument to ln(x)

   returns:
   double res: the value of ln(x)

   error:
   will return EZ_NAN if x < 0 */
double
ez_qln(double x);

/* a fast logarithm base b

   parameters:
   double base: logarithm base
   double x: logarithm argument

   returns:
   double res: the value of log_b(x)

   error:
   will return EZ_NAN if x < 0 or base < 0 */
double
ez_qlog_b(double base, double x);

/* fast exponentiation by an integral exponent

   parameters:
   double base: exponentiation base
   int exp: integral exponent

   returns:
   double res: the value of base^exp */
double
ez_int_qexp_b(double base, int exp);

/* a fast natural exponentiation

   parameters:
   double x: the argument to e^x

   returns:
   double res: the value of e^x */
double
ez_qexp(double x);

/* a fast gamma(n-1) function
   alternatively, a fast factorial approximation

   parameters:
   double x: the argument to gamma(n-1) = x!

   returns:
   double res: the value of gamma(n-1) = x! */
double
ez_qfact(double x);
