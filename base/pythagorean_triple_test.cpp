#include "base/pythagorean_triple.h"

#include <type_traits>

#include "gtest/gtest.h"

TEST(PythagoreanTriple, BasicTest) {
  using PPT = PrimitivePythagoreanTriple<int>;
  PPT triple;
  EXPECT_FALSE(triple.IsValid());
  EXPECT_EQ(PPT(0, 0, 0), triple);
  EXPECT_EQ(0, triple.a());
  EXPECT_EQ(0, triple.b());
  EXPECT_EQ(0, triple.c());

  triple = PPT(3, 4, 6);
  EXPECT_FALSE(triple.IsValid());
  EXPECT_EQ(PPT(0, 0, 0), triple);

  EXPECT_TRUE(triple.SetTriple(3, 4, 5));
  EXPECT_TRUE(triple.IsValid());
  EXPECT_EQ(PPT(3, 4, 5), triple);
  EXPECT_EQ(PPT(3, 5, 4), triple);
  EXPECT_EQ(PPT(4, 3, 5), triple);
  EXPECT_EQ(PPT(4, 5, 3), triple);
  EXPECT_EQ(PPT(5, 3, 4), triple);
  EXPECT_EQ(PPT(5, 4, 3), triple);
  EXPECT_EQ(3, triple.a());
  EXPECT_EQ(4, triple.b());
  EXPECT_EQ(5, triple.c());

  // Check that triple.b() is even.
  EXPECT_TRUE(triple.SetTriple(8, 15, 17));
  EXPECT_EQ(15, triple.a());
  EXPECT_EQ(8, triple.b());
  EXPECT_EQ(17, triple.c());
}

TEST(PythagoreanTriple, PriceTreeRepresentation) {
  using PPT = PrimitivePythagoreanTriple<int>;
  PPT t(8, 15, 17);

  EXPECT_EQ(PPT(21, 20, 29), t.PriceTree().LeftChild());
  EXPECT_EQ(PPT(55, 48, 73), t.PriceTree().MiddleChild());
  EXPECT_EQ(PPT(39, 80, 89), t.PriceTree().RightChild());

  t.SetTriple(3, 4, 5);
  EXPECT_EQ(PPT(35, 12, 37), t.PriceTree().LeftChild().MiddleChild());
}
