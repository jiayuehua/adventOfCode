#include <range/v3/all.hpp>
#include <fstream>
#include <fmt/format.h>
#include <string>
#include <string_view>

namespace views = ranges::views;
int escapelen(std::string_view sv)
{
  int n = 0;
  n += ranges::count(sv, '\\') + ranges::count(sv, '\"');
  n += 2;
  return n;
}

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    int n = 0;
    while (std::getline(ifs, s)) {
      n += escapelen(s);
    }
    fmt::print("{}\n", n);
  }
}