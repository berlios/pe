#include "base/common.h"
#include "base/task.h"

TASK(99) {
  auto lines =
      Split(ReadFileIntoString("data/099_base_exp.txt"), '\n', SkipEmpty());

  int line_number = -1;
  double max_log = -1;
  for (size_t i = 0; i < lines.size(); ++i) {
    auto numbers = Split(lines[i], ',');
    CHECK(numbers.size() == 2);

    int base = std::stoi(numbers[0]);
    int exponent = std::stoi(numbers[1]);

    double log_base = std::log(base);
    double result_log = log_base * exponent;
    if (max_log < result_log) {
      max_log = result_log;
      line_number = i + 1;
    }
  }

  return line_number;
}
