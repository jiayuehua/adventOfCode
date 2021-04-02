#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
namespace views = ranges::views;

int main(int argc, char **argv)
{
  if (argc > 1) {
    auto r = views::ints(387638, 919124) | views::filter([](int i) {
      auto str = std::to_string(i);
      if (ranges::is_sorted(str) && ranges::adjacent_find(str) != ranges::end(str)) {
        return true;
      } else {
        return false;
      }
    });
    std::cout << ranges::distance(r) << std::endl;
  }
}
