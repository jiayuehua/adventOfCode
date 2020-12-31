#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <optional>
#include <cctype>
#include <map>
#include <algorithm>
#include <vector>
#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <boost/dynamic_bitset.hpp>
#include <complex>
using namespace std::literals::complex_literals;
#include "../aoc2020/matrix.h"
#include "../aoc2020/mypair.h"

namespace views = ranges::views;

class Game
{
  using Position = std::complex<int>;
  constexpr static inline int N = 2001;
  constexpr static inline int DirIndex[2] = { 1, -1 };
  int origin = N / 2;
  FixedMatrix<bool, N> m;
  Mypair cur_;
  Position dir_;
  int cnt_ = 0;


public:
  Game() : cur_(origin, origin), dir_(0, 1)
  {
  }
  int forward(int n)
  {
    for (int i = 0; i < n; ++i) {
      cnt_ += !m(cur_.x, cur_.y);
      turn(m(cur_.x, cur_.y));
      m(cur_.x, cur_.y) = !m(cur_.x, cur_.y);
      cur_.x -= dir_.imag();
      cur_.y += dir_.real();
    }
    return cnt_;
  }
  void turn(bool isinfected)
  {
    dir_ *= Position{ 0, DirIndex[isinfected] };
  }

  friend std::istream &operator>>(std::istream &is, Game &g)
  {
    std::string s;
    int N = 25;
    for (int i = g.origin - N / 2; std::getline(is, s); ++i) {
      std::vector<int> v(s.size());
      int N = v.size();

      std::transform(s.begin(), s.end(), v.begin(), [](char c) { return c == '#'; });
      for (int j = g.origin - N / 2; j < g.origin + N / 2 + 1; ++j) {
        g.m(i, j) = v[j - (g.origin - N / 2)];
      }
    }
    return is;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    Game g;
    std::ifstream iss(argv[1]);
    iss >> g;
    std::cout << g.forward(7) << std::endl;
    std::cout << g.forward(63) << std::endl;
    std::cout << g.forward(9930) << std::endl;
  }
}
