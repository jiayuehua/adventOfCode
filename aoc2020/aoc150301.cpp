#include <range/v3/all.hpp>
#include <unordered_set>
#include <fstream>
#include <iterator>
#include <fmt/format.h>
#include <optional>
#include <cstdio>
#include <numeric>
#include <string>
#include <execution>
namespace views = ranges::views;

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string path;
    ifs >> path;
    std::pair<int, int> p{ 0, 0 };

    static std::pair<int, int> dir[256];
    dir['<'] = std::pair{ -1, 0 };
    dir['>'] = std::pair{ 1, 0 };
    dir['^'] = std::pair{ 0, 1 };
    dir['v'] = std::pair{ 0, -1 };
    std::map<std::pair<int, int>, int> m;
    m[p] = 1;

    ranges::for_each(
      path,
      [p, &m](char s) mutable {
        p.first += dir[s].first;
        p.second += dir[s].second;
        ++m[p];
      });
    //int r = ranges::count_if(m, [](auto p) { return p.second; });

    fmt::print("{}\n", m.size());
  }
}