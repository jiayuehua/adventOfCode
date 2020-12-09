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


//void f(std::size_t x_max, std::size_t y_max)// test layout and basic access
//{
//  std::cout << "\nf(" << x_max << "," << y_max << "):\n";
//
//  Matrix<double> a(x_max, y_max);
//
//  for (std::size_t x = 0; x < x_max; x++)// initialize
//    for (std::size_t y = 0; y < y_max; y++)
//      a[x][y] = static_cast<double>(x * 1 + y * 10);
//
//  std::cout << "C-style access used to initialize:\n"
//            << a;
//
//  for (std::size_t x = 0; x < x_max; x++)
//    for (std::size_t y = 0; y < y_max; y++)
//      a(x, y) = static_cast<double>(x * 1 + y * 10);
//  std::cout << "Fortran-style access used to initialize:\n"
//            << a;
//
//  std::cout << "addresses: \n";
//
//  for (std::size_t x = 0; x < x_max; x++)
//    for (std::size_t y = 0; y < y_max; y++)
//      std::cout << "(" << x << "," << y << ") at " << &a[x][y] - &a[0][0] << "\n";
//  std::cout << "columns :\n";
//
//  for (std::size_t x = 0; x < x_max; x++) {
//    std::cout << "column " << x << ":\n";
//    for (Slice_iter<double> c = a.column(x); c != c.end(); ++c)
//      std::cout << "\t" << *c << "\n";
//  }
//
//  std::cout << "rows :\n";
//
//  for (std::size_t y = 0; y < y_max; y++) {
//    std::cout << "row " << y << ":";
//    for (Slice_iter<double> r = a.row(y); r != r.end(); ++r)
//      std::cout << "\t" << *r;
//    std::cout << "\n";
//  }
//}
//
//void g(std::size_t x_max, std::size_t y_max)// check multiplication
//{
//  std::cout << "\ng(" << x_max << "," << y_max << "):\n";
//
//  Matrix<double> a(x_max, y_max);
//
//  for (std::size_t x = 0; x < x_max; x++)// initialize
//    for (std::size_t y = 0; y < y_max; y++)
//      a[x][y] = static_cast<double>(x * 1 + y * 10);
//
//  std::valarray<double> r(2u, x_max);
//  std::cout << "a*v: " << a * r << std::endl;
//
//  std::valarray<double> c(2u, y_max);
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
void turnon(Matrix<bool> &a, std::size_t sx, std::size_t sy, std::size_t ex, std::size_t ey) noexcept
{
  for (auto i = sx; i < ex; ++i) {
    for (auto j = sy; j < ey; ++j) {
      a(i, j) = true;
    }
  }
}

void turnoff(Matrix<bool> &a, std::size_t sx, std::size_t sy, std::size_t ex, std::size_t ey) noexcept
{
  for (auto i = sx; i < ex; ++i) {
    for (auto j = sy; j < ey; ++j)
      a(i, j) = false;
  }
}
//void toggle(bool **a, int sx, int sy, int ex, int ey) noexcept
void toggle(Matrix<bool> &a, std::size_t sx, std::size_t sy, std::size_t ex, std::size_t ey) noexcept
{
  for (auto i = sx; i < ex; ++i) {
    for (auto j = sy; j < ey; ++j)
      a(i, j) = !a(i, j);
  }
}
namespace views = ranges::views;

int main(int argc, char **argv)
{
  // foo();

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
    Matrix<bool> pa(1000, 1000);
    typedef void (*Action)(Matrix<bool> &, std::size_t sx, std::size_t sy, std::size_t ex, std::size_t ey) noexcept;

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

    auto n = ranges::count(std::begin(pa.array()), std::end(pa.array()), true);
    fmt::print("{}", n);
  }
}