#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <numeric>
#include <iomanip>
#include <execution>
#include <range/v3/all.hpp>
#include "matrix.h"

namespace views = ranges::views;
struct LightMatrix
{
  Matrix<bool> mnext_;

public:
  Matrix<bool> mcurr_;
  auto count() const noexcept
  {
    return std::count(std::execution::par_unseq, std::begin(mcurr_.array()), std::end(mcurr_.array()), true);
  }
  LightMatrix(int n) : mnext_(n, n), mcurr_(n, n) {}
  void transform() noexcept
  {
    auto indexs = (views::ints | views::take(mcurr_.rowCount() - 1) | views::drop(1));
    std::vector<int> v(static_cast<std::size_t>(mcurr_.rowCount() - 2));
    ranges::copy(indexs, v.begin());
    std::for_each(std::execution::par_unseq, v.begin(), v.end(), [this, &v](auto i) {
      std::for_each(std::execution::par_unseq, v.begin(), v.end(), [this, i](auto j) {
        int cnt = mcurr_(i, j - 1) + mcurr_(i - 1, j - 1) + mcurr_(i - 1, j) + mcurr_(i - 1, j + 1) + mcurr_(i, j + 1) + mcurr_(i + 1, j + 1) + mcurr_(i + 1, j) + mcurr_(i + 1, j - 1);
        if (mcurr_(i, j)) {
          mnext_(i, j) = (cnt == 2) || (cnt == 3);
        } else {
          if (cnt == 3) {
            mnext_(i, j) = true;
          }
        }
      });
    });
    mnext_(1, 100) = true;
    mnext_(1, 1) = true;
    mnext_(100, 1) = true;
    mnext_(100, 100) = true;
    std::swap(mcurr_, mnext_);
    std::fill(std::execution::par_unseq, std::begin(mnext_.array()), std::end(mnext_.array()), false);
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    LightMatrix lm(102);

    for (auto j = 0; (ifs >> s); ++j) {
      std::transform(s.begin(), s.end(), lm.mcurr_.row(j + 1).begin() + 1, [](char c) { return c == '#'; });
    }
    ranges::for_each(views::ints | views::take(100), [&lm](int) {
      lm.transform();
    });
  }
}