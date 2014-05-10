#include <gmpxx.h>
#include <string>

#include "base/task.h"
#include "gtest/gtest.h"

using std::string;

TASK(16) {
  mpz_class result;
  mpz_ui_pow_ui(result.get_mpz_t(), 2, 1000);  // Assignes 2^1000 to result.

  string digits = result.get_str();
  int sum_of_digits = 0;
  for (size_t i = 0; i < digits.size(); ++i) {
    sum_of_digits += digits[i] - '0';
  }

  SetResult(ToString(sum_of_digits));
}
