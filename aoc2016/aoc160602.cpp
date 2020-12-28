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

    auto chars = views::iota('a') | views::take(26);
    std::string code;
    for (int i = 0; i < 8; ++i) {
      std::vector<int> charsCount(256);
      auto v = s | views::drop(i) | views::stride(8);
      ranges::for_each(v, [&charsCount](char c) { ++charsCount[c]; });
      char mc = 'a';
      auto minCount = 10000;

      for (char c : chars) {
        if ((charsCount[c] < minCount) && (charsCount[c])) {
          minCount = charsCount[c];
          mc = c;
        }
      }

      code += mc;
    }
    fmt::print("{}", code);
    fmt::print("\n");
  }
}