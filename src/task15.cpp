#include <gmpxx.h>
#include <string>

#include "base/task.h"
#include "gtest/gtest.h"

using std::string;

TASK(15) {
  mpz_class result;
  mpz_bin_uiui(result.get_mpz_t(), 2*20, 20);
  SetResult(result.get_str());
}
