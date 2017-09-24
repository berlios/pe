#include <algorithm>
#include <string>

#include "base/task.h"
#include "gtest/gtest.h"

using std::remove_if;
using std::string;

string FormatDigit(int digit) {
  string str;
  switch (digit) {
    case 1: {
      str = "one";
      break;
    }
    case 2: {
      str = "two";
      break;
    }
    case 3: {
      str = "three";
      break;
    }
    case 4: {
      str = "four";
      break;
    }
    case 5: {
      str = "five";
      break;
    }
    case 6: {
      str = "six";
      break;
    }
    case 7: {
      str = "seven";
      break;
    }
    case 8: {
      str = "eight";
      break;
    }
    case 9: {
      str = "nine";
      break;
    }
    default: {
      str = "";
    }
  }
  return str;
}

string FormatTensByHighestDigit(int n) {
  string str;

  switch (n) {
    case 2: {
      str = "twenty";
      break;
    }
    case 3: {
      str = "thirty";
      break;
    }
    case 4: {
      str = "forty";
      break;
    }
    case 5: {
      str = "fifty";
      break;
    }
    case 6: {
      str = "sixty";
      break;
    }
    case 7: {
      str = "seventy";
      break;
    }
    case 8: {
      str = "eighty";
      break;
    }
    case 9: {
      str = "ninety";
      break;
    }
    default: {
      str = "";
    }
  }
  return str;
}

// This function is guaranteed to work only for numbers 1 to 1000.
void FormatInteger(int n, string *str) {
  str->clear();

  if (n < 1 || n > 1000) {
    *str = "";
    return;
  }

  if (n == 1000) {
    *str = "one thousand";
    return;
  }

  if (n/100 > 0) {
    str->append(FormatDigit(n/100));
    str->append(" hundred");
    if (n%100 != 0) {
      str->append(" and ");
    }
  }

  n = n%100;
  if (n/10 >= 2) {
    str->append(FormatTensByHighestDigit(n/10));
    if (n%10 != 0) {
      str->append("-");
    }
  }

  if (n/10 != 1) {
    if (n%10 != 0) {
      str->append(FormatDigit(n%10));
    }
  } else {
    switch (n) {
      case 10: {
        str->append("ten");
        break;
      }
      case 11: {
        str->append("eleven");
        break;
      }
      case 12: {
        str->append("twelve");
        break;
      }
      case 13: {
        str->append("thirteen");
        break;
      }
      case 14: {
        str->append("fourteen");
        break;
      }
      case 15: {
        str->append("fifteen");
        break;
      }
      case 16: {
        str->append("sixteen");
        break;
      }
      case 17: {
        str->append("seventeen");
        break;
      }
      case 18: {
        str->append("eighteen");
        break;
      }
      case 19: {
        str->append("nineteen");
        break;
      }
    }
  }
}

TEST(Task17, FormatInteger) {
  string str;
  FormatInteger(1, &str);
  EXPECT_EQ("one", str);

  FormatInteger(15, &str);
  EXPECT_EQ("fifteen", str);

  FormatInteger(21, &str);
  EXPECT_EQ("twenty-one", str);

  FormatInteger(32, &str);
  EXPECT_EQ("thirty-two", str);

  FormatInteger(40, &str);
  EXPECT_EQ("forty", str);

  FormatInteger(87, &str);
  EXPECT_EQ("eighty-seven", str);

  FormatInteger(114, &str);
  EXPECT_EQ("one hundred and fourteen", str);

  FormatInteger(342, &str);
  EXPECT_EQ("three hundred and forty-two", str);

  FormatInteger(1000, &str);
  EXPECT_EQ("one thousand", str);
}

class CharacterIsEqualTo {
 public:
  explicit CharacterIsEqualTo(char c) : c_(c) { }
  bool operator()(char c) {
    return c == c_;
  }
 private:
  char c_;
};

TASK(17) {
  string result;
  for (int i = 1; i <= 1000; ++i) {
    string number_in_words;
    FormatInteger(i, &number_in_words);
    string::iterator it = remove_if(number_in_words.begin(),
                                    number_in_words.end(),
                                    CharacterIsEqualTo(' '));

    it = remove_if(number_in_words.begin(), it,
                   CharacterIsEqualTo('-'));
    number_in_words.erase(it, number_in_words.end());

    result += number_in_words;
  }

  return result.size();
}
