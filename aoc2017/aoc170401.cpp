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
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string line;
    int validcount = 0;
    while (std::getline(ifs, line)) {
      std::istringstream iss(line);
      std::map<std::string, int> m;
      std::string tmp;
      while (iss >> tmp) {
        ++m[tmp];
      }
      auto v = m | ranges::views::values;
      if (ranges::all_of(v, [](int i) { return i == 1; })) {
        ++validcount;
      }
      std::cout << validcount << std::endl;
    }
  }
}