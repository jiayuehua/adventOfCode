#include <fstream>
#include <iostream>
#include <fmt/format.h>
#include <cstdint>
#include <numeric>
#include <algorithm>
#include <string>
#include <range/v3/algorithm.hpp>
#include "../aoc2020/combinations_algo.h"
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::istream_iterator<std::string> b(ifs);
    std::istream_iterator<std::string> e;
    std::vector<std::string> vs(b, e);
    std::string_view resultl, resultr;
    for_each_combination(vs.begin(), vs.begin() + 2, vs.end(), [&resultl, &resultr](auto f, auto e) {
      auto [l, r] = ranges::mismatch(*f, *(f + 1));
      ++l;
      ++r;
      auto le = (*f).end();
      auto re = (*(f + 1)).end();
      if (ranges::equal(l, le, r, re)) {
        fmt::print("{}{}\n", std::string_view(f->begin(), l - 1), std::string_view(l, le));
        return true;
      }
      return false;
    });
  }
}