#include <fstream>
#include <sstream>
#include <iostream>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <deque>
#include <algorithm>
#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
namespace views = ranges::views;
struct Game
{
  std::deque<int> qa_{
    2,
    31,
    14,
    45,
    33,
    18,
    29,
    36,
    44,
    47,
    38,
    6,
    9,
    5,
    48,
    17,
    50,
    41,
    4,
    21,
    42,
    23,
    25,
    28,
    3
  };
  std::deque<int> qb_{
    26,
    16,
    27,
    12,
    49,
    32,
    19,
    46,
    37,
    15,
    10,
    30,
    11,
    24,
    1,
    40,
    7,
    8,
    43,
    34,
    20,
    35,
    22,
    39,
    13
  };
  void round()
  {
    while (!qa_.empty() && !qb_.empty()) {
      int a = qa_.front();
      int b = qb_.front();
      qa_.pop_front();
      qb_.pop_front();
      if (a < b) {
        qb_.push_back(b);
        qb_.push_back(a);
      } else {
        qa_.push_back(a);
        qa_.push_back(b);
      }
    }
  }
  int score() const
  {
    int n = qa_.size() + qb_.size();
    auto view = views::ints(1, n + 1) | views::reverse;
    //fmt::print("{},{}", n, view.size());
    std::vector<int> v(view.begin(), view.end());
    if (!qa_.empty()) {
      return ranges::inner_product(v, qa_, 0);
    } else {
      return ranges::inner_product(v, qb_, 0);
    }
  }
};


int main(int argc, char **argv)
{
  Game g;
  g.round();
  fmt::print("{}\n", g.score());
}