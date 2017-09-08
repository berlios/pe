#ifndef BASE_QUADRATIC_RATIONAL_H_
#define BASE_QUADRATIC_RATIONAL_H_

#include <gmpxx.h>

#include "base/macros.h"

// Numbers of the form a*sqrt(n) + b where a and b are rationals.
class QuadraticRational {
 public:
  explicit QuadraticRational(int n) : n_(n), a_(0), b_(0) {}
  QuadraticRational(int n, int a, int b) : n_(n), a_(a), b_(b) {}
  QuadraticRational(int n, const mpq_class& a, const mpq_class& b)
      : n_(n), a_(a), b_(b) {}
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

#endif  // BASE_QUADRATIC_RATIONAL_H_
