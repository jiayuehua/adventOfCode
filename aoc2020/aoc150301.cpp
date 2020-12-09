#include <range/v3/all.hpp>
#include <map>
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
    dir['<' + 0u] = std::pair{ -1, 0 };
    dir['>' + 0u] = std::pair{ 1, 0 };
    dir['^' + 0u] = std::pair{ 0, 1 };
    dir['v' + 0u] = std::pair{ 0, -1 };
    std::map<std::pair<int, int>, int> m;
    m[p] = 1;

    ranges::for_each(
      path,
      [p, &m](char s) mutable {
        auto ci = static_cast<std::size_t>(s);
        p.first += dir[ci].first;
        p.second += dir[ci].second;
        ++m[p];
      });
    //int r = ranges::count_if(m, [](auto p) { return p.second; });

    fmt::print("{}\n", m.size());
  }
}