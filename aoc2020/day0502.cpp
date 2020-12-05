#include <fstream>
#include <sstream>
#include <string_view>
#include <cctype>
#include <fmt/format.h>
#include <range/v3/all.hpp>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <tuple>


int main(int argc, char **argv)
{
  namespace views = ranges::views;
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::array<char, 256> a;
    ranges::fill(a, '0');
    a['R'] = '1';
    a['B'] = '1';

    std::vector<std::string> v;
    v.reserve(1024);
    ranges::move(ranges::istream<std::string>(ifs), std::back_inserter(v));
    auto seatNum = views::all(v) | views::transform([&a](auto &&i) {
      std::string s = "0000000111";
      ranges::transform(i, s.begin(), [&a](char c) {
        return a[c];
      });
      int n = std::stoi(s, 0, 2);
      return n;
    }) | ranges::to<std::vector>;
    ranges::sort(seatNum);
    auto p = ranges::adjacent_find(seatNum, [](auto &&l, auto &&r) { return r - l == 2; });
    fmt::print("{}\n", *p + 1);
    return 0;
  }
}
