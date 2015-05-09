#include <gmpxx.h>

#include "base/task.h"
#include "gtest/gtest.h"

mpz_class PlaceLastDigitInFront(const mpz_class &num) {
  if (num < 10 && num > -10) {
    return num;
  }

  mpz_class copy = num;
  uint last_digit = mpz_tdiv_q_ui(copy.get_mpz_t(), copy.get_mpz_t(), 10);

  mpz_class tmp = 10;
  uint size = mpz_class(abs(copy)).get_str().size();
  mpz_pow_ui(tmp.get_mpz_t(), tmp.get_mpz_t(), size);
  tmp *= last_digit;

  if (num >= 0) {
    copy += tmp;
  } else {
    copy -= tmp;
  }

  return copy;
}

TEST(Task35, PlaceLastDigitInFront) {
  EXPECT_EQ(0, PlaceLastDigitInFront(0));
  EXPECT_EQ(6, PlaceLastDigitInFront(6));
  EXPECT_EQ(24, PlaceLastDigitInFront(42));
  EXPECT_EQ(7456, PlaceLastDigitInFront(4567));
  EXPECT_EQ(-4765, PlaceLastDigitInFront(-7654));
  EXPECT_EQ(-9, PlaceLastDigitInFront(-9));
  EXPECT_EQ(-1, PlaceLastDigitInFront(-10));
  EXPECT_EQ(79, PlaceLastDigitInFront(97));
}

TASK(35) {
  mpz_class prime = 2;
  int circular_primes_count = 0;
  while (prime < 1000*1000) {
    mpz_class copy = prime;
    bool is_circular = true;
    for (int i = 0; i < mpz_sizeinbase(prime.get_mpz_t(), 10); ++i) {
      if (mpz_probab_prime_p(copy.get_mpz_t(), 20) == 0) {
        is_circular = false;
        break;
      }
      copy = PlaceLastDigitInFront(copy);
    }

    if (is_circular) {
      circular_primes_count++;
    }

    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
  }

  SetResult(ToString(circular_primes_count));
}
