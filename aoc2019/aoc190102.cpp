#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <ranges>
//namespace views = ranges::views;
constexpr int fuel(int n) noexcept
{
  int k = n / 3 - 2;
  if (k <= 0) {
    return 0;
  } else {
    return k + fuel(k);
  }
}

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    ranges::istream_view<int> iv(ifs);
    std::vector<int> v;
    ranges::copy(iv, std::back_inserter(v));
    std::cout << std::transform_reduce(v.begin(), v.end(), 0, std::plus{}, &fuel) << std::endl;
  }
}
