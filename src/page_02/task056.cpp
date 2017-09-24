#include <algorithm>
#include <gmpxx.h>

#include "base/digit_manipulation.h"
#include "base/task.h"

TASK(56) {
  uint max_digit_sum = 0;
  for (int i = 1; i < 100; ++i) {
    for (int j = 1; j < 100; ++j) {
      mpz_class num;
      mpz_ui_pow_ui(num.get_mpz_t(), i, j);
      max_digit_sum = std::max(max_digit_sum, DigitSum(num));
    }
  }

  return max_digit_sum;
}
