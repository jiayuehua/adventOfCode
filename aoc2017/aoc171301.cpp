#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <fmt/format.h>
#include <string>
#include <numeric>
#include <execution>
#include <utility>
#include <algorithm>
#include <map>
#include <cstdint>
using std::int64_t;
using gint = int64_t;
//time %N==(N-(pos+i))/N
using std::int64_t;
template<class T>
constexpr T mymod(T n, T N) noexcept
{
  n %= N;
  if (n < 0) {
    n += N;
  }
  return n;
}
gint postoremain(gint pos, gint i, gint N)
{
  return mymod(N - (pos + i + 1), N);
}

struct TimeStamp
{
  static inline constexpr std::array<std::pair<int64_t, int64_t>, 2> primeposs{
    std::pair{ 13l, 0l },
    std::pair{ 91l, 20l },
  };
  static constexpr int64_t reverse(int64_t Mi, int64_t p) noexcept
  {
    Mi %= p;
    for (int i = 1; i < p; ++i) {
      if ((Mi * i) % p == 1) {
        return i;
      }
    }
    return 1;
  }
  static constexpr int64_t firstvalid() noexcept
  {
    int64_t sum = 0;

    int64_t M = 1;
    for (auto [p, i] : primeposs) {
      M *= p;
    }
    for (int i = 0; i < primeposs.size(); ++i) {
      auto [mi, pos] = primeposs[i];
      auto a = postoremain(pos, i, mi);
      auto Mi = M / mi;
      auto ti = reverse(Mi, mi);
      sum += Mi * ti * a;
    }
    return sum % M;
  }
};
int main()
{
  TimeStamp ts;
  fmt::print("firstvalid:{}\n", ts.firstvalid());
}
