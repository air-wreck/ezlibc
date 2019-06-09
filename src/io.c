#include "io.h"
#include "syscalls.h"

int
ez_print(const char *msg, int len)
{
  const int stdout_fd = 1;
  return ez_sys_write(stdout_fd, msg, len);
}

int
ez_int_print(int n)
{
  /* for the special case of n == 0, just print 0 */
  if (n == 0) return ez_print("0", 1);

  /* our positive-forcing won't work for INT_MIN, so handle as special case */
  if (n < -2147483647) return ez_print("-2147483648", 11);

  /* handle sign separately */
  char *sign = "+";
  if (n < 0) sign = "-";
  n = n >= 0 ? n : -n;

  /* 2147483647, or ten digits, is the max size for signed 32-bit int */
  char digits[10] = {0};
  int i = 9;
  while (n > 0) {
    digits[i] = (n % 10) + 48;  /* convet num to ASCII representation */
    n /= 10;
    i--;
  }

  return ez_print(sign, 1) + ez_print(digits+i+1, 9-i);
}

int
ez_f_print(double n, int places)
{
  /* if places invalid, give an error */
  if (places < 0 || places > 9) return -1;

  /* handle 0 separately */
  if (n == 0.0) {
    int ret = ez_print("0.", 2);
    int i;
    for (i = 0; i < places; i++) {
      ret += ez_print("0", 1);
    }
    return ret;
  }

  /* for now, we assume that the double fits within an int
     that could be problematic later on */
  double abs_n = n >= 0.0 ? n : -n;
  int whole = (int) abs_n;
  int pwr_ten = 1;  /* power of ten to multiply fractional part */
  int i;
  for (i = 0; i < places; i++) {
    pwr_ten *= 10;
  }
  int frac = (int) ((abs_n - whole) * pwr_ten);

  /* to avoid sign on fractional part, do not call ez_int_print() */
  char digits[10] = {0};
  i = 9;
  while (frac > 0) {
    digits[i] = (frac % 10) + 48;  /* convet num to ASCII representation */
    frac /= 10;
    i--;
  }

  int ret = 0;
  if (abs_n < 1) {
    char *sign = "+";
    if (n < 0) sign = "-";
    ret += ez_print(sign, 1);
  }
  ret += ez_int_print((int) n);
  ret += ez_print(".", 1);
  ret += ez_print(digits+i+1, 9-i);
  return ret;
}

int
ez_str_print(const char *msg)
{
  int i = 0;
  while (msg[i] != 0) {
    ez_print(msg+i, 1);
    i++;
  }
  return i;
}

char
ez_getchar()
{
  const int stdin_fd = 0;
  char c;
  ez_sys_read(stdin_fd, &c, 1);
  return c;
}

int
ez_n_getstr(char *buf, int len)
{
  const int stdin_fd = 0;
  int n_bytes = ez_sys_read(stdin_fd, buf, len);
  buf[n_bytes] = EZ_NULL;
  return n_bytes;
}

int
ez_str10_to_int(const char *str10)
{
  /* detect presence of a +/- sign char */
  int sign;  /* sign +1/-1 */
  int start_index;  /* starting index of the actual numeric part */
  if (str10[0] == '+') {
    sign = 1;
    start_index = 1;
  } else if (str10[0] == '-') {
    sign = -1;
    start_index = 1;
  } else if (str10[0] >= 48 && str10[0] <= 57 ){
    /* check to see if the first char is numeric */
    sign = 1;
    start_index = 0;
  } else {
    /* the string is not a valid int */
    return -1;
  }

  /* get the length of the numeric part of the string */
  int len = 0;
  while (str10[start_index + len] != EZ_NULL) {
    /* check if this character is a valid integer */
    if (str10[start_index + len] < 48 || str10[start_index + len] > 57) {
      return -1;
    }
    len++;
  }

  /* loop through powers of ten and convert to int */
  int num = 0;
  int i;
  for (i = start_index; i < start_index + len; i++) {
    int pwr_ten = 1;
    int j;
    for (j = 0; j < len - i - 1 + start_index; j++) {
      pwr_ten *= 10;
    }
    num += pwr_ten * (str10[i] - 48);
  }

  return sign * num;
}
