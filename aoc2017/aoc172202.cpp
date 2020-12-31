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
enum {
  Clean = 0,
  Weakened,
  Infected,
  Flagged
};

class Game
{
  using Position = std::complex<int>;
  constexpr static inline int N = 20001;
  int origin = N / 2;

  FixedMatrix<char, N> m;
  Mypair cur_;
  bool valid() const noexcept
  {
    return (0 <= cur_.x && cur_.x < N && 0 <= cur_.y && cur_.y < N);
  }
  Position startdir_;
  static constexpr Position dir_[4] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };//left,same,right,reverses
  int cnt_ = 0;


public:
  Game() : cur_(origin, origin), startdir_(0, 1)
  {
  }
  int forward(int n)
  {
    for (int i = 0; (i < n) && valid(); ++i) {
      cnt_ += (m(cur_.x, cur_.y) == Weakened);
      turn(m(cur_.x, cur_.y));
      m(cur_.x, cur_.y) = (m(cur_.x, cur_.y) + 1) % 4;
      cur_.x -= startdir_.imag();
      cur_.y += startdir_.real();
    }
    if (!valid()) {
      std::cerr << "invalid index:" << cur_.x << cur_.y << std::endl;
    }
    return cnt_;
  }
  void turn(char state)
  {
    startdir_ *= dir_[state];
  }

  friend std::istream &operator>>(std::istream &is, Game &g)
  {
    std::string s;
    int N = 25;
    for (int i = g.origin - N / 2; std::getline(is, s); ++i) {
      std::vector<int> v(s.size());
      int N = v.size();

      std::transform(s.begin(), s.end(), v.begin(), [](char c) { return (c == '#') * 2; });
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
    //std::cout << g.forward(100) << std::endl;
    std::cout << g.forward(10000000) << std::endl;
    //std::cout << g.forward(9930) << std::endl;
  }
}
