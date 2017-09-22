#include <gmpxx.h>
#include <vector>

#include "base/number_theory.h"
#include "base/task.h"

TASK(78) {
  std::vector<mpz_class> partition_numbers = {1, 1};
  for (int n = partition_numbers.size();; ++n) {
    mpz_class next_partition_number;

    int sign = 1;
    for (int i = 1; ; ++i) {
      int k = NthPentagonalNumber(i).get_si();
      if (k > n) {
        break;
      }
      next_partition_number += sign * partition_numbers[n - k];
      sign = -sign;
    }

    sign = 1;
    for (int i = -1; ; --i) {
      int k = NthPentagonalNumber(i).get_si();
      if (k > n) {
        break;
      }
      next_partition_number += sign * partition_numbers[n - k];
      sign = -sign;
    }

    if (next_partition_number % (1000 * 1000) == 0) {
      return n;
    }

    partition_numbers.push_back(next_partition_number);
  }
}
