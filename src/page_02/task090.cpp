#include <bitset>
#include <unordered_set>
#include <utility>

#include "base/task.h"

namespace {
class UnorderedPairOfStrings {
 public:
  UnorderedPairOfStrings() {}
  UnorderedPairOfStrings(std::string s1, std::string s2) {
    if (s1 < s2) {
      first_ = std::move(s1);
      second_ = std::move(s2);
    } else {
      first_ = std::move(s2);
      second_ = std::move(s1);
    }
  }

  const std::string& first() const { return first_; }
  const std::string& second() const { return second_; }

  bool operator==(const UnorderedPairOfStrings& other) const {
    return first_ == other.first_ && second_ == other.second_;
  }

 private:
  std::string first_;
  std::string second_;
};

struct Rule {
  Rule(int left, int right) : left_digit(left), right_digit(right) {}
  void SwapSides() { std::swap(left_digit, right_digit); }
  int left_digit;
  int right_digit;
};
}

namespace std {
template <>
struct hash<UnorderedPairOfStrings> {
  std::size_t operator()(const UnorderedPairOfStrings& pair) const {
    return std::hash<std::string>{}(pair.first() + pair.second());
  }
};
}

TASK(90) {
  std::unordered_set<UnorderedPairOfStrings> resulting_set;
  std::vector<Rule> rules{{0, 1}, {0, 4}, {2, 5}, {8, 1},
                          {0, 6}, {1, 6}, {3, 6}, {4, 6}};

  for (int i = 0; i < 16 * 16 * 16; ++i) {
    int n = i;
    std::vector<Rule> adjusted_rules = rules;
    std::bitset<4> bits(n % 16);
    n /= 16;
    for (size_t j = 0; j < bits.size(); ++j) {
      if (bits[j] == 1) {
        adjusted_rules[j].SwapSides();
      }
    }

    bits = std::bitset<4>(n % 16);
    n /= 16;
    for (size_t j = 0; j < bits.size(); ++j) {
      if (bits[j] == 1) {
        adjusted_rules[4 + j].right_digit = 9;
      }
    }

    bits = std::bitset<4>(n % 16);
    for (size_t j = 0; j < bits.size(); ++j) {
      if (bits[j] == 1) {
        adjusted_rules[4 + j].SwapSides();
      }
    }

    std::unordered_set<int> left_die, right_die;
    for (const Rule& rule : adjusted_rules) {
      left_die.emplace(rule.left_digit);
      right_die.emplace(rule.right_digit);
    }
    if (left_die.size() > 6) {
      continue;
    }
    if (right_die.size() > 6) {
      continue;
    }

    std::vector<int> missing_left_digits;
    for (int digit : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      if (left_die.count(digit) == 0) {
        missing_left_digits.push_back(digit);
      }
    }

    std::vector<int> missing_right_digits;
    for (int digit : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      if (right_die.count(digit) == 0) {
        missing_right_digits.push_back(digit);
      }
    }

    std::vector<bool> select_left_digits(missing_left_digits.size());
    for (size_t j = 0; j < 6 - left_die.size(); ++j) {
      *(select_left_digits.rbegin() + j) = 1;
    }

    do {
      std::vector<bool> select_right_digits(missing_right_digits.size());
      for (size_t j = 0; j < 6 - right_die.size(); ++j) {
        *(select_right_digits.rbegin() + j) = 1;
      }

      do {
        std::vector<int> left(left_die.begin(), left_die.end());
        std::vector<int> right(right_die.begin(), right_die.end());
        for (size_t j = 0; j < missing_left_digits.size(); ++j) {
          if (select_left_digits[j]) {
            left.push_back(missing_left_digits[j]);
          }
        }

        for (size_t j = 0; j < missing_right_digits.size(); ++j) {
          if (select_right_digits[j]) {
            right.push_back(missing_right_digits[j]);
          }
        }

        CHECK(left.size() == 6);
        CHECK(right.size() == 6);

        std::sort(left.begin(), left.end());
        std::sort(right.begin(), right.end());

        std::string s1, s2;
        for (int left_digit : left) {
          s1 += std::to_string(left_digit);
        }
        for (int right_digit : right) {
          s2 += std::to_string(right_digit);
        }

        resulting_set.emplace(s1, s2);

      } while (std::next_permutation(select_right_digits.begin(),
                                     select_right_digits.end()));
    } while (std::next_permutation(select_left_digits.begin(),
                                   select_left_digits.end()));
  }

  return resulting_set.size();
}
