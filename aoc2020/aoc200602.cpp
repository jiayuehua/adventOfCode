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
#include <algorithm>

int main(int argc, char **argv)
{
  namespace views = ranges::views;
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::vector<std::string> v;
    v.reserve(1000);
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    std::move(ib, ie, std::back_inserter(v));
    auto validanswers = v | views::split(std::string("###")) | views::transform([](auto &&g) {
      auto gb = g | views::transform([](auto sv) {
        std::string s(sv);
        ranges::sort(s);
        return s;
      }) | views::common;
      std::string s = gb.front();

      std::string inter = std::reduce(gb.begin(), gb.end(), s, [](const std::string &l, const std::string &r) {
        std::string str;
        std::set_intersection(l.cbegin(), l.cend(), r.cbegin(), r.cend(), std::back_inserter(str));
        return str;
      });
      return inter.size();
    });
    auto sum = std::reduce(validanswers.begin(), validanswers.end(), 0);
    fmt::print("{}\n", sum);
  }
}