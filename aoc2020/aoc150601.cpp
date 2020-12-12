#include <range/v3/all.hpp>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <fmt/format.h>
#include <optional>
#include <cstdio>
#include <numeric>
#include <string>
#include <execution>
#include "matrix.h"


void turnon(Matrix<bool> &a, int sx, int sy, int ex, int ey) noexcept
{
  for (auto i = sx; i < ex; ++i) {
    for (auto j = sy; j < ey; ++j) {
      a(i, j) = true;
    }
  }
}

void turnoff(Matrix<bool> &a, int sx, int sy, int ex, int ey) noexcept
{
  for (auto i = sx; i < ex; ++i) {
    for (auto j = sy; j < ey; ++j)
      a(i, j) = false;
  }
}
void toggle(Matrix<bool> &a, int sx, int sy, int ex, int ey) noexcept
{
  for (auto i = sx; i < ex; ++i) {
    for (auto j = sy; j < ey; ++j)
      a(i, j) = !a(i, j);
  }
}
namespace views = ranges::views;

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    std::vector<std::string> v;
    while (std::getline(ifs, s)) {
      v.push_back(s);
    }
    v.reserve(1024);
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    std::move(ib, ie, std::back_inserter(v));
    Matrix<bool> pa(1000, 1000);
    typedef void (*Action)(Matrix<bool> &, int sx, int sy, int ex, int ey) noexcept;

    static Action actions[] = {
      turnoff,
      turnon,
      toggle
    };


    ranges::for_each(v, [&pa](const std::string &str) mutable {
      std::istringstream ist(str);
      int action;
      int sx, sy, ex, ey;
      std::string ignore;
      ist >> action >> sx >> sy >> ignore >> ex >> ey;
      (actions[action])(pa, sx, sy, ex + 1, ey + 1);
    });

    auto n = ranges::count(std::begin(pa.array()), std::end(pa.array()), true);
    fmt::print("{}", n);
  }
}