#include "math.h"

int
ez_int_abs(int x)
{
  /* this might break for INT_MIN */
  int mask = x >> 31;
  x ^= mask;
  return x - mask;
}

double
ez_f_abs(double x)
{
  /* bitwise is too Chinese for doubles
     this should work for reasonable doubles */
  return x >= 0 ? x : -1.0 * x;
}

int
ez_round(double x)
{
  double y = ez_f_abs(x);
  int sign = 1;
  if (x < 0) sign = -1;
  int res = (int) (y + 0.5);
  return sign * res;
}

int
ez_floor(double x)
{
  if (x >= 0) return (int) x;
  return (int) x - 1;
}

int
ez_ceil(double x)
{
  if (x >= 0) return (int) x + 1;
  return (int) x;
}

int
ez_fact(int x)
{
  if (x < 0)
    return EZ_NAN;

  int res = 1;
  int n;
  for (n = 1; n <= x; n++)
    res *= n;
  return res;
}

int
ez_nCr(int n, int r)
{
  return ez_fact(n) / (ez_fact(r) * ez_fact(n-r));
}

int
ez_nPr(int n, int r)
{
  return ez_fact(n) / ez_fact(n-r);
}

double
ez_ln(double x, double err)
{
  /* check if x is valid */
  if (x <= 0) return EZ_NAN;

  /* we will handle 1 separately */
  if (x == 1) return 0;

  /* for x > 2, use ln(ab) = ln(a) + ln(b) to reduce argument */
  double res = 0;
  while (x >= 2) {
    res += 0.69314718056;  /* this is ln(2) */
    x /= 2.0;
  }

  /* now that 0 <= x < 2, we can use the Taylor polynomial
     for convenience, we first re-center the series at 0
     the error is bounded by the next term in the series expansion */
  double a = x - 1;
  double term = a;
  int n = 1;
  while (term / (double) n > err) {
    if (n % 2 == 1) res += term / (double) n;
    else res -= term / (double) n;
    n++;
    term *= a;
  }
  return res;
}

double
ez_log_b(double base, double x, double err)
{
  if (base < 0 || x < 0)
    return EZ_NAN;

  /* use the change-of-base formula with ez_ln()
     we need to improve the accuracy of ez_ln() to account for err
     do this until the possible error range is within err */
  double err0 = err;
  double n;
  double d;
  do {
    n = ez_ln(x, err);
    d = ez_ln(base, err);
    err /= 10;
  } while ((n+err)/(d-err) - (n-err)/(d+err) > err0);
  return n / d;
}

double
ez_int_exp_b(double base, int exp)
{
  /* n^0 = 1 */
  if (exp == 0) return 1;

  /* first compute base^|exp| */
  double res = base;
  unsigned int tmp_exp = ez_f_abs(exp);
  unsigned int i;
  for (i = 1; i < tmp_exp; i++) {
    res *= base;
  }

  /* if exp < 0, then base^exp = 1 / base^|exp| */
  if (exp < 0) res = 1 / res;

  return res;
}

double
ez_exp(double x, double err)
{
  /* we first compute e^|x| and then apply negative if need be at the end */
  double y = ez_f_abs(x);

  /* do a range reduction to 0 <= y < 1 using:
     e^x = e^(k+y) = e^k e^y = m e^y, if k is integral, e^k is exact */
  unsigned int k = (int) y;
  y -= k;
  double m = ez_int_exp_b(EZ_E, k);
  err /= m;  /* make sure we don't compound error */

  /* we can use the Taylor polynomial with the Lagrange error term
     there exists some 0 < z < y such that e^z is the error coefficient
     we can just take e > e^y as an overestimation of the error coeff. */
  double res = 1;
  unsigned int deg = 1;
  double term = y;
  while (EZ_E * term * y / (double) deg > err) {
    res += term;
    deg++;
    term *= y / (double) deg;
  }
  res = m * (res + term);

  /* if x is negative, we have e^x = 1/e^|x| = 1/e^y */
  if (x < 0) return 1.0 / res;
  return res;
}

double
ez_exp_b(double base, double exp, double err)
{
  /* if base < 0, this is undefined for real exponents */
  if (base < 0)
    return EZ_NAN;

  /* if 0 < base < 1, use (1/a)^b = 1/(a^b) = a^(-b)
     potentially investigate error compounding? */
  if (base < 1) {
    base = 1 / base;
    exp = -exp;
  }

  /* we use the simple equality that a^b = e^(b*ln(a)); since we have
     series expansions for e^x and ln(x), we can easily compute this
     we just need to be careful not to compound error beyond the bounds
     we use the same general error correction algorithm as ez_log_b */
  double err0 = err;
  double pwr_lo;
  double pwr_hi;
  double ln;
  double exp_hi;
  double exp_lo;
  do {
    ln = ez_ln(base, err);
    pwr_lo = exp * (ln - err);
    pwr_hi = exp * (ln + err);
    exp_lo = ez_exp(pwr_lo, err) - err;
    exp_hi = ez_exp(pwr_hi, err) + err;
    err /= 10;
  } while (exp_hi - exp_lo > err0);
  double pwr = exp * ez_ln(base, err);
  return ez_exp(pwr, err);
}

