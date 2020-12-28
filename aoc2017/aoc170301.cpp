#include <boost/circular_buffer.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
namespace views = ranges::views;

int main(int argc, char **argv)
{
  int n = 277678;
  int c = 0;
  int i = 1;
  for (;; i += 2) {
    if (n == std::clamp(n, i * i + 1, (i + 2) * (i + 2))) {
      c = (i + 2) * (i + 2) - (i * i);
      break;
    }
  }
  std::cout << i << std::endl;
  std::cout << c << std::endl;
  std::cout << n << std::endl;

  auto corner = ((i + 2) * (i + 2) - n) % (c / 4);
  std::cout << corner << std::endl;
  if (corner > c / 8) {
    corner -= (c / 8);
  } else {
    corner = (c / 8) - corner;
  }
  corner += c / 8;
  std::cout << corner << std::endl;
}