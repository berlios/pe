#include "base/common.h"

#include <string>
#include <vector>

#include "gtest/gtest.h"

using std::string;
using std::vector;

TEST(BaseCommon, AlphabeticalValue) {
  EXPECT_EQ(53u, AlphabeticalValue("COLIN"));
}

TEST(BaseCommon, ToString) {
  EXPECT_EQ("0", ToString(0));
  EXPECT_EQ("42", ToString(42));
  EXPECT_EQ("-4200", ToString(-4200));

  // Check INT_MAX. Unfortunately, compiler barks at -2147483648 as
  // it's unsigned only in ISO C90.
  EXPECT_EQ("2147483647", ToString(2147483647));
}

TEST(BaseCommon, DeleteLeadingChars) {
  string tmp = "aabca";
  DeleteLeadingChars('a', &tmp);
  EXPECT_EQ("bca", tmp);

  tmp = "aaaaaa";
  DeleteLeadingChars('a', &tmp);
  EXPECT_EQ("", tmp);

  tmp = "bacaaaaa";
  DeleteLeadingChars('a', &tmp);
  EXPECT_EQ("bacaaaaa", tmp);
}

TEST(BaseCommon, DeleteLeadingZeroes) {
  string tmp = "00345341";
  DeleteLeadingZeroes(&tmp);
  EXPECT_EQ("345341", tmp);

  tmp = "00";
  DeleteLeadingZeroes(&tmp);
  EXPECT_EQ("0", tmp);
}

TEST(BaseCommon, Split) {
  string str = ",0,11,222";
  vector<string> list = Split(str, ',');

  EXPECT_EQ(4u, list.size());
  EXPECT_EQ("", list[0]);
  EXPECT_EQ("0", list[1]);
  EXPECT_EQ("11", list[2]);
  EXPECT_EQ("222", list[3]);
}

TEST(BaseCommon, SplitSkipEmpty) {
  string str = "0,11,222,";
  vector<string> list = Split(str, ',', SkipEmpty());

  EXPECT_EQ(3u, list.size());
  EXPECT_EQ("0", list[0]);
  EXPECT_EQ("11", list[1]);
  EXPECT_EQ("222", list[2]);
}
