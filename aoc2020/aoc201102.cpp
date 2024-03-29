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
template<int RowCnt, int ColCnt>
struct LightMatrix
{
  struct Direction
  {
    int x_;
    int y_;
  };
  Direction d_[8] = { { 0, -1 }, { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 } };
  bool validpos(int i, int j) const noexcept
  {
    return (i >= 0) && (i < RowCnt) && (j >= 0) && (j < ColCnt);
  }

  bool occupied(int i, int j, Direction d) const noexcept
  {
    for (i += d.x_, j += d.y_; validpos(i, j) && mcurr_((i), (j)) != Empty && mcurr_((i), (j)) != Occupied; i += d.x_, j += d.y_) {
    }
    return validpos(i, j) && mcurr_((i), (j)) == Occupied;
  }
  int surroundOccupiedNum(int i, int j) const noexcept
  {
    int cnt = 0;
    for (int k = 0; k < 8; ++k) {
      cnt += occupied(i, j, d_[k]);
    }
    return cnt;
  }


public:
  FixedMatrix<int, RowCnt, ColCnt> mcurr_;
  FixedMatrix<int, RowCnt, ColCnt> mnext_;

private:
  std::vector<int> vr_;
  std::vector<int> vc_;

public:
  LightMatrix() noexcept
    : vr_(static_cast<std::size_t>(mcurr_.rowCount() - 2)),
      vc_(static_cast<std::size_t>(mcurr_.colCount() - 2))
  {
    std::size_t start = 0;
    auto indexs = views::iota(start) | views::drop(1) | views::take(mcurr_.rowCount() - 2);
    auto colindexs = views::iota(start) | views::drop(1) | views::take(mcurr_.colCount() - 2);
    ranges::copy(indexs, vr_.begin());
    ranges::copy(colindexs, vc_.begin());
  }
  auto count() noexcept
  {
    return std::count(std::execution::par_unseq, std::begin(mcurr_.array()), std::end(mcurr_.array()), Occupied);
  }
  bool transform() noexcept
  {
    std::for_each(std::execution::par_unseq, vr_.begin(), vr_.end(), [this](auto i) {
      std::for_each(std::execution::par_unseq, vc_.begin(), vc_.end(), [this, i](auto j) {
        if (Occupied == this->mcurr_(i, j) && this->surroundOccupiedNum(i, j) >= 5) {
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

    state[static_cast<int>('.')] = Floor;
    state[static_cast<int>('L')] = Empty;
    state[static_cast<int>('#')] = Occupied;
    for (int j = 0; (ifs >> s); ++j) {
      std::transform(s.begin(), s.end(), lm.mcurr_.row(j + 1).begin() + 1, [](char c) { return state[static_cast<int>(c)]; });
    }
    lm.mnext_ = lm.mcurr_;
    for (; !lm.transform();) {
    }

    fmt::print("{}\n", lm.count());
  }
}