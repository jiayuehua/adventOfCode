#include <complex>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/circular_buffer.hpp>
#include <range/v3/all.hpp>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <numeric>
#include <algorithm>
namespace views = ranges::views;
using gint = std::int64_t;
class Generator : public ranges::view_facade<Generator>
{
  int i_ = 0;
  gint start_;
  int factor_ = 16807;
  friend ranges::range_access;
  int read() const
  {
    return start_ & 65535;
  }
  void next()
  {
    start_ *= factor_;
    start_ %= static_cast<gint>(2147483647ul);
  }
  bool equal(ranges::default_sentinel_t) const { return false; }

public:
  Generator(gint start, int factor) : start_(start), factor_(factor)
  {
    start_ *= factor_;
    start_ &= static_cast<gint>(std::numeric_limits<int>::max());
  }
  Generator() {}
};
int main()
{
  Generator a(873, 16807);
  auto left = views::filter(a, [](auto i) { return (i & 0b11) == 0; }) | views::take(5000000) | views::common;

  Generator b(583, 48271);
  auto right = views::filter(b, [](auto i) { return (i & 0b111) == 0; }) | views::take(5000000) | views::common;
  int n = std::transform_reduce(left.begin(), left.end(), right.begin(), 0, std::plus<>{}, std::equal_to<>{});
  std::cout << n << std::endl;
}
