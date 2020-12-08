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
    auto groups = v | views::split(std::string("###"))
                  | views::transform([](auto &&s) {
                      std::array<bool, 256> count{};
                      ranges::for_each(s, [&count](std::string_view sv) {
                        ranges::for_each(sv, [&count](char c) { count[c] = true; });
                      });
                      return ranges::count(count, true);
                    });
    auto n = std::reduce(groups.begin(), groups.end(), 0);

    fmt::print("{}\n", n);
  }
}