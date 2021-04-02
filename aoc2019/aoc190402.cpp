#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <string_view>
namespace views = ranges::views;
bool exactTwoAdj(std::string_view s)
{
  auto i = ranges::adjacent_find(s);
  if (i != ranges::end(s)) {
    if ((i + 2) == s.end() || (*(i + 2) != *i)) {
      return true;
    } else {
      auto j = ranges::adjacent_find(i + 2, s.end(), std::less{});
      s.remove_prefix(j + (j != s.end()) - s.begin());
      return exactTwoAdj(s);
    }
  } else {
    return false;
  }
}

int main(int argc, char **argv)
{
  std::cout << exactTwoAdj("123444") << std::endl;
  auto r = views::ints(387638, 919124) | views::filter([](int i) {
    auto str = std::to_string(i);

    return ranges::is_sorted(str) && exactTwoAdj(str);
  });
  std::cout << ranges::distance(r) << std::endl;
}
