#include <string>
#include <vector>

#include "base/common.h"
#include "base/number_theory.h"
#include "base/task.h"

TASK(42) {
  std::vector<std::string> words{
    #include "src/p042_words.txt"  // Hm, neat.
  };

  int count = 0;
  // SSO FTW!
  for (auto word : words) {
    int word_value = 0;
    for (auto letter : word) {
      word_value += letter - 'A' + 1;
    }

    if (IsTriangleNumber(word_value)) {
      count++;
    }
  }

  SetResult(ToString(count));
}
