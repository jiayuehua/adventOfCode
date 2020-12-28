#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <boost/variant.hpp>
#include <unordered_map>
#include <range/v3/all.hpp>
#include "combinations_algo.h"
#include "matrix.h"
struct Combinations
{
  FixedMatrix<int, 8, 8> networks_;
  std::array<int, 8> a = { 0, 1, 2, 3, 4, 5, 6, 7 };
  int max = std::numeric_limits<int>::min();
  int max_distance() noexcept
  {
    auto f = [this](auto b, auto e) {
      int s = 0;
      for (; b != e - 1; ++b) {
        s += networks_(*b, *(b + 1));
      }
      max = std::max(s, max);
      return false;
    };
    for_each_reversible_permutation(a.begin(), a.end(), a.end(), f);
    return max;
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    Combinations com;
    std::ifstream ifs(argv[1]);
    std::string s;
    for (int i = 0; i < 7; ++i) {
      int row = i;

      int col = i + 1;
      for (; col < 8; ++col) {
        std::getline(ifs, s);
        std::istringstream iss(s);
        std::string ignore;
        int value;
        iss >> ignore >> ignore >> ignore >> ignore >> value;
        com.networks_(row, col) = value;
        com.networks_(col, row) = value;
      }
    }
    std::cout << com.networks_ << std::endl;
    std::cout << com.max_distance() << std::endl;
  }
}