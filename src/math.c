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
  while (x > 2) {
    res += 0.69314718056;  /* this is ln(2) */
    x /= 2.0;
  }

  /* now that 0 < x <= 2, we can use the Taylor polynomial
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
  /* use the change-of-base formula with ez_ln()
     we need to improve the accuracy of ez_ln() to account for err
     do this until the possible error range is within err */
  double err0 = err;
  double n = ez_ln(x, err);
  double d = ez_ln(base, err);
  while ((n+err)/(d-err) - (n-err)/(d+err) > err0) {
    err /= 10;
    n = ez_ln(x, err);
    d = ez_ln(base, err);
  }
  return n / d;
}

double
ez_int_exp_b(double base, int exp)
{
  /* n^0 = 1 */
  if (exp == 0) return 1;

  /* first compute base^|exp| */
  double res = base;
  int tmp_exp = ez_f_abs(exp);
  int i;
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

  /* we can use the Taylor polynomial with the Lagrange error term
     there exists some 0 < z < y such that e^z is the error coefficient
     we can just take e^ceil(y) as an overestimation of the error */
  double err_coeff = ez_int_exp_b(EZ_E, ez_ceil(y));
  double res = 1;
  int deg = 1;
  double term = y;
  while (err_coeff * term * y / (double) deg > err) {
    res += term;
    deg++;
    term *= y / (double) deg;
  }

  /* if x is negative, we have e^x = 1/e^|x| = 1/e^y */
  if (x < 0) return 1.0 / res;
  return res;
}

double
ez_exp_b(double base, double exp, double err)
{
  /* we use the simple equality that a^b = e^(b*ln(a)); since we have
     series expansions for e^x and ln(x), we can easily compute this
     we just need to be careful not to compound error beyond the bounds
     we use the same general error correction algorithm as ez_log_b */
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

int
ez_alt_permu(int n)
{
  /* implement memoization later */
  if (n == 0 || n == 1) return 1;

  int sum = 0;
  for (int k = 0; k < n; k++)
    sum += ez_nCr(n-1, k) * ez_alt_permu(k) * ez_alt_permu(n-1-k);
  return sum / 2;
}

double /* FIX - implement lagrange */
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

  /* handle the special case, to a certain tolerance */
  double tolerance = 0.00000001;
  if (EZ_PI / 2 - y < tolerance) {
    return EZ_NAN;
  }

  /* we use the Maclaurin series
     this is because the precision is not guaranteed with trig identities
     here, we use the Lagrange error term
     there is some term 0 < z < y such that tan(z) is the error term */
  double term = y;
  double res = term;
  int i = 1;
  while (term > err) {
    i += 2;
    term = ez_alt_permu(i) * ez_int_exp_b(y, i) / ez_fact(i);
    res += term;
  }

  if (x < 0) res *= -1;
  return sign * res;
}

double
ez_sqrt(double x, double err)
{
  return ez_exp_b(x, 0.5, err);
}
