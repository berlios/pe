#include <gmpxx.h>
#include <map>

std::map<mpz_class, uint> Factorize(const mpz_class &number);
mpz_class SumOfAllDivisors(const mpz_class &number);
mpz_class SumOfProperDivisors(const mpz_class &number);
uint LengthOfRepeatingCycle(const mpq_class &fraction);
