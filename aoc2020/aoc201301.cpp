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
namespace views = ranges::views;
int waittime(int n, const std::vector<int> &v) noexcept
{
  auto vb = v | views::transform([n](int i) { return std::make_pair((i - n % i), i); });
  ranges::for_each(vb, [](auto p) { std::cout << p.first << "," << p.second << ";"; });

  auto it = std::min_element(vb.begin(), vb.end(), [](const auto &l, const auto &r) { return l.first < r.first; });
  return (*it).first * (*it).second;
}
int main(int argc, char **argv)
{
  if (argc > 1) {

    std::ifstream ifs(argv[1]);
    std::vector<int> v;
    int n = 1000677;
    int busid, ignore;
    while (ifs >> busid) {
      v.push_back(busid);
    }

    int t = waittime(n, v);
    fmt::print("{}", t);
  }
}