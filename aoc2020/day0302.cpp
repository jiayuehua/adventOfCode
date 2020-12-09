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
    //std::vector<std::string> v;
    //ranges::move(ranges::istream<std::string>(ifs), std::back_inserter(v));
    std::vector<std::string> v;
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    std::move(ib, ie, std::back_inserter(v));
    auto nv = views::all(v) | views::enumerate | views::transform([](auto &&i) {
      std::array<int, 4> res;
      for (auto n : { 1, 3, 5, 7 }) {
        auto linenum = static_cast<std::size_t>(std::get<0>(i));
        auto m = static_cast<std::size_t>(n);
        auto colnum = linenum * m;
        std::string_view sv = std::get<1>(i);
        res[m / 2] = sv[colnum % sv.size()] == '#';
      }
      return res;
    });
    std::int64_t sum = 1;
    for (std::size_t n = 0; n < 4; ++n) {
      auto t = ranges::count_if(nv, [n](auto arr) { return arr[n] == true; });
      fmt::print("{}\n", t);
      sum *= t;
    }
    auto nvb = views::all(v) | views::enumerate | views::stride(2) | views::transform([](auto &&i) {
      //int n = 1;
      auto linenum = std::get<0>(i);
      std::string_view sv = std::get<1>(i);
      return sv[linenum % sv.size()] == '#';
    });
    auto n = ranges::count(nvb, true);
    sum *= n;
    fmt::print("{}\n", sum);
    return 0;
  }
}
