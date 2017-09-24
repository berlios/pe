#include <gmpxx.h>

#include "base/digit_manipulation.h"
#include "base/task.h"

TASK(20) {
  mpz_class factorial = 1;

  for (int i = 1; i <= 100; ++i) {
    factorial *= i;
  }

  return DigitSum(factorial);
}
