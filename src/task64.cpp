#include <algorithm>
#include <gmpxx.h>

#include "base/macros.h"
#include "base/number_theory.h"
#include "base/task.h"
#include "gtest/gtest.h"

// Numbers of the form a*sqrt(n) + b where a and b are rationals.
class QuadraticRational {
 public:
  explicit QuadraticRational(int n) : n_(n), a_(0), b_(0) {}
  QuadraticRational(int n, int a, int b) : n_(n), a_(a), b_(b) {}
  QuadraticRational(int n, const mpq_class& a, const mpq_class& b) : n_(n), a_(a), b_(b) {}
  mpz_class Floor() const {
    mpf_class tmp = n_;
    tmp = sqrt(tmp);
    tmp = tmp * a_ + b_;

    mpz_class result;
    mpz_set_f(result.get_mpz_t(), tmp.get_mpf_t());
    return result;
  }

  QuadraticRational Reciprocal() const {
    QuadraticRational result(n_);

    result.a_ = a_ / (a_ * a_ * n_ - b_ * b_);
    result.b_ = -b_ / (a_ * a_ * n_ - b_ * b_);

    return result;
  }

  QuadraticRational& operator-=(const mpz_class& n) {
    b_ -= n;
    return *this;
  }

  bool operator==(const QuadraticRational& other) const {
    CHECK(n_ == other.n_);
    return a_ == other.a_ && b_ == other.b_;
  }

 private:
  int n_;
  mpq_class a_;
  mpq_class b_;
};

int GetContinuedFractionPeriod(int n) {
  std::vector<QuadraticRational> fractions;
  fractions.emplace_back(n, 1, 0);

  while (true) {
    QuadraticRational f = fractions.back();
    f -= f.Floor();
    f = f.Reciprocal();
    auto it = std::find(fractions.rbegin(), fractions.rend(), f);
    if (it == fractions.rend()) {
      fractions.emplace_back(f);
      continue;
    }

    return std::distance(fractions.rbegin(), it) + 1;
  }
}

TEST(Task64, QuadraticRational) {
  QuadraticRational n(23, 1, 0);

  EXPECT_EQ(4, n.Floor());
  EXPECT_EQ(QuadraticRational(23, mpq_class(1, 23), 0), n.Reciprocal());

  n -= 4;
  EXPECT_EQ(QuadraticRational(23, mpq_class(1, 7), mpq_class(4, 7)),
            n.Reciprocal());
  EXPECT_EQ(1, n.Reciprocal().Floor());
}

TEST(Task64, GetContinuedFractionPeriod) {
  EXPECT_EQ(1, GetContinuedFractionPeriod(2));
  EXPECT_EQ(2, GetContinuedFractionPeriod(3));
}

TASK(64) {
  int counter = 0;
  for (int i = 2; i <= 10000; ++i) {
    if (IsSquareNumber(i)) {
      continue;
    }
    if (GetContinuedFractionPeriod(i) % 2 == 1) {
      counter++;
    }
  }
  return counter;
}
