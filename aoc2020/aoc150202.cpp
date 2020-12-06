#include <range/v3/all.hpp>
#include <unordered_set>
#include <fstream>
#include <iterator>
#include <fmt/format.h>
#include <optional>
#include <cstdio>
#include <numeric>
#include <string>
#include <execution>
struct Box
{
  int x;
  int y;
  int z;
  constexpr int area() const noexcept
  {
    return 2 * (x * y + y * z + x * z);
  }
  auto operator<=>(const Box &) const = default;
};
namespace views = ranges::views;

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::vector<std::string> v;
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    std::move(ib, ie, std::back_inserter(v));

    auto r = std::transform_reduce(
      std::execution::par_unseq,
      v.begin(),
      v.end(),
      0,
      [](int l, int r) { return l + r; },
      [](const std::string &s) {
        int x, y, z;
        std::sscanf(static_cast<const char *const>(s.c_str()), "%dx%dx%d", &x, &y, &z);
        return 2 * (x + y + z - (std::max(x, std::max(y, z)))) + x * y * z;
      });
    fmt::print("{}\n", r);
  }
}