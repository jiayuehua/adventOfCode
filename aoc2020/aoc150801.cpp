#include <range/v3/all.hpp>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <fmt/format.h>
#include <optional>
#include <cstdio>
#include <numeric>
#include <string>
#include <string_view>
#include <execution>

namespace views = ranges::views;
int escapelen(std::string_view sv)
{
  int n = 0;
  for (auto i = sv.begin(); i != sv.end(); ++i) {
    if (*i == '\\') {
      if (*(i + 1) == 'x') {
        i += 2;
      }
      ++i;
    }
    ++n;
  }
  n -= 2;
  return n;
}

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    int n = 0;
    while (std::getline(ifs, s)) {
      n += s.size() - escapelen(s);
    }
    fmt::print("{}\n", n);
  }
}