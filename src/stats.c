#include "stats.h"
#include "math.h"

double
ez_avg(double *x, int len)
{
  double sum = 0;
  int i;
  for (i = 0; i < len; i++)
    sum += x[i];
  return sum / len;
}

double
ez_stdev(double *x, int len)
{
  double avg = ez_avg(x, len);
  double devsq = 0;
  int i;
  for (i = 0; i < len; i++)
    devsq += (x[i] - avg) * (x[i] - avg);
  return ez_sqrt(devsq / (len - 1), 0.000001);
}

ez_linreg_result
ez_linreg(double *x, double *y, int xlen, int ylen)
{
  ez_linreg_result res;
  return res;
}

double
ez_erf(double x, double err)
{
  /* erf is odd */
  int s = +1;
  if (x < 0) s = -1;
  x = ez_f_abs(x);

  /* scale err to account for normalization at the end */
  double k = 1.1283791670955125739;  /* 2/sqrt(pi) */
  err /= k;

  /* Maclaurin series with alternating error term */
  double term = x;
  double i = 0;
  double sign = +1;
  double fact = 1;
  double pwr = x;
  double res = term;
  while (term > err) {
    i++;
    fact *= i;
    sign = -sign;
    pwr *= x * x;
    term = pwr / (fact * (2 * i + 1));
    res += sign * term;
  }

  /* normalize and return result */
  return s * k * res;
}

double
ez_normpdf(double x, double avg, double stdev, double err)
{
  double k = 0.39894228040143267794;  /* 1/sqrt(2pi) */
  double a = k / stdev;
  double z = (x - avg) / stdev;
  return a * ez_exp(z * z / -2.0, err / a);
}

double
ez_normcdf(double lo, double hi, double avg, double stdev, double err)
{
  /* find z-score and just use erf */
  double z_hi = (hi - avg) / stdev;
  double z_lo = (lo - avg) / stdev;
  double k = 0.7071067811865475244008; /* 1/sqrt(2) */
  return 0.5 * (ez_erf(k * z_hi, err) - ez_erf(k * z_lo, err));
}
