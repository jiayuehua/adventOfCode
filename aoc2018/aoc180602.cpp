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
  int left, right, top, bottom;
  int maxarea;
  static inline constexpr int Maxdis = 10000;
  void computemaxarea()
  {
    int width = right - left + 1;
    int hight = bottom - top + 1;
    ranges::for_each(p, [this](std::pair<int, int> &p) {
      p.first -= this->top;
      p.second -= this->left;
    });

    Matrix<int> m(bottom + 200, right + 200);
    for (int i = 0; i < m.rowCount(); ++i) {
      for (int j = 0; j < m.colCount(); ++j) {
        std::vector<int> b(p.size());
        ranges::transform(p, b.begin(), [i, j](std::pair<int, int> point) {
          return std::abs(i - point.first) + std::abs(j - point.second);
        });
        int dis = ranges::accumulate(b, 0);
        if (dis < Maxdis) {
          ++maxarea;
        }
      }
    }
  }

public:
  int getmaxarea() const
  {
    return maxarea;
  }
  friend std::istream &operator>>(std::istream &is, Coordinate &c)
  {
    int x, y;
    std::string s;
    for (; is >> y >> x;) {
      c.p.emplace_back(x, y);
    }
    auto k = c.p | views::keys;
    auto v = c.p | views::values;
    auto [pl, pr] = ranges::minmax_element(v);
    auto [pt, pb] = ranges::minmax_element(k);
    c.left = *pl;
    c.right = *pr;
    c.top = *pt;
    c.bottom = *pb;
    c.computemaxarea();
    return is;
  }
};
namespace views = ranges::views;
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string c;
    Coordinate cor;
    ifs >> cor;
    std::cout << cor.getmaxarea() << std::endl;
  }
}
