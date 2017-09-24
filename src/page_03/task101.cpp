#include <gmpxx.h>
#include <vector>

#include "base/task.h"
#include "gtest/gtest.h"

namespace {
// Special case of lagrange polynomials. x-coordinates of points used to
// construct the polynomial are 1, 2, 3, ... and so on.
// Meant to be working with integers.
class LagrangePolynomial {
 public:
  LagrangePolynomial() = default;
  LagrangePolynomial(std::initializer_list<mpz_class> values)
      : values_(values.begin(), values.end()) {}

  void Set(std::vector<mpz_class> values) { values_ = std::move(values); }

  mpq_class operator()(int x) const {
    mpq_class sum = 0;
    for (size_t i = 0; i < values_.size(); ++i) {
      mpq_class product = 1;
      for (size_t j = 0; j < values_.size(); ++j) {
        if (j == i) {
          continue;
        }

        product *= x - (j + 1);
        product /= static_cast<int>(i + 1) - static_cast<int>(j + 1);
      }

      sum += product * values_[i];
    }

    return sum;
  }

 private:
  std::vector<mpz_class> values_;
};
}

TEST(Task101, LagrangePolynomial) {
  LagrangePolynomial p{1, 2};
  EXPECT_EQ(3, p(3));

  std::vector<mpz_class> values{1, 8, 27};
  p.Set(values);
  EXPECT_EQ(58, p(4));
}

TEST(Task101, LagrangePolynomialDefaultConstruct) {
  LagrangePolynomial p;
  p.Set({2, 4});
  EXPECT_EQ(6, p(3));
}

TASK(101) {
  auto generating_function = [](int x) {
    mpz_class result = 1;

    int sign = -1;
    mpz_class power = x;
    for (int i = 1; i <= 10; ++i) {
      result += sign * power;
      sign = -sign;
      power *= x;
    }

    return result;
  };

  mpz_class result;
  std::vector<mpz_class> values;
  for (int i = 1; i <= 10; ++i) {
    values.push_back(generating_function(i).get_si());
    LagrangePolynomial p;
    p.Set(values);
    for (int x = i;; ++x) {
      if (generating_function(x) != p(x)) {
        result += p(x);
        break;
      }
    }
  }

  return result;
}
