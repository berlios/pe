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
