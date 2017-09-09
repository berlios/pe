#include <string>
#include <vector>

#include "base/common.h"
#include "base/task.h"

bool AdvanceIndexesByLetter(const std::vector<std::string>& strings, char c,
                            std::vector<int>* indexes) {
  bool advanced_at_least_once = false;
  for (size_t i = 0; i < strings.size(); ++i) {
    int& index = (*indexes)[i];
    if (index == 3) {
      continue;
    }
    if (strings[i][index] == c) {
      index++;
      advanced_at_least_once = true;
    }
  }

  return advanced_at_least_once;
}
void RetractIndexesByLetter(const std::vector<std::string>& strings, char c,
                            std::vector<int>* indexes) {
  for (size_t i = 0; i < strings.size(); ++i) {
    int& index = (*indexes)[i];
    if (index == 0) {
      continue;
    }
    if (strings[i][index - 1] == c) {
      index--;
    }
  }
}

void ShortestCommonSuperstring(const std::vector<std::string>& strings,
                               std::vector<int>* indexes,
                               std::string* minimum_length_string,
                               std::string* current_sequence) {
  if (current_sequence->size() >= minimum_length_string->size()) {
    return;
  }

  if (*std::min_element(indexes->begin(), indexes->end()) == 3) {
    *minimum_length_string = *current_sequence;
    return;
  }

  for (char c : "0123456789") {
    if (!AdvanceIndexesByLetter(strings, c, indexes)) {
      continue;
    }
    current_sequence->push_back(c);
    ShortestCommonSuperstring(strings, indexes, minimum_length_string,
                              current_sequence);
    current_sequence->pop_back();
    RetractIndexesByLetter(strings, c, indexes);
  }
}

std::string ShortestCommonSuperstring(const std::vector<std::string>& strings) {
  std::string sequence;
  std::vector<int> indexes(strings.size());
  std::string minimum_length_string =
      std::accumulate(strings.begin(), strings.end(), std::string{});
  ShortestCommonSuperstring(strings, &indexes, &minimum_length_string,
                            &sequence);
  return minimum_length_string;
}

TASK(79) {
  std::string file_contents = ReadFileIntoString("data/079_keylog.txt");
  while (file_contents.back() == '\n') {
    file_contents.pop_back();
  }
  std::vector<std::string> strings = Split(file_contents, '\n');
  return ShortestCommonSuperstring(strings);
}
