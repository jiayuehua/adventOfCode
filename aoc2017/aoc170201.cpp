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
    int n = 0;
    while (std::getline(ifs, line)) {
      std::istringstream iss(line);
      std::istream_iterator<int> b(iss);
      std::istream_iterator<int> e;
      std::vector<int> v;
      std::copy(b, e, std::back_inserter(v));
      auto [pmin, pmax] = std::minmax_element(v.begin(), v.end());
      n += (*pmax - *pmin);
    }
    std::cout << n << std::endl;
  }
}