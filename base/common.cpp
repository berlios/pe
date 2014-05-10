#include "base/common.h"

#include <sstream>
#include <string>

std::string ToString(int n) {
  std::stringstream s;
  s << n;
  return s.str();
}

void DeleteLeadingChars(char c, std::string *str) {
  size_t pos = str->find_first_not_of(c);
  if (pos == std::string::npos) {
    pos = str->size();
  }

  str->assign(str->substr(pos));
}

void DeleteLeadingZeroes(std::string *str) {
  DeleteLeadingChars('0', str);
  if (str->size() == 0) {
    // If str contained only zeroes, one of them should be left.
    str->push_back('0');
  }
}
