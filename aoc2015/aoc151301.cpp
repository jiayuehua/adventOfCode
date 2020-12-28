#include <array>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <boost/variant.hpp>
#include <unordered_map>
#include "combinations_algo.h"
#include "matrix.h"
struct Combinations
{
  FixedMatrix<int, 8, 8> networks_;
  std::array<int, 8> a = { 0, 1, 2, 3, 4, 5, 6, 7 };
  int max = std::numeric_limits<int>::min();
  int maxhappiness() noexcept
  {
    auto f = [this](auto b, auto e) {
      int s = networks_(*b, *(e - 1));
      s += networks_(*(e - 1), *b);
      for (; b != e - 1; ++b) {
        s += networks_(*b, *(b + 1));
        s += networks_(*(b + 1), *b);
      }
      max = std::max(s, max);
      return false;
    };
    for_each_reversible_circular_permutation(a.begin(), a.end(), a.end(), f);
    return max;
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    Combinations com;
    std::ifstream ifs(argv[1]);
    int i = 0;
    std::unordered_map<std::string, int> m;
    m["gain"] = 1;
    m["lose"] = -1;
    std::string s;
    fmt::print("a\n");
    for (; std::getline(ifs, s); ++i) {
      int row = i / 7;
      int col = i % 7;
      std::istringstream iss(s);
      std::string ignore, sign;
      int value;
      iss >> ignore >> ignore >> sign >> value;
      fmt::print("sign:{},v:{}\n", sign, value);
      value *= m[sign];
      if (col >= row) {
        com.networks_(row, col + 1) = value;
      } else {
        com.networks_(row, col) = value;
      }
    }

    fmt::print("{}\n", com.maxhappiness());
  }
}