#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <set>
#include <map>
#include <fmt/format.h>
#include <numeric>
namespace views = ranges::views;

std::vector<std::string> getPath(std::string const &s, const std::map<std::string, std::string> &m)
{
  std::vector<std::string> v;

  for (auto i = m.find(s); i != m.end(); i = m.find(i->second)) {
    v.push_back(i->second);
  }
  return v;
}

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    ranges::istream_view<std::string> iv(ifs);
    std::map<std::string, std::string> m;
    ranges::for_each(iv, [&m](const std::string &s) {
      auto k = s.substr(4);
      auto v = s.substr(0, 3);
      m[k] = v;
    });
    std::vector you = getPath("YOU", m);
    std::vector san = getPath("SAN", m);
    auto y = you | views::reverse;
    auto s = san | views::reverse;
    auto [l, r] = ranges::mismatch(y, s);
    std::cout << ranges::distance(l, y.end()) + ranges::distance(r, s.end()) << std::endl;
    //std::cout << ranges::distance(r, s.end()) << std::endl;
    //1,2,3
    //1,3
  }
}
