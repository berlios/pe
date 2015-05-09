#ifndef BASE_DIGIT_MANIPULATION_H_
#define BASE_DIGIT_MANIPULATION_H_

#include <gmpxx.h>
#include <set>

typedef std::set<int> DigitSet;

DigitSet GetDigitSet(uint num);

uint DigitCount(const mpz_class &num);
uint DigitSum(const mpz_class &number);
mpz_class PlaceLastDigitInFront(const mpz_class &num);
mpz_class ReverseInBase(const mpz_class &num, uint base);
mpz_class Reverse(const mpz_class &num);
mpz_class DeleteFirstDigit(const mpz_class &num);
mpz_class DeleteLastDigit(const mpz_class &num);

#endif  // BASE_DIGIT_MANIPULATION_H_
