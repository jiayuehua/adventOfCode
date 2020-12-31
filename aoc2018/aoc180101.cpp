#include <fstream>
#include <iostream>
#include <fmt/format.h>
#include <cstdint>
#include <numeric>
#include <algorithm>
using gint = std::int64_t;
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::istream_iterator<int> b(ifs);
    std::istream_iterator<int> e;
    auto sum = std::accumulate(b, e, 0);
    fmt::print("{}\n", sum);
  }
}