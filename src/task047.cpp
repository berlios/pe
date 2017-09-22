#include "base/number_theory.h"
#include "base/task.h"

int NumberOfPrimeDivisors(int n) {
  static const std::vector<int> prime_list = Sieve(200*1000);

  int count = 0;
  for (auto prime : prime_list) {
    if (n % prime == 0) {
      count++;
      while (n % prime == 0) {
        n /= prime;
      }
    }

    if (n == 1) {
      break;
    }
  }

  return count;
}

TASK(47) {
  int count = 0;
  for (int i = 2;; ++i) {
    if (NumberOfPrimeDivisors(i) == 4) {
      count++;
    } else {
      count = 0;
    }

    if (count == 4) {
      return i - 3;
    }
  }
}
