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

int main(int argc, char **argv)
{
  namespace views = ranges::views;
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    ranges::istream_view<std::string> ist(ifs);
    std::vector<std::string> v;
    ranges::copy(ist, std::back_inserter(v));
    int n = 0;
    auto s = views::all(v)
             | views::chunk(3) | views::transform([](auto &&range) {
                 std::array<std::string, 3> a;
                 for (int i = 0; auto &&s : range) {
                   a[i] = s;
                   ++i;
                 }
                 std::istringstream ist(a[0]);
                 int l, r;
                 ist >> l >> r;
                 r = -r;
                 char c = a[1][0];
                 return a[2].size() >= r && ((a[2][l - 1] == c) + (a[2][r - 1] == c)) == 1;
                 //int n = ranges::count(a[2], c);
                 //return (l <= n && n <= r);
               });
    int r = ranges::count(s, true);
    fmt::print("{}\n", r);
    return 0;
  }
}
