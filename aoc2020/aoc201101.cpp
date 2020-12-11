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
enum {
  Floor,
  Empty,
  Occupied
};

namespace views = ranges::views;
template<std::size_t RowCnt, std::size_t ColCnt>
struct LightMatrix
{
  bool occupied(std::size_t i, std::size_t j) const noexcept
  {
    return mcurr_(i, j) == Occupied;
  }
  int surroundOccupiedNum(std::size_t i, std::size_t j) const noexcept
  {
    return occupied(i, j - 1) + occupied(i - 1, j - 1) + occupied(i - 1, j) + occupied(i - 1, j + 1) + occupied(i, j + 1) + occupied(i + 1, j + 1) + occupied(i + 1, j) + occupied(i + 1, j - 1);
  }

  std::vector<std::size_t> vr_;
  std::vector<std::size_t> vc_;

public:
  FixedMatrix<int, RowCnt, ColCnt> mnext_;
  LightMatrix() noexcept
    : vr_(mcurr_.rowCount() - 2),
      vc_(mcurr_.colCount() - 2)
  {
    std::size_t start = 0;
    auto indexs = views::iota(start) | views::drop(1) | views::take(mcurr_.rowCount() - 2);
    auto colindexs = views::iota(start) | views::drop(1) | views::take(mcurr_.colCount() - 2);
    ranges::copy(indexs, vr_.begin());
    ranges::copy(colindexs, vc_.begin());
  }
  std::size_t count() noexcept
  {
    return std::count(std::execution::par_unseq, std::begin(mcurr_.array()), std::end(mcurr_.array()), Occupied);
  }
  FixedMatrix<int, RowCnt, ColCnt> mcurr_;
  bool transform() noexcept
  {
    std::for_each(std::execution::par_unseq, vr_.begin(), vr_.end(), [this](auto i) {
      std::for_each(std::execution::par_unseq, vc_.begin(), vc_.end(), [this, i](auto j) {
        if (Occupied == this->mcurr_(i, j) && this->surroundOccupiedNum(i, j) >= 4) {
          this->mnext_(i, j) = Empty;
        } else if (Empty == this->mcurr_(i, j) && this->surroundOccupiedNum(i, j) == 0) {
          this->mnext_(i, j) = Occupied;
        }
      });
    });
    if (mnext_ != mcurr_) {
      mcurr_ = mnext_;
      return false;
    } else {
      return true;
    }
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    LightMatrix<101, 94> lm;
    static char state[256];
    state['.'] = Floor;
    state['L'] = Empty;
    state['#'] = Occupied;

    for (std::size_t j = 0; (ifs >> s); ++j) {
      std::transform(s.begin(), s.end(), lm.mcurr_.row(j + 1).begin() + 1, [](char c) { return state[c]; });
    }
    lm.mnext_ = lm.mcurr_;
    for (; !lm.transform();) {
    }

    fmt::print("{}\n", lm.count());
  }
}