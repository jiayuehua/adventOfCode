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
#include <execution>

namespace views = ranges::views;

int main(int argc, char **argv)
{
  if (argc > 1) {

    std::ifstream ifs(argv[1]);
    std::vector<std::string> v;
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    std::move(ib, ie, std::back_inserter(v));
    static bool vowols[256]{};
    ranges::fill(vowols, false);
    vowols['a'] = true;
    vowols['e'] = true;
    vowols['i'] = true;
    vowols['o'] = true;
    vowols['u'] = true;
    auto bitset = views::all(v) | views::transform([](const std::string &s) {
      bool ca = ranges::count_if(s, [](char c) {
        return vowols[c];
      }) > 2;
      bool cb = ranges::adjacent_find(s, [](char a, char b) { return a == b; }) != s.end();
      bool cc = s.find("ab") == std::string::npos and s.find("cd") == std::string::npos and s.find("pq") == std::string::npos and s.find("xy") == std::string::npos;

      return ca and cb and cc;
    });
    auto n = ranges::count(bitset, true);
    fmt::print("{}\n", n);
  }
}