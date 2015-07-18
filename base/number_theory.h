#include <gmpxx.h>
#include <map>

std::vector<int> Sieve(int upper_limit);
std::map<mpz_class, uint> Factorize(const mpz_class &number);
int NumberOfPrimeDivisors(const mpz_class &number);
mpz_class SumOfAllDivisors(const mpz_class &number);
mpz_class SumOfProperDivisors(const mpz_class &number);
uint LengthOfRepeatingCycle(const mpq_class &fraction);

// Triangle numbers are of the form i*(i + 1)/2
mpz_class NthTriangleNumber(uint n);
bool IsTriangleNumber(const mpz_class &num);

// Pentagonal numbers are of the form i*(3i - 1)/2
mpz_class NthPentagonalNumber(uint n);
bool IsPentagonalNumber(const mpz_class &num);

namespace {
template<class T>
struct GCDHelper {
  static T GCD(const T &a, const T &b) {
    using std::max;
    using std::min;

    T maximum = max(a, b);
    T minimum = min(a, b);

    T remainder = maximum % minimum;

    while (remainder != 0) {
      maximum = minimum;
      minimum = remainder;
      remainder = maximum % minimum;
    }

    return minimum;
  }
};

template <>
struct GCDHelper<mpz_class> {
  static mpz_class GCD(const mpz_class &a, const mpz_class &b) {
    mpz_class ret;
    mpz_gcd(ret.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
    return ret;
  }
};

}

template<class T>
inline T GCD(const T &a, const T &b) {
  return GCDHelper<T>::GCD(a, b);
}

// Class that represents quadratic polynomial over the field represented by
// the type T. It can be created with either all coefficients specified or none,
// in which case it's created with zero coefficients.
// Example usage:
//
//     Quadratic<int> f(1, 1, 41);
//     EXPECT_TRUE(IsPrime(f(30)));
template<class T>
class Quadratic {
 public:
  // Construct a polynomial a*x^2 + b*x + c.
  Quadratic(const T &a, const T &b, const T &c) : a_(a), b_(b), c_(c) { }

  // Default constructor creates polynomial that's zero everywhere.
  Quadratic() : Quadratic(T(0), T(0), T(0)) { }

  void SetCoefficients(const T &a, const T &b, const T &c) {
    a_ = a;
    b_ = b;
    c_ = c;
  }

  T operator()(const T &x) const {
    return a_*x*x + b_*x + c_;
  }

  bool operator==(const Quadratic<T> &g) const {
    return (a_ == g.a_ &&
            b_ == g.b_ &&
            c_ == g.c_);
  }

  bool operator!=(const Quadratic<T> &g) const {
    return !(*this == g);
  }

  const T& a() const { return a_; }
  const T& b() const { return b_; }
  const T& c() const { return c_; }

  void set_a(const T& a) { a_ = a; }
  void set_b(const T& b) { b_ = b; }
  void set_c(const T& c) { c_ = c; }

 private:
  // Coefficients of the quadratic a*x^2 + b*x + c.
  T a_, b_, c_;
};
