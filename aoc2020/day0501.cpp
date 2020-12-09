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
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    auto seatNum = views::all(v) | views::transform([&a](auto &&i) {
      fmt::print("{}\n", i.size());
      std::string s = "0000000111";
      ranges::transform(i, s.begin(), [&a](char c) {
        auto ci = static_cast<std::size_t>(c);
        return a[ci];
      });
      int n = std::stoi(s, 0, 2);
      return n;
    });
    ranges::for_each(seatNum, [](auto i) {
      fmt::print("{}\n", i);
    });
    auto p = ranges::max_element(seatNum);
    fmt::print("{}\n", *p);
    return 0;
  }
}
