#include <algorithm>
#include <gmpxx.h>
#include <string>

#include "base/digit_manipulation.h"
#include "base/task.h"

TASK(41) {
  mpz_class last_pandigital_prime{0};

  // Let's go from 9 digit numbers down.
  for (int i = 9; i > 0; --i) {
    std::string str;
    for (int j = i; j > 0; --j) {
      str.push_back('0' + j);
    }

    auto greater = [](char a, char b) { return a > b; };

    do {
      mpz_class num{str};
      if (mpz_probab_prime_p(num.get_mpz_t(), 15) != 0) {
        last_pandigital_prime = num;
        break;
      }
    } while (std::next_permutation(str.begin(), str.end(), greater));

    if (last_pandigital_prime != 0) {
      break;
    }
  }

  return last_pandigital_prime;
}
