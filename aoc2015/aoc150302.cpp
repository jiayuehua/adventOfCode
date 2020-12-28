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
    std::pair<int, int> q{ 0, 0 };

    static std::pair<int, int> dir[256];
    dir[static_cast<std::size_t>('<')] = std::pair{ -1, 0 };
    dir[static_cast<std::size_t>('>')] = std::pair{ 1, 0 };
    dir[static_cast<std::size_t>('^')] = std::pair{ 0, 1 };
    dir[static_cast<std::size_t>('v')] = std::pair{ 0, -1 };
    std::map<std::pair<int, int>, int> m;
    m[p] = 1;
    auto chunks = views::all(path) | views::chunk(2);
    ranges::for_each(chunks,
      [p, q, &m](auto chunk) mutable {
        std::size_t f = static_cast<std::size_t>(chunk.front());
        std::size_t l = static_cast<std::size_t>(chunk.back());
        p.first += dir[f].first;
        p.second += dir[f].second;
        q.first += dir[l].first;
        q.second += dir[l].second;
        ++m[p];
        ++m[q];
      });
    fmt::print("{}\n", m.size());
  }
}