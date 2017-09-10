#include "base/common.h"

#include <algorithm>
#include <fstream>
#include <sstream>

uint AlphabeticalValue(const std::string &word) {
  uint score = 0;
  for (size_t i = 0; i < word.size(); ++i) {
    score += word[i] - 'A' + 1;
  }

  return score;
}


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

std::string ReadFileIntoString(const std::string &filename) {
  std::ifstream t(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

