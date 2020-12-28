#include <boost/circular_buffer.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include <../aoc2020/combinations_algo.h>
namespace views = ranges::views;

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string line;
    int n = 0;
    while (std::getline(ifs, line)) {
      int t = 0;
      auto f = [&t](auto b, auto e) {
        if ((*b % *(b + 1)) == 0) {
          t += (*b) / *(b + 1);
        }
        return false;
      };
      std::istringstream iss(line);
      std::istream_iterator<int> b(iss);
      std::istream_iterator<int> e;
      std::vector<int> v;
      std::copy(b, e, std::back_inserter(v));
      for_each_permutation(v.begin(), v.begin() + 2, v.end(), f);
      n += t;
    }
    std::cout << n << std::endl;
  }
}