#include "base/digit_manipulation.h"

#include "gtest/gtest.h"

TEST(DigitManipulation, DigitSet) {
  DigitSet digits = GetDigitSet(12344);
  ASSERT_EQ(4, digits.size());
  EXPECT_NE(digits.end(), digits.find(1));
  EXPECT_NE(digits.end(), digits.find(2));
  EXPECT_NE(digits.end(), digits.find(3));
  EXPECT_NE(digits.end(), digits.find(4));

  EXPECT_EQ(4, DigitCount(4067));
}

TEST(DigitManipulation, NthDigit) {
  EXPECT_EQ(5, NthDigit(145, 3));
}

TEST(DigitManipulation, DigitSum) {
  mpz_class a;
  a = "1234567890";
  EXPECT_EQ(45, DigitSum(a));
}

TEST(DigitManipulation, PlaceLastDigitInFront) {
  EXPECT_EQ(0, PlaceLastDigitInFront(0));
  EXPECT_EQ(6, PlaceLastDigitInFront(6));
  EXPECT_EQ(24, PlaceLastDigitInFront(42));
  EXPECT_EQ(7456, PlaceLastDigitInFront(4567));
  EXPECT_EQ(-4765, PlaceLastDigitInFront(-7654));
  EXPECT_EQ(-9, PlaceLastDigitInFront(-9));
  EXPECT_EQ(-1, PlaceLastDigitInFront(-10));
  EXPECT_EQ(79, PlaceLastDigitInFront(97));
}

TEST(DigitManipulation, Reverse) {
  EXPECT_EQ(0, Reverse(0));
  EXPECT_EQ(6, Reverse(6));
  EXPECT_EQ(45689, Reverse(98654));

  // 585 in base 10 = 1001001001 in base 2.
  EXPECT_EQ(585, ReverseInBase(585, 2));
}

TEST(DigitManipulation, DeleteFirstAndLastDigits) {
  EXPECT_EQ(0, DeleteLastDigit(7));
  EXPECT_EQ(0, DeleteLastDigit(-3));

  EXPECT_EQ(4567, DeleteLastDigit(45678));
  EXPECT_EQ(-4567, DeleteLastDigit(-45673));
  EXPECT_EQ(-4567, DeleteLastDigit(-45678));

  EXPECT_EQ(0, DeleteFirstDigit(7));
  EXPECT_EQ(0, DeleteFirstDigit(-3));

  EXPECT_EQ(5678, DeleteFirstDigit(45678));
  EXPECT_EQ(-5678, DeleteFirstDigit(-45678));
}

TEST(DigitManipulation, Pandigital) {
  EXPECT_TRUE(Is1To9Pandigital(123456789));
  EXPECT_TRUE(Is1To9Pandigital(987654321));
  EXPECT_TRUE(Is1To9Pandigital(657491832));
  EXPECT_FALSE(Is1To9Pandigital(1234567890));
  EXPECT_FALSE(Is1To9Pandigital(1123456789));

  EXPECT_TRUE(Is1ToNPandigital(2143));

  EXPECT_TRUE(Is0To9Pandigital(1406357289));
  EXPECT_FALSE(Is0To9Pandigital(123456789));
  EXPECT_FALSE(Is0To9Pandigital(12345678900));

  EXPECT_TRUE(IsKToNPandigital(1234, 1, 4));
  EXPECT_FALSE(IsKToNPandigital(1234, 0, 4));
}
