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

class IsChar {
 public:
  IsChar(char c) : c_(c) { }
  bool operator()(char c) {
    return c == c_;
  }
 private:
  char c_;
};

std::vector<std::string> Split(const std::string &to_split, char delimiter) {
  std::vector<std::string> ret;

  size_t start = 0;
  size_t end = to_split.find_first_of(delimiter);

  while (end != std::string::npos) {
    ret.push_back(to_split.substr(start, end - start));
    start = end + 1;
    end = to_split.find_first_of(delimiter, start);
  }

  ret.push_back(to_split.substr(start));

  return ret;
}

std::string ReadFileIntoString(const std::string &filename) {
  std::ifstream t(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

