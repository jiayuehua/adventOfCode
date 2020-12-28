#include <boost/circular_buffer.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
#include "../aoc2020/matrix.h"
#include "../aoc2020/mypair.h"
namespace views = ranges::views;

template<int N>
int firstgreaterthan(FixedMatrix<int, N, N> &m, int dst)
{
  Mypair dir[4] = {
    Mypair{ -1, 0 },
    Mypair{ 0, -1 },
    Mypair{ 1, 0 },
    Mypair{ 0, 1 }
  };
  int di = 0;
  Mypair src{ N / 2, N / 2 };
  m(src.x, src.y) = 1;
  std::cout << m(src.x, src.y) << std::endl;
  m(src.x, src.y + 1) = 1;
  std::cout << m(src.x, src.y + 1) << std::endl;


  for (Mypair cur = src + Mypair{ -1, 1 };; cur += dir[di]) {
    int sum = 0;

    for (int i = -1; i < 2; ++i) {
      for (int j = -1; j < 2; ++j) {
        auto t = cur + Mypair{ i, j };
        sum += m(t.x, t.y);
      }
    }
    m(cur.x, cur.y) = sum;
    if (sum > dst) {
      return sum;
    }
    std::cout << m(cur.x, cur.y) << std::endl;
    if (m(cur.x, cur.y) >= dst) {
      return m(cur.x, cur.y);
    }

    auto diff = cur - src;
    if (diff.y > 0) {
      if (diff.x + 1 == diff.y) {
        di = 0;
      } else if (diff.y == -diff.x) {
        di = 1;
      }
    } else {
      if (diff.y == diff.x) {
        di = 2;
      } else if (diff.y == -diff.x) {
        di = 3;
      }
    }
  }
  return 0;
}

int main(int argc, char **argv)
{
  FixedMatrix<int, 600, 600> m;
  std::cout << firstgreaterthan(m, 277678) << std::endl;
}