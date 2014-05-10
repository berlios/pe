#include <gmpxx.h>
#include <algorithm>
#include <string>

#include "base/task.h"
#include "gtest/gtest.h"

using std::max;
using std::string;

static inline void CollatzFuncion(const mpz_class &in, mpz_class *out) {
  if (in%2 == 0) {
    *out = in/2;
  } else {
    *out = in*3 + 1;
  }
}

int SizeofCollatzChain(int n) {
  mpz_class m = n;
  int size = 1;

  while (m != 1) {
    CollatzFuncion(m, &m);
    size++;
  }

  return size;
}
TEST(Task14, CollatzFuncion) {
  mpz_class out;
  CollatzFuncion(10, &out);
  EXPECT_EQ(5, out);

  CollatzFuncion(13, &out);
  EXPECT_EQ(40, out);

  CollatzFuncion(1, &out);
  EXPECT_EQ(4, out);
}

TEST(Task14, SizeofCollatzChain) {
  EXPECT_EQ(10, SizeofCollatzChain(13));
}

TASK(14) {
  int result = 0, size = 0;

  for (int i = 1; i < 1000*1000; ++i) {
    int current_size = SizeofCollatzChain(i);
    if (size < current_size) {
      size = current_size;
      result = i;
    }
  }
  SetResult(ToString(result));
}
