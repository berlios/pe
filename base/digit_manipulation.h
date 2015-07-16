#ifndef BASE_DIGIT_MANIPULATION_H_
#define BASE_DIGIT_MANIPULATION_H_

#include <gmpxx.h>
#include <set>

typedef std::set<int> DigitSet;

DigitSet GetDigitSet(uint num);

uint NthDigit(const mpz_class &num, uint n);
uint DigitCount(const mpz_class &num);
uint DigitSum(const mpz_class &number);
mpz_class PlaceLastDigitInFront(const mpz_class &num);
mpz_class ReverseInBase(const mpz_class &num, uint base);
mpz_class Reverse(const mpz_class &num);
mpz_class DeleteFirstDigit(const mpz_class &num);
mpz_class DeleteLastDigit(const mpz_class &num);

// N can be devised from the number itself --- its length in base10.
bool Is1ToNPandigital(int64_t num);
bool Is1To9Pandigital(int64_t num);

// Leading zero does not count.
bool Is0To9Pandigital(int64_t num);

// Both ends are inclusive, e.g. IsKToNPandigital(1234, 1, 4) returns true.
bool IsKToNPandigital(int64_t num, int k, int n);

#endif  // BASE_DIGIT_MANIPULATION_H_
