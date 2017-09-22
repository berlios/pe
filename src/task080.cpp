#include <gmpxx.h>

#include "base/number_theory.h"
#include "base/task.h"

TASK(80) {
  int sum = 0;

  for (int i = 2; i <=100; ++i) {
    if (IsSquareNumber(i)) {
      continue;
    }

    mpf_class n(i, 640);
    n = sqrt(n);
    mp_exp_t dummy;
    for (char c : n.get_str(dummy).substr(0, 100)) {
      sum += c - '0';
    }
  }

  return sum;
}
