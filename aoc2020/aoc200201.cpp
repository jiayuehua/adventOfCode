#include <fstream>
#include <sstream>
#include <string_view>
#include <cctype>
#include <fmt/format.h>
#include <range/v3/all.hpp>
#include <string>
#include <array>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <algorithm>

int main(int argc, char **argv)
{
  namespace views = ranges::views;
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    std::vector<std::string> v;
    std::move(ib, ie, std::back_inserter(v));

    auto vb = views::all(v)
              | views::chunk(3) | views::transform([](auto &&range) {
                  std::array<std::string, 3> a;
                  for (std::size_t i = 0; auto &&s : range) {
                    a[i] = s;
                    ++i;
                  }
                  std::istringstream ist(a[0]);
                  int l, r;
                  ist >> l >> r;
                  r = -r;
                  char c = a[1][0];
                  int m = static_cast<int>(ranges::count(a[2], c));
                  return (l <= m && m <= r);
                });
    auto r = ranges::count(vb, true);
    fmt::print("{}\n", r);
    return 0;
  }
}