double
ez_sin(double x, double err)
{
  /* to make life easier, use y = |x|, since sin(-x) = -sin(x)
     just don't forget to check sign at the end */
  double y = ez_f_abs(x);

  /* do a range reduction on y to make 0 <= y <= pi/2
     we can do better with log_{2pi} (x) later, but just loop for now */
  while (y > 2 * EZ_PI) {
    y -= 2.0 * EZ_PI;
  }

  /* y is in the unit circle, now get in first quadrant */
  int sign = 1;
  if (y > EZ_PI / 2.0 && y <= EZ_PI) {
    y = EZ_PI - y;
  } else if (y > EZ_PI && y < 3.0 * EZ_PI / 2.0) {
    y -= EZ_PI;
    sign = -1;
  } else if (y > 3.0 * EZ_PI / 2.0) {
    y = 2.0 * EZ_PI - y;
    sign = -1;
  }

  /* compute the Taylor polynomial of sine
     use the next term as the bounds for the error */
  double term = y;
  double res = term;
  int i = 0;
  while (term > err) {
    double fact = (double) ((2*i+2) * (2*i+3));
    term *= y * y / fact;
    if (i % 2 == 0) res -= term;
    else res += term;
    i++;
  }

  if (x < 0) res *= -1.0;
  return sign * res;
}

double
ez_cos(double x, double err)
{
  /* we can just use a cofunction identity with sine */
  return ez_sin(EZ_PI / 2.0 - x, err);
}

double
ez_tan(double x, double err)
{
  /* we can exploit the symmetry tan(-x) = -tan(x) */
  double y = ez_f_abs(x);

  /* do a range reduction to 0 <= y <= pi/2 */
  while (y > EZ_PI) {
    y -= EZ_PI;
  }
  int sign = 1;
  if (y > EZ_PI / 2) {
    y = EZ_PI - y;
    sign = -1;
  }

  /* handle the special case, to within the given error tolerance */
  if (EZ_PI / 2 - y < err) {
    return EZ_NAN;
  }

  /* keep on computing more accurate sin and cos estimates until they are good
     enough to use trig identities to compute tan
     actually, we can make this way faster by directly adding to the series
     expansions rather than recomputing each time, but whatever */
  double err0 = err;
  double s;
  double c;
  do {
    s = ez_sin(y, err);
    c = ez_cos(y, err);
    err /= 10;
  } while ((s+err)/(c-err) - (s-err)/(c+err) > err0);
  double res = s / c;

  if (x < 0) res *= -1;
  return sign * res;
}

double
ez_asin(double x, double err)
{
  /* symmetry --- asin(x) is odd */
  double y = ez_f_abs(x);

  /* reject out-of-range */
  if (y > 1)
    return EZ_NAN;

  /* if within error of 1, return pi/2
     that's probably the wrong bounds, but oh well */
  if (1 - y < err) {
    if (x < 0) return -EZ_PI / 2;
    return EZ_PI / 2;
  }

  /* use the identity asin(x) = atan( x / sqrt(1-x^2) )
     again naively correcting for compounded error */
  double err0 = err;
  double sqrt_lo;
  double sqrt_hi;
  double sqrt;
  double atan_lo;
  double atan_hi;
  do {
    sqrt = ez_sqrt(1 - y*y, err);
    sqrt_lo = sqrt - err;
    sqrt_hi = sqrt + err;
    atan_lo = ez_atan(y / sqrt_hi, err) - err;
    atan_hi = ez_atan(y / sqrt_lo, err) + err;
    err /= 10;
  } while (atan_hi - atan_lo > err0);

  double res = ez_atan(y / ez_sqrt(1 - y*y, err), err);
  if (x < 0) res = -res;
  return res;
}

double
ez_acos(double x, double err)
{
  /* trig identities to the rescue! */
  return -ez_asin(x, err) + EZ_PI / 2;
}

double
ez_atan(double x, double err)
{
  /* symmetry: atan(-x) = -atan(x) */
  double y = ez_f_abs(x);

  /* if x > 1, use pi/2 - atan(1/x) = atan(x) */
  int flip = 0;
  if (y > 1) {
    flip = 1;
    y = 1 / y;
  }

  /* if x is within the given error of 1, just return pi/4 */
  if (1 - y < err)
    return EZ_PI / 4;

  /* do a Maclaurin series with alternating error terms */
  double term = y;
  double res = term;
  int deg = 1;
  int sign = +1;
  double pwr = y;  /* keeping a running power is cheaper */
  while (term > err) {
    deg += 2;
    sign = -sign;
    pwr *= y*y;
    term = pwr / deg;
    res += sign * term;
  }

  if (flip) res = EZ_PI / 2 - res;
  if (x < 0) return -res;
  return res;
}

double  /* consider a faster implementation (e.g. Newton, digit-by-digit) */
ez_sqrt(double x, double err)
{
  /* handle special values */
  if (x < 0)
    return EZ_NAN;
  if (x == 0)
    return 0;

  /* reduce argument x to 0 <= y < 4 by finding an even exponent 2k and using:
     sqrt(x) = sqrt( 2^(2k) * y ) = 2^k * sqrt(y)
     this technique is taken from the OpenJDK implementation */
  unsigned int m = 1;
  while (x > 4) {
    x /= 4;
    m <<= 1;
  }

  /* now the error is really 2^k * err, so we need to use err = err0 / 2^k */
  return m * ez_exp_b(x, 0.5, err / m);
}
