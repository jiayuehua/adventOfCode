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
  static inline constexpr int Mid = -1;
  //static inline constexpr int Infinity = 99;
  void computemaxarea()
  {
    int width = right - left + 1;
    int hight = bottom - top + 1;
    ranges::for_each(p, [this](std::pair<int, int> &p) {
      p.first -= this->top;
      p.second -= this->left;
    });

    Matrix<int> m(hight, width);
    for (int i = 0; i < m.rowCount(); ++i) {
      for (int j = 0; j < m.colCount(); ++j) {
        std::vector<int> b(p.size());
        auto iv = views::ints | views::take(b.size()) | views::common;
        std::vector<int> indexs(iv.begin(), iv.end());

        ranges::transform(p, b.begin(), [i, j](std::pair<int, int> point) {
          return std::abs(i - point.first) + std::abs(j - point.second);
        });
        auto z = views::zip(b, indexs);
        ranges::partial_sort(z, z.begin() + 2);
        if (b.front() == *(b.begin() + 1)) {
          m(i, j) = Mid;
        } else {
          m(i, j) = indexs.front();
        }
      }
    }
    std::set<int> infinitys;
    infinitys.insert(Mid);
    for (int i = 0; i < m.rowCount(); ++i) {
      infinitys.insert(m(i, 0));
      infinitys.insert(m(i, m.colCount() - 1));
    }
    for (int j = 0; j < m.colCount(); ++j) {
      infinitys.insert(m(0, j));
      infinitys.insert(m(m.rowCount() - 1, j));
    }
    //std::cout << m << std::endl;
    std::map<int, int> counts;
    for (int i = 0; i < m.rowCount(); ++i) {
      for (int j = 0; j < m.colCount(); ++j) {
        if (!infinitys.contains(m(i, j))) {
          ++counts[m(i, j)];
        }
      }
    }
    int max = 0;
    auto areas = counts | views::values;
    maxarea = *ranges::max_element(areas);
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
