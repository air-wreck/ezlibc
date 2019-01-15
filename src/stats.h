/* ezlibc/qmath.h

basic stats functions  */

#ifndef EZ_STATS_
#define EZ_STATS_

/** basic one-variable statistics **/
double
ez_avg(double *x, int len);

double
ez_stev(double *x, int len);


/** regressions **/
typedef struct {
  double a;
  double b;
  double r;
  double rsq;
} ez_linreg_result;

ez_linreg_result
ez_linreg(double *x, double *y, int xlen, int ylen);


/** distributions **/
double
ez_erf(double x, double err);

double
ez_normpdf(double x, double avg, double stdev, double err);

double
ez_normcdf(double lo, double hi, double avg, double stdev, double err);


#endif
