#ifndef BASE_COMMON_H_
#define BASE_COMMON_H_

#include <string>
#include <vector>

uint AlphabeticalValue(const std::string &word);
std::string ToString(int n);
void DeleteLeadingChars(char c, std::string *str);

// This function does not check the string to contain only digits.
// In fact, it doesn't check anything.
void DeleteLeadingZeroes(std::string *str);

std::vector<std::string> Split(const std::string &to_split, char delimiter);

void ReadFileIntoString(const std::string &filename, std::string *output);

#endif  // BASE_COMMON_H_
