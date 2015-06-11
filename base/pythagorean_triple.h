#ifndef BASE_PYTHAGOREAN_TRIPLE_H_
#define BASE_PYTHAGOREAN_TRIPLE_H_

#include "base/number_theory.h"

template<class T>
class PriceTriple;

// Class for holding primitive pythagorean triples (duh) a, b and c.
// They satisfy:
//   - a^2 + b^2 = c^2;
//   - GCD(a, b, c) = 1.
// Default-constructed object is not a valid triple (just three zeros).
// You can, however, construct an object using three numbers (alright, three
// elements of type T). In that case, first, their order doesn't matter.
// And second, if supplied elements do not form a primitive triple then
// you'll get an invalid triple consisting of three zeros.
template<class T>
class PrimitivePythagoreanTriple {
 public:
  // Default-constructed object is not a valid triple. Use constructor taking
  // three elements of type T instead.
  PrimitivePythagoreanTriple() : a_(0), b_(0), c_(0) { }

  // This constructor checks if arguments can be reordered so that
  // a^2 + b^2 = c^2. It also checks for GCD(a, b, c) = 1.
  PrimitivePythagoreanTriple(const T &a, const T &b, const T &c) {
    SetTriple(a, b, c);
  }

  bool IsValid() const {
    return a_ != 0 && b_ != 0 && c_ != 0;
  }

  bool SetTriple(const T &a, const T &b, const T &c) {
    if (a == 0 || b == 0 || c == 0) {
      a_ = b_ = c_ = T(0);
      return false;
    }

    if (GCD(GCD(a, b), c) != T(1)) {
      a_ = b_ = c_ = T(0);
      return false;
    }

    using std::max;
    using std::min;
    const T &z = max(max(a, b), c);
    const T &x = min(min(a, b), c);

    // The middle number out of 3.
    //     y = min(max(a, b), max(a, c), max(b, c))
    const T &y = min(min(max(a, b), max(a, c)), max(b, c));

    // Maybe work around the possible overflow somehow?
    if (x*x + y*y != z*z) {
      a_ = b_ = c_ = T(0);
      return false;
    }

    if (y % 2 == 0) {
      a_ = x;
      b_ = y;
      c_ = z;
    } else {
      a_ = y;
      b_ = x;
      c_ = z;
    }

    return true;
  }

  PriceTriple<T> PriceTree() const {
    return PriceTriple<T>(a(), b(), c());
  }

  bool operator==(const PrimitivePythagoreanTriple<T> &other) const {
    return a_ == other.a_ &&
           b_ == other.b_ &&
           c_ == other.c_;
  }

  bool operator!=(const PrimitivePythagoreanTriple<T> &other) const {
    return !(*this == other);
  }

  // Returns the odd of the two catheti.
  T a() const { return a_; }

  // Returns the even of the two catheti.
  T b() const { return b_; }

  // Returns the hypothenuse.
  T c() const { return c_; }

 private:
  // The triple itself. b_ should always be even (one of a_ and b_ is always
  // even so it's going to always be b_).
  T a_;
  T b_;
  T c_;

  friend class PriceTriple<T>;
};

template<class T>
class PriceTriple : public PrimitivePythagoreanTriple<T> {
 public:
  PriceTriple(const T &a, const T &b, const T &c)
      : PrimitivePythagoreanTriple<T>(a, b, c) { }
  PriceTriple() : PrimitivePythagoreanTriple<T>() { }

  PriceTriple<T> LeftChild() const {
    PriceTriple<T> res;

    // Refer to http://arxiv.org/pdf/0809.4324.pdf for details.
    res.a_ = this->a()*2 + this->b() - this->c();
    res.b_ = this->a()*(-2) + this->b()*2 + this->c()*2;
    res.c_ = this->a()*(-2) + this->b() + this->c()*3;

    return res;
  }

  PriceTriple<T> MiddleChild() const {
    PriceTriple<T> res;

    // Refer to http://arxiv.org/pdf/0809.4324.pdf for details.
    res.a_ = this->a()*2 + this->b() + this->c();
    res.b_ = this->a()*2 + this->b()*(-2) + this->c()*2;
    res.c_ = this->a()*2 - this->b() + this->c()*3;

    return res;
  }

  PriceTriple<T> RightChild() const {
    PriceTriple<T> res;

    // Refer to http://arxiv.org/pdf/0809.4324.pdf for details.
    res.a_ = this->a()*2 - this->b() + this->c();
    res.b_ = this->a()*2 + this->b()*2 + this->c()*2;
    res.c_ = this->a()*2 + this->b() + this->c()*3;

    return res;
  }

  bool IsRoot() const {
    return this->a() == 3 && this->b() == 4 && this->c() == 5;
  }
};

#endif  // BASE_PYTHAGOREAN_TRIPLE_H_
