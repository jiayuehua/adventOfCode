#include <complex>
#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <plf_colony.h>
namespace views = ranges::views;
int length(const std::string &c)
{
  plf::colony<char> v(c.begin(), c.end());
  for (int n = v.size(), last = 0; n != last;) {
    for (auto it = v.begin(); it != v.end();) {
      it = ranges::adjacent_find(v, [](char l, char r) { return l != r && std::tolower(l) == std::tolower(r); });
      if (it != v.end()) {
        auto origin = it;
        std::advance(it, 2);
        v.erase(origin, it);
      }
    }
    last = n;
    n = v.size();
  }
  return v.size();
}
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string c;
    ifs >> c;
    auto v = views::repeat_n(c, 26) | views::enumerate | views::transform([](auto pair) { 
      auto id = std::get<0>(pair);
      auto second = std::get<1>(pair);
      second.erase(ranges::remove_if(second, [id](char c) { return std::tolower(c) == ('a' + id); }),second.end());
      return length(second); });
    std::cout << *ranges::min_element(v) << std::endl;
  }
}
