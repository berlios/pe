#include "base/number_theory.h"

#include "gtest/gtest.h"

TEST(NumberTheory, Sieve) {
  std::vector<int> prime_list{2, 3, 5, 7, 11, 13, 17, 19, 23};
  EXPECT_NE(prime_list, Sieve(23));
  EXPECT_EQ(prime_list, Sieve(24));

  EXPECT_EQ(prime_list, Sieve(29));
  EXPECT_NE(prime_list, Sieve(30));
}

TEST(NumberTheory, NumberOfPrimeDivisors) {
  EXPECT_EQ(1, NumberOfPrimeDivisors(2));
  EXPECT_EQ(1, NumberOfPrimeDivisors(4));
  EXPECT_EQ(1, NumberOfPrimeDivisors(16));

  EXPECT_EQ(2, NumberOfPrimeDivisors(15));
  EXPECT_EQ(2, NumberOfPrimeDivisors(45));

  EXPECT_EQ(3, NumberOfPrimeDivisors(644));
  EXPECT_EQ(3, NumberOfPrimeDivisors(645));
  EXPECT_EQ(3, NumberOfPrimeDivisors(646));
}

TEST(NumberTheory, SumOfDivisors) {
  mpz_class a = 8;
  EXPECT_EQ(15, SumOfAllDivisors(a));
  EXPECT_EQ(7, SumOfProperDivisors(a));

  a = 24;
  EXPECT_EQ(60, SumOfAllDivisors(a));
  EXPECT_EQ(36, SumOfProperDivisors(a));

  a = 3;
  EXPECT_EQ(4, SumOfAllDivisors(a));
  EXPECT_EQ(1, SumOfProperDivisors(a));
}

TEST(NumberTheory, Numbers220And284AreAmicable) {
  EXPECT_EQ(284, SumOfProperDivisors(220));
  EXPECT_EQ(220, SumOfProperDivisors(284));
}

TEST(NumberTheory, LengthOfRepeatingCycle) {
  EXPECT_EQ(0u, LengthOfRepeatingCycle(mpq_class(1, 2)));
  EXPECT_EQ(1u, LengthOfRepeatingCycle(mpq_class(1, 3)));
  EXPECT_EQ(0u, LengthOfRepeatingCycle(mpq_class(7, 14)));
  EXPECT_EQ(6u, LengthOfRepeatingCycle(mpq_class(1, 7)));
  EXPECT_EQ(6u, LengthOfRepeatingCycle(mpq_class(21, 49)));
  EXPECT_EQ(16u, LengthOfRepeatingCycle(mpq_class(1, 17)));
}

TEST(NumberTheory, TriangleNumbers) {
  EXPECT_EQ(1, NthTriangleNumber(1));
  EXPECT_EQ(10, NthTriangleNumber(4));
  EXPECT_EQ(55, NthTriangleNumber(10));

  EXPECT_TRUE(IsTriangleNumber(45));
  EXPECT_TRUE(IsTriangleNumber(55));
  EXPECT_FALSE(IsTriangleNumber(54));
  EXPECT_FALSE(IsTriangleNumber(65));
}

TEST(NumberTheory, PentagonalNumbers) {
  EXPECT_EQ(1, NthPentagonalNumber(1));
  EXPECT_EQ(22, NthPentagonalNumber(4));
  EXPECT_EQ(117, NthPentagonalNumber(9));

  EXPECT_TRUE(IsPentagonalNumber(35));
  EXPECT_TRUE(IsPentagonalNumber(145));
  EXPECT_TRUE(IsPentagonalNumber(1));
  EXPECT_FALSE(IsPentagonalNumber(2));

  EXPECT_FALSE(IsPentagonalNumber(50));
  EXPECT_TRUE(IsPentagonalNumber(51));
  EXPECT_FALSE(IsPentagonalNumber(52));
}

TEST(NumberTheory, GDC) {
  EXPECT_EQ(6, GCD(24, 18));
  EXPECT_EQ(1, GCD(24, 1234567891));
  EXPECT_EQ(3, GCD(3, 24));
  EXPECT_EQ(2, GCD(mpz_class(24), mpz_class(50)));
}

TEST(NumberTheory, Quadratic) {
  Quadratic<int> f;
  EXPECT_EQ(0, f(0));
  EXPECT_EQ(0, f(1));
  EXPECT_EQ(0, f(42));
  EXPECT_EQ(0, f(-42));

  // Set f(x) = x^2 + 2x + 1.
  f.SetCoefficients(1, 2, 1);
  EXPECT_EQ(1, f(0));
  EXPECT_EQ(4, f(1));
  EXPECT_EQ(43*43, f(42));
  EXPECT_EQ(41*41, f(-42));

  f = Quadratic<int>(-1, -3, 2);
  EXPECT_EQ(2, f(0));
  EXPECT_EQ(-1 - 3 + 2, f(1));
  EXPECT_EQ(-42*42 - 3*42 + 2, f(42));
  EXPECT_EQ(-42*42 + 3*42 + 2, f(-42));
  
  f.set_a(5);
  EXPECT_EQ(5, f.a());

  f.set_b(7);
  EXPECT_EQ(7, f.b());

  f.set_c(9);
  EXPECT_EQ(9, f.c());

  EXPECT_EQ(Quadratic<int>(5, 7, 9), f);
}
