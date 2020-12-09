#include <range/v3/all.hpp>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <fmt/format.h>
#include <optional>
#include <cstdio>
#include <numeric>
#include <string>
#include <execution>
#include "matrix.h"
//-------------------------------------------------------------
//
//
//void f(std::size_t x_max, std::size_t y_max)// test layout and basic access
//{
//  std::cout << "\nf(" << x_max << "," << y_max << "):\n";
//
//  Matrix<double> a(x_max, y_max);
//
//  for (int x = 0; x < x_max; x++)// initialize
//    for (int y = 0; y < y_max; y++)
//      a[x][y] = x + y * 10;
//
//  std::cout << "C-style access used to initialize:\n"
//            << a;
//
//  for (int x = 0; x < x_max; x++)
//    for (int y = 0; y < y_max; y++)
//      a(x, y) = x + y * 10;
//
//  std::cout << "Fortran-style access used to initialize:\n"
//            << a;
//
//  std::cout << "addresses: \n";
//
//  for (int x = 0; x < x_max; x++)
//    for (int y = 0; y < y_max; y++)
//      std::cout << "(" << x << "," << y << ") at " << &a[x][y] - &a[0][0] << "\n";
//  std::cout << "columns :\n";
//
//  for (int x = 0; x < x_max; x++) {
//    std::cout << "column " << x << ":\n";
//    for (Slice_iter<double> c = a.column(x); c != c.end(); ++c)
//      std::cout << "\t" << *c << "\n";
//  }
//
//  std::cout << "rows :\n";
//
//  for (int y = 0; y < y_max; y++) {
//    std::cout << "row " << y << ":";
//    for (Slice_iter<double> r = a.row(y); r != r.end(); ++r)
//      std::cout << "\t" << *r;
//    std::cout << "\n";
//  }
//}
//void g(int x_max, int y_max)// check multiplication
//{
//  std::cout << "\ng(" << x_max << "," << y_max << "):\n";
//
//  Matrix<double> a(x_max, y_max);
//
//  for (int x = 0; x < x_max; x++)// initialize
//    for (int y = 0; y < y_max; y++)
//      a[x][y] = x + y * 10;
//
//  std::valarray<double> r(2, x_max);
//  std::cout << "a*v: " << a * r << std::endl;
//  std::cout << "m*v: " << (a * r) << std::endl;
//
//  std::valarray<double> c(2, y_max);
//  std::cout << "v*a: " << c * a << std::endl;
//}
//
//void foo()
//{
//  f(3, 4);
//  f(4, 3);
//
//  g(3, 4);
//  g(4, 3);
//}
void turnon(Matrix<int> &a, std::size_t sx, std::size_t sy, std::size_t ex, std::size_t ey) noexcept
{
  for (auto i = sx; i < ex; ++i) {
    for (auto j = sy; j < ey; ++j) {
      ++a(i, j);
    }
  }
}

void turnoff(Matrix<int> &a, std::size_t sx, std::size_t sy, std::size_t ex, std::size_t ey) noexcept
{
  for (auto i = sx; i < ex; ++i) {
    for (auto j = sy; j < ey; ++j)
      a(i, j) = std::max(a(i, j) - 1, 0);
  }
}
void toggle(Matrix<int> &a, std::size_t sx, std::size_t sy, std::size_t ex, std::size_t ey) noexcept
{
  for (auto i = sx; i < ex; ++i) {
    for (auto j = sy; j < ey; ++j)
      a(i, j) += 2;
  }
}
namespace views = ranges::views;

int main(int argc, char **argv)
{

  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    std::vector<std::string> v;
    while (std::getline(ifs, s)) {
      v.push_back(s);
    }
    v.reserve(1024);
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    std::move(ib, ie, std::back_inserter(v));
    Matrix<int> pa(1000, 1000);
    typedef void (*Action)(Matrix<int> &, std::size_t sx, std::size_t sy, std::size_t ex, std::size_t xy) noexcept;

    static Action actions[] = {
      turnoff,
      turnon,
      toggle
    };


    ranges::for_each(v, [&pa](const std::string &str) mutable {
      std::istringstream ist(str);
      int action;
      std::size_t sx, sy, ex, ey;
      std::string ignore;
      ist >> action >> sx >> sy >> ignore >> ex >> ey;
      (actions[action])(pa, sx, sy, ex + 1, ey + 1);
    });

    int n = std::reduce(std::begin(pa.array()), std::end(pa.array()), 0);
    fmt::print("{}", n);
  }
}