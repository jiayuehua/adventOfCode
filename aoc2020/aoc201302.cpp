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
  static inline constexpr int64_t step_ = 29;
  static inline int64_t start_ = 11l << 43;
  static inline constexpr int64_t forwardsz_ = 1l << 27;
  static inline constexpr std::pair<int64_t, int64_t> relativepos_[8] = {
    { 13, 42 },
    { 17, 43 },
    { 19, 79 },
    { 23, 52 },
    { 37, 66 },
    { 41, 19 },
    { 521, 60 },
    { 661, 29 }
  };
  //static inline constexpr int64_t step_ = 7;
  //static inline int64_t start_ = 1l << 14;
  //static inline constexpr int64_t forwardsz_ = 1l << 18;
  //static inline constexpr std::pair<int64_t, int64_t> relativepos_[4] = {
  //  { 13, 1 },
  //  { 59, 4 },
  //  { 31, 6 },
  //  { 19, 7 }
  //};

  static constexpr int64_t valid(int64_t n) noexcept
  {
    bool r = std::all_of(std::execution::unseq, std::begin(relativepos_), std::end(relativepos_), [n](auto pair) {
      return ((n * step_ + pair.second) % pair.first) == 0l;
    });
    switch (r) {
    case true:
      return n * step_;
    case false:
      return std::numeric_limits<int64_t>::max();
    }
    return std::numeric_limits<int64_t>::max();
  }

  int64_t firstvalidtimestamp() noexcept
  {
    std::vector<int64_t> v(forwardsz_);

    for (int64_t start = start_; start < std::numeric_limits<int64_t>::max(); start += forwardsz_) {
      ranges::copy(views::ints(start_) | views::take(forwardsz_), v.begin());
      auto r = std::transform_reduce(
        std::execution::par_unseq, v.begin(), v.end(), std::numeric_limits<int64_t>::max(), [](int64_t l, int64_t r) { return std::min(l, r); }, [](int64_t i) { return valid(i); });

      if (r != std::numeric_limits<int64_t>::max()) {
        return r;
      }
    }
    return std::numeric_limits<int64_t>::max();
  }
};
int main()
{
  TimeStamp ts;
  fmt::print("firstvalid:{}\n", ts.firstvalidtimestamp());
}