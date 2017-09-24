#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/common.h"
#include "base/task.h"

std::string Sorted(std::string str) {
  std::sort(str.begin(), str.end());
  return str;
}

TASK(98) {
  auto words =
      Split(ReadFileIntoString("data/098_words.txt"), ',', SkipEmpty());
  for (auto& word : words) {
    word = word.substr(1, word.size() - 2);
  }

  std::unordered_map<std::string, std::vector<std::string>> anagrams;

  for (const auto& word : words) {
    anagrams[Sorted(word)].emplace_back(word);
  }

  size_t max_length = 0;
  for (const auto& word : words) {
    max_length = std::max(max_length, word.size());
  }

  std::unordered_map<int, std::vector<std::string>> squares;
  for (int64_t i = 1;; ++i) {
    std::string square_string = std::to_string(i * i);
    if (square_string.size() > max_length) {
      break;
    }

    squares[square_string.size()].emplace_back(square_string);
  }

  int largest_square = -1;

  for (const auto& pair : anagrams) {
    const std::vector<std::string>& all_anagrams = pair.second;

    if (all_anagrams.size() <= 1) {
      continue;
    }

    const std::vector<std::string>& squares_strings =
        squares[all_anagrams[0].size()];

    for (const std::string& anagram : all_anagrams) {
      for (const std::string& square : squares_strings) {
        std::unordered_map<char, char> letter_to_digit_mapping;
        std::unordered_map<char, char> digit_to_letter_mapping;
        bool valid_mapping = true;
        for (size_t i = 0; i < anagram.size(); ++i) {
          char letter = anagram[i];
          char digit = square[i];
          auto it = letter_to_digit_mapping.find(letter);
          if (it != letter_to_digit_mapping.end() && it->second != digit) {
            valid_mapping = false;
            break;
          }
          letter_to_digit_mapping[letter] = digit;

          auto it2 = digit_to_letter_mapping.find(digit);
          if (it2 != digit_to_letter_mapping.end() && it2->second != letter) {
            valid_mapping = false;
            break;
          }
          digit_to_letter_mapping[digit] = letter;
        }

        if (!valid_mapping) {
          continue;
        }

        for (const std::string& anagram2 : all_anagrams) {
          if (anagram == anagram2) {
            continue;
          }

          std::string mapped_anagram;
          std::transform(anagram2.begin(), anagram2.end(),
                         std::back_inserter(mapped_anagram),
                         [&letter_to_digit_mapping](char c) {
                           return letter_to_digit_mapping[c];
                         });

          if (std::find(squares_strings.begin(), squares_strings.end(),
                        mapped_anagram) != squares_strings.end()) {
            largest_square = std::max(largest_square, std::stoi(square));
          }
        }
      }
    }
  }

  return largest_square;
}
