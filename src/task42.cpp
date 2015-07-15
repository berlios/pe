#include <string>
#include <vector>

#include "base/common.h"
#include "base/number_theory.h"
#include "base/task.h"

TASK(42) {
  std::vector<std::string> words{
#include "src/042_words.txt"  // Hm, neat.
  };

  int count = 0;
  // SSO FTW!
  for (auto word : words) {
    if (IsTriangleNumber(AlphabeticalValue(word))) {
      count++;
    }
  }

  return count;
}
