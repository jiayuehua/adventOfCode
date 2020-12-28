#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <boost/variant.hpp>
#include <unordered_map>
#include <algorithm>
#include <range/v3/all.hpp>
#include "matrix.h"
namespace views = ranges::views;
struct Displayer
{
  FixedMatrix<bool, 6, 50> screen_;
  void matrix(int y, int x) noexcept
  {
    for (int i = 0; i < x; ++i) {
      ranges::fill(screen_.row(i).begin(), screen_.row(i).begin() + y, true);
    }
  }
  void rotateRow(int rownum, int n) noexcept
  {
    auto row = screen_.row(rownum);
    std::rotate(row.begin(), screen_.row(rownum).begin() + screen_.colCount() - n, row.end());
  }
  void rotateCol(int colnum, int n) noexcept
  {
    auto col = screen_.column(colnum);
    std::rotate(col.begin(), screen_.column(colnum).begin() + screen_.rowCount() - n, col.end());
  }
  void print() const
  {
    for (int k = 0; k < 10; ++k) {
      int cols = k * 5;
      for (int i = 0; i < 6; ++i) {
        for (int j = cols; j < 5 + cols; ++j) {
          if (screen_(i, j)) {
            fmt::print("#");
          } else {
            fmt::print(".");
          }
        }
        fmt::print("\n");
      }


      fmt::print("\n");
    }
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    typedef void (Displayer::*MemFunc)(int, int) noexcept;
    Displayer d;
    std::map<std::string, MemFunc> m;
    m["rect"] = &Displayer::matrix;
    m["row"] = &Displayer::rotateRow;
    m["column"] = &Displayer::rotateCol;
    std::ifstream ifs(argv[1]);
    std::string s;
    std::string command;
    int x, y;

    for (; ifs >> command >> x >> y;) {
      auto f = m[command];
      (d.*f)(x, y);
    }
    std::cout << ranges::count(d.screen_.array(), true);
    d.print();
  }
}