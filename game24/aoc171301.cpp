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
#include <boost/integer/mod_inverse.hpp>
using std::int64_t;
using gint = int64_t;
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
struct TimeStamp
{

  static constexpr int64_t firstvalid(int r, int pos) noexcept
  {
    std::array<std::pair<int64_t, int64_t>, 2> primeposs{
      std::pair{ 91l, r },
      std::pair{ pos, 0l },
    };

    int64_t sum = 0;

    int64_t M = 1;
    for (auto [p, i] : primeposs) {
      M *= p;
    }
    for (int i = 0; i < primeposs.size(); ++i) {
      auto [mi, a] = primeposs[i];
      auto Mi = M / mi;
      auto ti = boost::integer::mod_inverse(Mi, mi);
      sum += Mi * ti * a;
    }
    return sum % M;
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    int r, p;
    int sum = 0;
    TimeStamp ts;
    for (int i = 0; ifs >> r >> p; ++i) {
      if ((r % ((p - 1) * 2)) == 0) {
        sum += (r * p);
      }
    }
    fmt::print("sum:{}\n", sum);
  }
}
