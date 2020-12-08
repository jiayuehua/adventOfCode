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
    v.reserve(1000);
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    std::move(ib, ie, std::back_inserter(v));
    auto bitset = views::all(v) | views::transform([](const std::string &s) {
      auto [first, second] = ranges::mismatch(
        s.begin() + 2, s.end(), s.begin(), s.end() - 2, [](char a, char b) { return a != b; });
      bool ca = (first != s.end());
      //if (ca) {
      //  fmt::print("ca:{}{}\n", s, first - s.begin());
      //}

      auto dupstrpos = views::ints | views::take(s.size() - 4) | views::transform([begin = s.c_str(), end = s.c_str() + s.size()](int i) {
        std::string_view l(begin + i, 2);
        std::string_view r(begin + i + 2, end);
        std::string_view s(begin, end);
        if (r.find(l) != r.npos) {
          fmt::print("{},l={},r={}\n", s, l, r);
        }
        return r.find(l) != r.npos;
      });
      auto cb = (ranges::find(dupstrpos, true) != dupstrpos.end());
      //if (ca and cb) {
      //  fmt::print("ca:{}\n", s);
      //}
      return ca and cb;
    });
    auto n = ranges::count(bitset, true);
    fmt::print("{}\n", n);
  }
}