#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <numeric>
#include <iomanip>
#include <range/v3/all.hpp>
#include "matrix.h"

struct Property
{
  int cap_;
  int dur_;
  int fla_;
  int txt_;
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    Matrix<int> m(4, 5);
    int t;
    for (std::size_t i = 0; ifs >> s >> s >> t; ++i) {
      fmt::print("{} ", t);
      s.clear();
      int row = i / 5;
      int j = i % 5;
      m(row, j) = t;
    }
    fmt::print("\n");
    std::cout << m;
    fmt::print("\n");

    std::cout << m;
    fmt::print("\n");
    Matrix<int> mb(4, 5);
    int r = 0;
    for (int i = 0; i < 101; ++i) {
      for (int j = 0; j < 101 - i; ++j) {
        for (int k = 0; k < 101 - i - j; ++k) {
          int l = 100 - i - j - k;
          std::vector<int> v{ i, j, k, l };
          int sum = 1;
          for (int n = 0; n < 4; ++n) {
            int p = std::inner_product(m.column(n).begin(), m.column(n).end(), v.begin(), 0);
            sum *= std::max(0, p);
          }
          r = std::max(r, sum);
        }
      }
    }
    fmt::print("{}\n", r);
  }
}