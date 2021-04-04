#include <complex>
#include <exception>
#include <fstream>
#include <set>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <../aoc2020/matrix.h>
namespace views = ranges::views;
class Coordinate
{
  std::vector<std::pair<int, int>> p;
  std::vector<std::pair<int, int>> v;
  FixedMatrix<int, 2000> m_;


public:
  Coordinate() {}
  void onestep()
  {
    ranges::transform(p, v, p.begin(), [](std::pair<int, int> l, std::pair<int, int> r) {
      return std::pair{ l.first + r.first, l.second + r.second };
    });
  }
  friend std::istream &operator>>(std::istream &is, Coordinate &c)
  {
    int x, y;
    int vx, vy;
    while (is >> x >> y >> vx >> vy) {
      c.v.push_back(std::pair{ vx, vy });
      c.p.push_back(std::pair{ x + vx * 10000, y + vy * 10000 });
    }
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, Coordinate &c)
  {
    //for (auto i : c.p) {
    //  os << i.first << "," << i.second << "\n";
    //}
    for (auto i = 0; i < 1000; ++i) {
      auto k = c.p | views::keys;
      auto [mi, ma] = ranges::minmax_element(k);
      os << "=i=" << i << ",";
      os << "=k==";
      os << *ma - *mi + 1 << ":";
      os << *mi << "," << *ma << ",";
      //os << *ma << "\n";
      auto v = c.p | views::values;
      auto [miv, mav] = ranges::minmax_element(v);
      os << "=v==";
      os << *mav - *miv + 1 << ":";
      os << *miv << "," << *mav << "\n";
      if (i >= 76 && i <= 86) {
        for (auto y = *miv; y < *mav + 1; ++y) {

          for (auto x = *mi; x < *ma + 1; ++x) {
            if (ranges::find(c.p, std::pair{ x, y }) != c.p.end()) {
              std::cout << '#';
            } else {
              std::cout << '.';
            }
          }
          std::cout << "\n";
        }
      }
      //os << *mav << "\n";
      c.onestep();
      //for (auto i : c.p) {
      //  os << i.first << "," << i.second << "\n";
      //}
    }
    //for (auto i : c.p) {
    //  os << i.first << "," << i.second << "\n";
    //}


    return os;
  }
};
namespace views = ranges::views;
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Coordinate co;
    ifs >> co;
    std::cout << co;
  }
}
