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
    //std::vector<std::string> v;
    //ranges::move(ranges::istream<std::string>(ifs), std::back_inserter(v));
    std::vector<std::string> v;
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    std::move(ib, ie, std::back_inserter(v));
    auto nv = views::all(v) | views::enumerate | views::transform([](auto &&i) { 
      auto linenum = std::get<0>(i);
      auto colnum=linenum*3;
      std::string_view sv = std::get<1>(i);
      if (sv[colnum % sv.size()] == '#') {
        return true;
      }
      return false; });
    auto n = ranges::count(nv, true);
    fmt::print("{}\n", n);
    return 0;
  }
}
