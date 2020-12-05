#include <fstream>
#include <sstream>
#include <string_view>
#include <cctype>
#include <fmt/format.h>
#include <range/v3/all.hpp>
#include <string>
#include <array>
#include <vector>
#include <tuple>
#include <numeric>
#include <cstdint>

int main(int argc, char **argv)
{
  namespace views = ranges::views;
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::vector<std::string> v;
    ranges::copy(ranges::istream<std::string>(ifs), std::back_inserter(v));
    auto nv = views::all(v) | views::enumerate | views::transform([](auto &&i) {
      std::array<int, 4> res;
      for (auto n : { 1, 3, 5, 7 }) {
        int linenum = std::get<0>(i);
        int colnum = linenum * n;
        std::string_view sv = std::get<1>(i);
        res[n / 2] = sv[colnum % sv.size()] == '#';
      }
      return res;
    });
    std::int64_t sum = 1;
    for (int n = 0; n < 4; ++n) {
      int t = ranges::count_if(nv, [n](auto array) { return array[n] == true; });
      fmt::print("{}\n", t);
      sum *= t;
    }
    auto nvb = views::all(v) | views::enumerate | views::stride(2) | views::transform([](auto &&i) {
      int n = 1;
      int linenum = std::get<0>(i);
      std::string_view sv = std::get<1>(i);
      return sv[linenum % sv.size()] == '#';
    });
    auto n = ranges::count(nvb, true);
    sum *= n;
    fmt::print("{}\n", sum);
    return 0;
  }
}
