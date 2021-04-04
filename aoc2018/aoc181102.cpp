#include <complex>
#include <exception>
#include <fstream>
#include <set>
#include <sstream>
#include <iostream>
#include <tuple>
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
  std::tuple<int, int, int> maxTotalPowerIndex() const
  {
    auto m = std::numeric_limits<int>::min();
    std::tuple<int, int, int> p{ 0, 0, 0 };
    for (int K = 1; K < 301; ++K) {
      for (int i = 0; i < N - (K - 1); ++i) {
        for (int j = 0; j < N - (K - 1); ++j) {
          auto s = 0;
          for (int a = j; a < j + K; ++a) {
            for (int b = i; b < i + K; ++b) {
              s += m_(a, b);
            }
          }
          if (s > m) {
            //fmt::print("s:{}\n", s);
            p = std::make_tuple(i + 1, j + 1, K);
            m = s;
          }
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
  //c.output(32, 44);
  auto [i, j, k] = c.maxTotalPowerIndex();
  fmt::print("{},{},{}\n", i, j, k);
}
