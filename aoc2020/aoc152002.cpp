#include <iostream>
#include <fmt/format.h>
#include <numeric>
#include <execution>
#include <range/v3/all.hpp>

namespace views = ranges::views;
int min() noexcept
{
  std::size_t sz = 3600000;
  auto indexs = views::ints | views::drop(1) | views::take(sz);
  std::vector<int> va(sz);
  std::vector<int> v(sz);
  ranges::copy(indexs, va.begin());
  std::for_each(va.begin(), va.end(), [b = v.begin(), e = v.end()](int s) {
    int times = 50;
    int j = 0;
    for (auto i = b + s - 1; i < e && j < times; i += s) {
      ++j;
      *i += 11 * s;
    }
  });
  auto firstId = std::transform_reduce(
    std::execution::par_unseq, va.begin(), va.end(), v.begin(), 3600001, [](int i, int j) { return std::min(i, j); }, [](int i, int n) {
  if (n >= 36000000) {
    return i;
  } else {
    return 3600001;
  } });
  return firstId;
}

int main()
{
  fmt::print("minindex:{}\n", min());
}