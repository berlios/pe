#include <gmpxx.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <set>
#include <vector>

#include "base/task.h"
#include "gtest/gtest.h"

namespace {
struct BinaryOperation {
  virtual mpq_class operator()(const mpq_class& a,
                               const mpq_class& b) const = 0;
  virtual ~BinaryOperation() {}
};

struct Plus : BinaryOperation {
  mpq_class operator()(const mpq_class& a, const mpq_class& b) const override {
    return a + b;
  }
};

struct Minus : BinaryOperation {
  mpq_class operator()(const mpq_class& a, const mpq_class& b) const override {
    return a - b;
  }
};

struct Multiplication : BinaryOperation {
  mpq_class operator()(const mpq_class& a, const mpq_class& b) const override {
    return a * b;
  }
};

struct Division : BinaryOperation {
  mpq_class operator()(const mpq_class& a, const mpq_class& b) const override {
    if (b == 0) {
      throw 0;
    }
    return a / b;
  }
};

// There are only 5 unique ways to put parens in expression a * b * c * d
// where a star represents a binary operation.
// Here are all of them.
mpq_class Calculate1(const BinaryOperation& op1, const BinaryOperation& op2,
                     const BinaryOperation& op3, int a, int b, int c, int d) {
  return op3(op1(a, b), op2(c, d));
}
mpq_class Calculate2(const BinaryOperation& op1, const BinaryOperation& op2,
                     const BinaryOperation& op3, int a, int b, int c, int d) {
  return op3(op2(op1(a, b), c), d);
}
mpq_class Calculate3(const BinaryOperation& op1, const BinaryOperation& op2,
                     const BinaryOperation& op3, int a, int b, int c, int d) {
  return op3(op2(a, op1(b, c)), d);
}
mpq_class Calculate4(const BinaryOperation& op1, const BinaryOperation& op2,
                     const BinaryOperation& op3, int a, int b, int c, int d) {
  return op3(a, op2(op1(b, c), d));
}
mpq_class Calculate5(const BinaryOperation& op1, const BinaryOperation& op2,
                     const BinaryOperation& op3, int a, int b, int c, int d) {
  return op3(a, op2(b, op1(c, d)));
}

int Longest1ToN(int a, int b, int c, int d) {
  std::vector<int> digits{a, b, c, d};
  std::sort(digits.begin(), digits.end());

  std::vector<std::unique_ptr<BinaryOperation>> operations;
  operations.emplace_back(std::make_unique<Plus>());
  operations.emplace_back(std::make_unique<Minus>());
  operations.emplace_back(std::make_unique<Multiplication>());
  operations.emplace_back(std::make_unique<Division>());

  std::vector<std::function<decltype(Calculate1)>> functions{
      Calculate1, Calculate2, Calculate3, Calculate4, Calculate5};

  std::set<int> results;

  do {
    for (const auto& op1 : operations) {
      for (const auto& op2 : operations) {
        for (const auto& op3 : operations) {
          for (const auto& function : functions) {
            try {
              auto result = function(*op1, *op2, *op3, digits[0], digits[1],
                                     digits[2], digits[3]);
              if (result.get_den() == 1) {
                results.emplace(result.get_num().get_si());
              }
            } catch (...) {
            }
          }
        }
      }
    }
  } while (std::next_permutation(digits.begin(), digits.end()));

  auto it = results.find(1);
  int res = 0;
  while (it != results.end() && res + 1 == *it) {
    ++res;
    ++it;
  }
  return res;
}
}

TEST(Task93, Longest1ToN) { EXPECT_EQ(28, Longest1ToN(1, 2, 3, 4)); }

TASK(93) {
  std::vector<int> select_digits{0, 0, 0, 0, 0, 0, 1, 1, 1, 1};

  int max_length = 0;
  std::string result;
  do {
    std::vector<int> digits;
    for (size_t i = 0; i < select_digits.size(); ++i) {
      if (select_digits[i] == 1) {
        digits.push_back(i);
      }
    }

    int length = Longest1ToN(digits[0], digits[1], digits[2], digits[3]);
    if (length > max_length) {
      max_length = length;
      result = std::to_string(digits[0]) + std::to_string(digits[1]) +
               std::to_string(digits[2]) + std::to_string(digits[3]);
    }
  } while (std::next_permutation(select_digits.begin(), select_digits.end()));

  return result;
}
