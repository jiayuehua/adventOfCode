#include <range/v3/all.hpp>
#include <unordered_set>
#include <fstream>
#include <iterator>
#include <fmt/format.h>
#include <optional>


int main(int argc, char **argv)
{
  if (argc > 1) {
    fmt::print("{}\n", argv[1]);
    std::ifstream ifs(argv[1]);
    std::string s;
    ifs >> s;
    int n = 0;
    fmt::print("{}\n", s);
    ranges::for_each(s, [&n](char c) {
      static constexpr int a[2] = { -1, 1 };

      n += a[c == '('];
      return n == -1;
    });
    fmt::print("{}\n", n);
  }
}