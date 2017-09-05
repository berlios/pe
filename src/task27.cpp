#include <gmpxx.h>

#include "base/number_theory.h"
#include "base/task.h"
#include "gtest/gtest.h"

uint LengthOfPrimeSequence(const Quadratic<mpz_class> &f) {
  uint res = 0;

  while (mpz_probab_prime_p(f(res).get_mpz_t(), 15) != 0) {
    res++;
  }

  return res;
}

TEST(Task27, LengthOfPrimeSequence) {
  Quadratic<mpz_class> f(1, -79, 1601);
  EXPECT_EQ(80u, LengthOfPrimeSequence(f));
}

TASK(27) {
  Quadratic<mpz_class> f, res;
  uint max_prime_sequence_length = 0;

  for (int a = -999; a < 1000; ++a) {
    for (int b = -999; b < 1000; ++b) {
      f.SetCoefficients(1, a, b);
      uint current_prime_sequence_length = LengthOfPrimeSequence(f);
      if (current_prime_sequence_length > max_prime_sequence_length) {
        max_prime_sequence_length = current_prime_sequence_length;
        res = f;
      }
    }
  }

  mpz_class answer = res.b()*res.c();
  return answer;
}
