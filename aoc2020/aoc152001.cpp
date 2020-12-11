#include <iostream>
#include <fmt/format.h>
#include <numeric>
#include <execution>
#include <range/v3/all.hpp>

namespace views = ranges::views;

int getdivisor(int n) noexcept
{
  int sum = 0;
  for (int i = 1; i <= sqrt(n); ++i) {
    if (n % i == 0) {
      sum += i;
      if (i * i != n) {
        sum += n / i;
      }
    }
  }
  if (sum >= 3600000) {
    return n;
  } else {
    return 3600001;
  }
}
int min() noexcept
{
  auto indexs = views::ints | views::drop(1) | views::take(3600000);
  std::vector<int> v(3600000);
  ranges::copy(indexs, v.begin());
  auto n = std::transform_reduce(
    std::execution::par_unseq, v.begin(), v.end(), 3600001, [](int i, int j) { return std::min(i, j); }, &getdivisor);
  return n;
}


int main(int argc, char **argv)
{
  fmt::print("minindex:{}\n", min());
}