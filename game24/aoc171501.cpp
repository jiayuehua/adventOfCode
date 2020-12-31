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
struct Generator
{
  int i_ = 0;
  gint start_;
  bool operator==(const Generator &r) const
  {
    return i_ == r.i_;
  }
  bool operator!=(const Generator &r) const
  {
    return i_ != r.i_;
  }

  //constexpr auto operator<=>(const Generator &r) const
  //{
  //  return i_ <=> r.i_;
  //}
  int factor_ = 16807;
  using value_type = gint;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::input_iterator_tag;
  using reference = gint &;
  using pointer_type = gint *;
  Generator(gint start, int factor) : start_(start), factor_(factor)
  {
    start_ *= factor_;
    start_ &= static_cast<gint>(std::numeric_limits<int>::max());
  }
  Generator begin() const
  {
    return *this;
  }
  Generator end() const
  {
    Generator g(*this);
    //g.i_ = 5;
    g.i_ = 40'000'000;
    return g;
  }

  void operator++()
  {
    start_ *= factor_;
    start_ %= static_cast<gint>(2147483647ul);
    ++i_;
  }
  int operator*() const
  {
    //std::cout << factor_ << ":" << i_ << "," << start_ << std::endl;
    ;
    return start_ & 65535;
  }
};
int main()
{
  Generator a(873, 16807);
  Generator b(583, 48271);
  //for (auto i = a.begin(); i != a.end(); ++i) {
  //  std::cout << *i << std::endl;
  //}
  //return 0;
  int n = std::transform_reduce(a.begin(), a.end(), b.begin(), 0, std::plus<>{}, std::equal_to<>{});
  std::cout << n << std::endl;
}
