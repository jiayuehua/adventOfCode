#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <fmt/format.h>
#include <string>
#include <numeric>
#include <execution>
#include <utility>
#include <range/v3/all.hpp>
#include <algorithm>
#include <map>
#include <cstdint>
using std::int64_t;
namespace views = ranges::views;

struct TimeStamp
{
  static inline constexpr std::pair<int64_t, int64_t> relativepos_[] = {
    { 13, 13 * 4 - 42 },
    { 17, 17 * 3 - 43 },
    { 19, 19 * 5 - 79 },
    { 23, 23 * 3 - 52 },
    { 37, 37 * 2 - 66 },
    { 41, 41 - 19 },
    { 521, 521 - 60 },
    { 29, 0 },
    { 661, 661 - 29 }
  };
  static constexpr int64_t reverse(int64_t p, int64_t a) noexcept
  {
    for (int i = 1; i < p; ++i) {
      if ((a * i) % p == 1) {
        return i;
      }
    }
    return 1;
  }
  static constexpr int64_t firstvalid() noexcept
  {
    int64_t sum = 0;

    int64_t M = 1;
    for (auto [p, a] : relativepos_) {
      M *= p;
    }
    fmt::print("{}\n", M);

    for (auto [p, a] : relativepos_) {
      auto M0 = M / p;
      auto m0 = (M0) % p;
      auto t0 = reverse(p, m0);
      fmt::print("M0:{},m0:{},t0:{},p:{}\n", M0, m0, t0, p);
      sum += M0 * t0 * a;
    }
    return sum % M;
  }
};
int main()
{
  TimeStamp ts;
  fmt::print("firstvalid:{}\n", ts.firstvalid());
}
