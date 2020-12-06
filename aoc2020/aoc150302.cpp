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
    std::pair<int, int> q{ 0, 0 };

    static std::pair<int, int> dir[256];
    dir['<'] = std::pair{ -1, 0 };
    dir['>'] = std::pair{ 1, 0 };
    dir['^'] = std::pair{ 0, 1 };
    dir['v'] = std::pair{ 0, -1 };
    std::map<std::pair<int, int>, int> m;
    m[p] = 1;
    auto chunks = views::all(path) | views::chunk(2);
    ranges::for_each(chunks,
      [p, q, &m](auto chunk) mutable {
        p.first += dir[chunk.front()].first;
        p.second += dir[chunk.front()].second;
        q.first += dir[chunk.back()].first;
        q.second += dir[chunk.back()].second;
        ++m[p];
        ++m[q];
      });
    fmt::print("{}\n", m.size());
  }
}