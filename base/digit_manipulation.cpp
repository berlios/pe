#include "base/digit_manipulation.h"

DigitSet GetDigitSet(uint num) {
  DigitSet ret;

  while (num > 0) {
    ret.insert(num % 10);
    num = num / 10;
  }

  return ret;
}

uint DigitCount(const mpz_class &num) {
  uint k = 0;
  mpz_class power_of_ten = 1;

  while (num / power_of_ten > 0) {
    k++;
    power_of_ten *= 10;
  }

  return k;
}

uint DigitSum(const mpz_class &number) {
  mpz_class num = number;
  uint sum = 0;
  while (num != 0) {
    unsigned long digit = mpz_tdiv_q_ui(num.get_mpz_t(), num.get_mpz_t(), 10);
    sum += digit;
  }

  return sum;
};

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

mpz_class ReverseInBase(const mpz_class &num, uint base) {
  std::string str = num.get_str(base);
  std::reverse(str.begin(), str.end());

  return mpz_class(str, base);
}

mpz_class Reverse(const mpz_class &num) {
  return ReverseInBase(num, 10);
}

mpz_class DeleteFirstDigit(const mpz_class &num) {
  uint length = DigitCount(abs(num)) - 1;
  mpz_class tmp = 10;
  mpz_pow_ui(tmp.get_mpz_t(), tmp.get_mpz_t(), length);
  return num % tmp;
}

mpz_class DeleteLastDigit(const mpz_class &num) {
  return num / 10;
}

bool Is1To9Pandigital(const mpz_class &num) {
  if (num.get_str().size() != 9) {
    return false;
  }

  std::string str = num.get_str();
  std::sort(str.begin(), str.end());

  return str == "123456789";
}
