#include "qmath.h"
#include "math.h"

double
ez_qsqrt(double x)
{
  /* invalid and special values */
  if (x < 0)
    return EZ_NAN;
  if (x == 0)
    return 0;

  /* range reduction to [0, 4) */
  unsigned int v = (int) x;
  unsigned int k = 0;  /* will be log2(v) */
  while (v >>= 1) k++;
  unsigned int m = (1 << k);
  x /= (1 << 2*k);

  /* four iterations of Newton should be enough
     due to range reduction, just use initial guess res = x */
  const unsigned int iters = 4;
  double res = x;
  unsigned int i;
  for (i = 0; i < iters; i++)
    res = 0.5 * (res + x / res);
  return m * res;
}

double
ez_qsin(double x)
{
  /* range reduction to [-pi/2, pi/2] */
  x = ez_f_mod(x, EZ_2PI);
  if (x > EZ_PI)
    x -= EZ_2PI;
  if (x > EZ_PI/2)
    x = EZ_PI - x;
  if (x < -EZ_PI/2)
    x = -EZ_PI - x;

  /* Horner evaluation of fifth-degree Chebyshev polynomial */
  const double a1 =  0.999911528379604;
  const double a3 = -0.166020004258947;
  const double a5 =  0.007626662151178;
  double x2 = x * x;
  return x * (a1 + x2 * (a3 + x2 * a5));
}

double
ez_qcos(double x)
{
  /* cofunction with sine */
  return ez_qsin(EZ_PI/2 - x);
}

double
ez_qtan(double x)
{
  /* due to the asymptotes at +/- pi/2, it's faster to use the
     quotient identity with sine and cosine
     the NaN should propagate automatically if too close to asymptotes */
  return ez_qsin(x) / ez_qcos(x);
}

double
ez_qln(double x)
{
  /* we break x into several ranges with separate implementations */
  if (x <= 0)
    return EZ_NAN;
  if (x < 1)
    return -ez_qln(1 / x);  /* ln(1/x) = ln(1) - ln(x) = -ln(x) */
  if (x == 1)
    return 0;

  /* for x > 1, range reduction to [1, 2) using ln( 2^k b ) = k ln(2) + ln(b) */
  unsigned int v = (int) x;
  unsigned int k = 0;  /* will be log2(v) */
  while (v >>= 1) k++;
  double res = k * 0.69314718055994529;  /* this is ln(2) */
  x /= (1 << k);

  /* evaulate the fourth degree Chebyshev polynomial, err < 7e-5 */
  const double a4 = -0.05437093355557;
  const double a3 =  0.43393244200664;
  const double a2 = -1.44059216213207;
  const double a1 =  2.79283651560103;
  const double a0 = -1.73172644114354;
  return res + a0 + x * (a1 + x * (a2 + x * (a3 + x * a4)));
}

double
ez_qlog_b(double base, double x)
{
  /* change-of-base formula */
  if (x < 0 || base < 0)
    return EZ_NAN;
  return ez_qln(x) / ez_qln(base);
}

double
ez_int_qexp_b(double base, int exp)
{
  /* exponentiation by squaring, recursive for now */
  if (exp == 0)
    return 1;
  if (exp == 1)
    return base;
  if (exp % 2 == 0) {
    double tmp = ez_int_qexp_b(base, exp/2);
    return tmp * tmp;
  } else {
    double tmp = ez_int_qexp_b(base, (exp-1)/2);
    return base * tmp * tmp;
  }

}

/* TODO: actually implement this */
double
ez_qexp(double x)
{
  /* range reduction to [0, 1) */
  const double a4 = 0.0694155133774558;
  const double a3 = 0.140275036852553;
  const double a2 = 0.50977983530544;
  const double a1 = 0.998757050931838;
  const double a0 = 1.00002493721519;
  return a0 * a1 * a2 * a3 * a4;
}

double
ez_qfact(double x)
{
  /* by Stirling's approximation,
     gamma(n+1) ~ sqrt(2pi*n) * (n/e)^n = sqrt(2pi) sqrt(n) e^(n (ln(n) - 1))*/
  double res = ez_qsqrt(x) * 2.5066282746310002;  /* this is sqrt(2pi) */
  return res * ez_qexp(x * (ez_qln(x) - 1));
}
