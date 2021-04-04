#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <set>
#include <fmt/format.h>
#include <numeric>
namespace views = ranges::views;

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
    int totalcnt = 0;
    for (auto &&[k, v] : m) {
      int cnt = 1;
      for (auto i = m.find(v); i != m.end(); i = m.find(i->second)) {
        ++cnt;
      }
      totalcnt += cnt;
    }
    std::cout << totalcnt << std::endl;
  }
}
