#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <boost/variant.hpp>
#include <unordered_map>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <range/v3/algorithm.hpp>
bool istriangle(std::vector<int> v) noexcept
{
  if (v[0] + v[1] <= v[2]) {
    return false;
  }
  for (int i = 0; i < 2; ++i) {
    std::rotate(v.begin(), v.begin() + 1, v.end());
    if (v[0] + v[1] <= v[2]) {
      return false;
    }
  }
  return true;
}


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    int n = 0;
    while (std::getline(ifs, s)) {
      std::vector<int> v;
      int line;
      std::istringstream iss(s);

      while (iss >> line) {
        v.push_back(line);
      }
      if (istriangle(v)) {
        ++n;
      }
    }
    fmt::print("triangle count:{}", n);
  }
}