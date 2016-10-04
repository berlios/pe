#include <gmpxx.h>

#include "base/digit_manipulation.h"
#include "base/task.h"
#include "gtest/gtest.h"

int GetFamilySizeUsingMask(const mpz_class& p, uint mask) {
  int digit_count = DigitCount(p);
  int family_size = 0;

  for (int digit = 0; digit < 10; ++digit) {
    uint mask_copy = mask;
    mpz_class r;
    mpz_class p_copy = p;
    mpz_class multiplier = 1;
    for (int i = 0; i < digit_count; ++i) {
      int last_bit = mask_copy % 2;
      if (last_bit == 1) {
        r += digit * multiplier;
      } else {
        r += (p_copy % 10) * multiplier;
      }

      multiplier *= 10;
      p_copy /= 10;
      mask_copy /= 2;
    }

    if (mpz_probab_prime_p(r.get_mpz_t(), 15) &&
        DigitCount(r) == DigitCount(p)) {
      family_size++;
    }
  }

  return family_size;
}

bool AreAllDigitsSameWithMask(const mpz_class& num, uint mask) {
  int digit;
  bool digit_is_set = false;
  mpz_class num_copy = num;

  for (int i = 0; i < DigitCount(num); ++i) {
    int last_bit = mask % 2;
    if (last_bit == 1) {
      if (!digit_is_set) {
        digit_is_set = true;
        digit = mpz_class(num_copy % 10).get_ui();
      } else {
        if (mpz_class(num_copy % 10).get_ui() != digit) {
          return false;
        }
      }
    }

    mask /= 2;
    num_copy /= 10;
  }

  return true;
}

mpz_class SmallestPrimeOfFamilySize(int family_size) {
  if (family_size >= 10) {
    return -1;
  }

  mpz_class prime = 2;
  while (true) {
    mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
    int digit_count = DigitCount(prime);

    for (uint mask = 0; mask < (1 << digit_count); ++mask) {
      if (GetFamilySizeUsingMask(prime, mask) == family_size &&
          AreAllDigitsSameWithMask(prime, mask)) {
        return prime;
      }
    }
  }
}

TEST(Task51, SmallestPrimeOfFamilySize) {
  EXPECT_EQ(6, GetFamilySizeUsingMask(13, 0b10));
  EXPECT_EQ(13, SmallestPrimeOfFamilySize(6));

  EXPECT_EQ(7, GetFamilySizeUsingMask(56003, 0b110));
  EXPECT_EQ(56003, SmallestPrimeOfFamilySize(7));

  EXPECT_TRUE(AreAllDigitsSameWithMask(56003, 0b110));
  EXPECT_FALSE(AreAllDigitsSameWithMask(120383, 0b101010));
}

TASK(51) {
  return SmallestPrimeOfFamilySize(8);
}
