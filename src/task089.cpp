#include "base/common.h"
#include "base/macros.h"
#include "base/task.h"
#include "gtest/gtest.h"

namespace {
class RomanNumeralParser {
 public:
  RomanNumeralParser(std::string str)
      : str_(std::move(str)), index_(0), value_(0) {}
  int ParseValue() {
    while (index_ < str_.size()) {
      if (TryParseSingleNumeralWithSubtraction('I', 'V', 'X', 1)) {
        continue;
      }

      if (TryParseSingleNumeral('V', 5)) {
        continue;
      }

      if (TryParseSingleNumeralWithSubtraction('X', 'L', 'C', 10)) {
        continue;
      }

      if (TryParseSingleNumeral('L', 50)) {
        continue;
      }

      if (TryParseSingleNumeralWithSubtraction('C', 'D', 'M', 100)) {
        continue;
      }

      if (TryParseSingleNumeral('D', 500)) {
        continue;
      }

      TryParseSingleNumeral('M', 1000);
    }

    return value_;
  }

 private:
  bool TryParseSingleNumeral(char i, int value) {
    if (!IsCurrentChar(i)) {
      return false;
    }
    value_ += value;
    Advance();
    return true;
  }

  // The only expected values are:
  //   I V X 1
  //   X L C 10
  //   C D M 100
  bool TryParseSingleNumeralWithSubtraction(char i, char v, char x,
                                            int multiplier) {
    if (!IsCurrentChar(i)) {
      return false;
    }
    if (IsNextChar(v)) {
      value_ += 4 * multiplier;
      Advance(2);
    } else if (IsNextChar(x)) {
      value_ += 9 * multiplier;
      Advance(2);
    } else {
      value_ += 1 * multiplier;
      Advance();
    }
    return true;
  }

  void Advance() { index_++; }
  void Advance(int n) {
    CHECK(n >= 2);
    index_ += n;
  }
  bool IsCurrentChar(char c) { return str_[index_] == c; }
  bool IsNextChar(char c) {
    if ((index_ + 1) >= str_.size()) {
      return false;
    }
    if (str_[index_ + 1] == c) {
      return true;
    }
    return false;
  }
  std::string str_;
  size_t index_;
  int value_;
};

class RomanNumeral {
 public:
  RomanNumeral(int value) : remaining_value_(value) {}

  std::string GetString() {
    while (remaining_value_ > 0) {
      if (EmitIfGreater(1000, "M")) {
        continue;
      }
      if (EmitIfGreater(900, "CM")) {
        continue;
      }
      if (EmitIfGreater(500, "D")) {
        continue;
      }
      if (EmitIfGreater(400, "CD")) {
        continue;
      }
      if (EmitIfGreater(100, "C")) {
        continue;
      }
      if (EmitIfGreater(90, "XC")) {
        continue;
      }
      if (EmitIfGreater(50, "L")) {
        continue;
      }
      if (EmitIfGreater(40, "XL")) {
        continue;
      }
      if (EmitIfGreater(10, "X")) {
        continue;
      }
      if (EmitIfGreater(9, "IX")) {
        continue;
      }
      if (EmitIfGreater(5, "V")) {
        continue;
      }
      if (EmitIfGreater(4, "IV")) {
        continue;
      }
      EmitIfGreater(1, "I");
    }

    return str_;
  }

 private:
  bool EmitIfGreater(int threshold, const std::string& s) {
    if (remaining_value_ < threshold) {
      return false;
    }

    str_ += s;
    remaining_value_ -= threshold;
    return true;
  }

  std::string str_;
  int remaining_value_;
};

int RomanNumeralToInt(const std::string& s) {
  RomanNumeralParser parser(s);
  return parser.ParseValue();
}

std::string IntToMinimalRomanNumeral(int n) {
  RomanNumeral r(n);
  return r.GetString();
}
}

TEST(Task89, RomanNumeralToInt) {
  EXPECT_EQ(16, RomanNumeralToInt("XVI"));
  EXPECT_EQ(16, RomanNumeralToInt("XIIIIII"));
  EXPECT_EQ(19, RomanNumeralToInt("XIX"));
  EXPECT_EQ(49, RomanNumeralToInt("XXXXVIIII"));
  EXPECT_EQ(49, RomanNumeralToInt("XLIX"));
  EXPECT_EQ(1606, RomanNumeralToInt("MCCCCCCVI"));
  EXPECT_EQ(1606, RomanNumeralToInt("MDCVI"));
}

TEST(Task89, IntToMinimalRomanNumeral) {
  EXPECT_EQ("XVI", IntToMinimalRomanNumeral(16));
  EXPECT_EQ("XIX", IntToMinimalRomanNumeral(19));
  EXPECT_EQ("XLIX", IntToMinimalRomanNumeral(49));
  EXPECT_EQ("MDCVI", IntToMinimalRomanNumeral(1606));
}

TASK(89) {
  auto roman_numerals =
      Split(ReadFileIntoString("data/089_roman.txt"), '\n', SkipEmpty());

  int result = 0;
  for (const auto& numeral : roman_numerals) {
    std::string s = IntToMinimalRomanNumeral(RomanNumeralToInt(numeral));
    result += numeral.size() - s.size();
  }

  return result;
}
