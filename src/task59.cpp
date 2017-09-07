#include <algorithm>

#include "base/common.h"
#include "base/task.h"

static double english_frequencies[26] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074};

double ScoreData(const std::vector<uint8_t>& input) {
  double frequences[256] = {0.0};
  for (uint8_t element : input) {
    frequences[element] += 1;
  }
  for (double& f : frequences) {
    f /= input.size();
  }

  double score = 0.0;
  for (int i = 0; i < 256; ++i) {
    if ('A' <= i && i <= 'Z') {
      score += std::abs(frequences[i] - english_frequencies[i - 'A']);
    } else if ('a' <= i && i <= 'z') {
      score += std::abs(frequences[i] - english_frequencies[i - 'a']);
    } else {
      score += frequences[i];
    }
  }
  return score;
}

std::vector<uint8_t> XorWithSingleByte(const std::vector<uint8_t>& input,
                                       uint8_t xor_byte) {
  std::vector<uint8_t> result(input.size());
  for (size_t i = 0; i < input.size(); ++i) {
    result[i] = input[i] ^ xor_byte;
  }

  return result;
}

uint8_t DetectSingleCharXor(const std::vector<uint8_t>& input) {
  int best_i = -1;
  double best_score = std::numeric_limits<double>::infinity();

  // From the task we know that we are looking for all lowercase letters.
  for (int i = 'a'; i <= 'z'; ++i) {
    double score = ScoreData(XorWithSingleByte(input, i));
    if (score < best_score) {
      best_score = score;
      best_i = i;
    }
  }

  return best_i;
}

std::vector<uint8_t> RepeatingKeyXor(const std::vector<uint8_t>& input,
                                     const std::vector<uint8_t>& key) {
  std::vector<uint8_t> result(input.size());

  int key_index = 0;
  for (size_t i = 0; i < input.size(); ++i) {
    result[i] = input[i] ^ key[key_index];
    key_index = (key_index + 1) % key.size();
  }

  return result;
}

std::vector<uint8_t> GetEqualDistanceBytes(const std::vector<uint8_t>& data,
                                           int start, int step) {
  std::vector<uint8_t> result;
  result.reserve((data.size() - start) / step);
  for (size_t i = start; i < data.size(); i += step) {
    result.push_back(data[i]);
  }
  return result;
}

#include <iostream>

TASK(59) {
  auto codes = Split(ReadFileIntoString("data/059_cipher.txt"), ',');
  std::vector<uint8_t> cipher(codes.size());
  std::transform(codes.begin(), codes.end(), cipher.begin(),
                 [](const std::string& s) { return std::stoi(s); });

  std::vector<uint8_t> key(3);
  for (int i = 0; i < 3; ++i) {
    auto transposed_data = GetEqualDistanceBytes(cipher, i, 3);
    key[i] = DetectSingleCharXor(transposed_data);
  }

  auto decoded_data = RepeatingKeyXor(cipher, key);

  return std::accumulate(decoded_data.begin(), decoded_data.end(), 0);
}
