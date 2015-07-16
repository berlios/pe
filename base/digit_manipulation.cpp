#include "base/digit_manipulation.h"

#include "base/common.h"

DigitSet GetDigitSet(uint num) {
  DigitSet ret;

  while (num > 0) {
    ret.insert(num % 10);
    num = num / 10;
  }

  return ret;
}

uint NthDigit(const mpz_class &num, uint n) {
  return num.get_str()[n - 1] - '0';
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

bool Is1ToNPandigital(int64_t num) {
  return IsKToNPandigital(num, 1, std::to_string(num).size());
}

bool Is1To9Pandigital(int64_t num) {
  return IsKToNPandigital(num, 1, 9);
}

bool Is0To9Pandigital(int64_t num) {
  return IsKToNPandigital(num, 0, 9);
}

bool IsKToNPandigital(int64_t num, int k, int n) {
  if ((k < 0 || k > 9) || (n < 0 || n > 9) || k > n) {
    return false;
  }

  std::string expected_string;
  for (int i = k; i <= n; ++i) {
    expected_string.push_back('0' + i);
  }

  std::string num_str = std::to_string(num);
  std::sort(num_str.begin(), num_str.end());

  return expected_string == num_str;
};
