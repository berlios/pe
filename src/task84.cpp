#include <Eigen/Dense>
using namespace Eigen;

#include "base/task.h"

namespace {
struct MoveProbability {
  int jump_value;
  double p;
};
}

TASK(84) {
  Matrix<double, 40, 40> m = Matrix<double, 40, 40>::Zero();

  // std::vector<MoveProbability> dice_probabilities = {
  //     {2, 1. / 36},  {3, 2. / 36},  {4, 3. / 36}, {5, 4. / 36},
  //     {6, 5. / 36},  {7, 6. / 36},  {8, 5. / 36}, {9, 4. / 36},
  //     {10, 3. / 36}, {11, 2. / 36}, {12, 1. / 36}};

  std::vector<MoveProbability> dice_probabilities = {
      {2, 1. / 16}, {3, 2. / 16}, {4, 3. / 16}, {5, 4. / 16},
      {6, 3. / 16}, {7, 2. / 16}, {8, 1. / 16}};

  for (int i = 0; i < 40; ++i) {
    for (const auto& element : dice_probabilities) {
      m(i, (i + element.jump_value) % 40) = element.p;
    }

    auto scale_row_by = [&m, i](double value) {
      for (int j = 0; j < 40; ++j) {
        m(i, j) *= value;
      }
    };

    //     scale_row_by(215. / 216);
    //     m(i, 10) += 1. / 216;
    scale_row_by(63. / 64);
    m(i, 10) += 1. / 64;

    // CH1, CH2, CH3
    for (int j : {7, 22, 36}) {
      if (m(i, j) == 0) {
        continue;
      }

      double scale = m(i, j);

      m(i, j) *= 6. / 16;

      m(i, 0) += scale / 16;
      m(i, 10) += scale / 16;
      m(i, 11) += scale / 16;
      m(i, 24) += scale / 16;
      m(i, 39) += scale / 16;
      m(i, 5) += scale / 16;
      m(i, (j + 40 - 3) % 40) += scale / 16;

      if (j == 7) {
        m(i, 15) += 2. * scale / 16;
        m(i, 12) += scale / 16;
      }
      if (j == 22) {
        m(i, 25) += 2. * scale / 16;
        m(i, 28) += scale / 16;
      }
      if (j == 36) {
        m(i, 5) += 2. * scale / 16;
        m(i, 12) += scale / 16;
      }
    }

    // CC1, CC2, CC3
    for (int j : {2, 17, 33}) {
      if (m(i, j) == 0) {
        continue;
      }

      double scale = m(i, j);

      m(i, j) *= 14. / 16;
      m(i, 0) += scale / 16;
      m(i, 10) += scale / 16;
    }

    if (m(i, 30) != 0) {
      m(i, 10) += m(i, 30);
      m(i, 30) = 0;
    }
  }

  Eigen::EigenSolver<decltype(m)> eigensolver(m.transpose());
  if (eigensolver.info() != Eigen::Success) {
    abort();
  }

  auto almost_equal = [](double a, double b) { return std::abs(a - b) < 1e-8; };

  int index = -1;
  for (int i = 0; i < 40; ++i) {
    if (almost_equal(eigensolver.eigenvalues()(i).real(), 1) &&
        almost_equal(eigensolver.eigenvalues()(i).imag(), 0)) {
      index = i;
    }
  }

  auto eigenvector = eigensolver.eigenvectors().col(index).real();
  eigenvector /= eigenvector.sum();

  std::vector<std::pair<std::string, double>> res(40);
  for (int i = 0; i < 40; ++i) {
    res[i].first = std::to_string(i);
    if (res[i].first.size() == 1) {
      res[i].first = "0" + res[i].first;
    }
    res[i].second = eigenvector(i);
  }

  std::sort(res.begin(), res.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });

  return res[0].first + res[1].first + res[2].first;
}
