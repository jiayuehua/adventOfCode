#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
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
    std::string st;
    std::string s;
    while (ifs >> st) {
      s += st;
    }

    for (int i = 0; i < 8; ++i) {
      std::vector<int> charsCount(256);
      auto v = s | views::drop(i) | views::stride(8);
      ranges::for_each(v, [&charsCount](char c) { ++charsCount[c]; });
      char mc = 'a';
      auto maxCount = 0;
      auto chars = views::iota('a') | views::take(26);

      for (char c : chars) {
        if (charsCount[c] > maxCount) {
          maxCount = charsCount[c];
          mc = c;
        }
      }
      fmt::print("{}", mc);
    }
    fmt::print("\n");
  }
}