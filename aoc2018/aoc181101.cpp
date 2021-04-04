#include <complex>
#include <exception>
#include <fstream>
#include <set>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <../aoc2020/matrix.h>
#include <fmt/format.h>
namespace views = ranges::views;
class Coordinate
{
  static inline constexpr int N = 300;
  FixedMatrix<int, N> m_;
  static inline constexpr int S = 6392;
  constexpr int powerlever(int x, int y) const noexcept
  {
    ++x;
    ++y;
    int n = ((y + 10) * x + S) * (y + 10);
    int hd = (n % 1000) / 100;
    return hd - 5;
  }

public:
  Coordinate()
  {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        m_(i, j) = powerlever(i, j);
      }
    }
  }
  std::pair<int, int> maxTotalPowerIndex() const
  {
    auto m = std::numeric_limits<int>::min();
    std::pair<int, int> p{ 0, 0 };
    for (int i = 0; i < N - 2; ++i) {
      for (int j = 0; j < N - 2; ++j) {
        auto s = 0;
        for (int a = j; a < j + 3; ++a) {
          for (int b = i; b < i + 3; ++b) {
            s += m_(a, b);
          }
        }
        if (s > m) {
          fmt::print("s:{}\n", s);
          p = std::make_pair(i + 1, j + 1);
          m = s;
        }
      }
    }
    return p;
  }
  void output(int x, int y) const noexcept
  {
    std::swap(x, y);
    for (int i = x; i < x + 5; ++i) {
      for (int j = y; j < y + 5; ++j) {
        fmt::print("{},", m_(i, j));
      }
      fmt::print("\n===\n");
    }
  }
};
namespace views = ranges::views;
int main(int argc, char **argv)
{
  Coordinate c;
  c.output(32, 44);
  auto [i, j] = c.maxTotalPowerIndex();
  fmt::print("{},{}\n", i, j);
}
