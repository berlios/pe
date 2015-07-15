#ifndef BASE_COMMON_H_
#define BASE_COMMON_H_

#include <string>
#include <vector>

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

uint AlphabeticalValue(const std::string &word);
std::string ToString(int n);
void DeleteLeadingChars(char c, std::string *str);

// This function does not check the string to contain only digits.
// In fact, it doesn't check anything.
void DeleteLeadingZeroes(std::string *str);

std::vector<std::string> Split(const std::string &to_split, char delimiter);

void ReadFileIntoString(const std::string &filename, std::string *output);

#endif  // BASE_COMMON_H_
