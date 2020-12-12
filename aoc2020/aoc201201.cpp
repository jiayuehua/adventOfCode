#include <iostream>
#include <fstream>

#include <fmt/format.h>
#include <string>
#include <utility>
#include <unordered_map>
#include <functional>
#include <cmath>

#include <complex>

using namespace std::complex_literals;
using Direction = std::complex<int>;

struct Position
{
  int x_ = 0;
  int y_ = 0;
  Direction d_ = 1;

  void north(int n) noexcept
  {
    y_ += n;
  }
  void south(int n) noexcept
  {
    y_ -= n;
  }
  void
    east(int n) noexcept
  {
    x_ += n;
  }

  void west(int n) noexcept
  {
    x_ -= n;
  }
  void forward(int n) noexcept
  {
    x_ += n * d_.real();
    y_ += n * d_.imag();
  }
  void right(int n) noexcept
  {
    int diff = n / 90;
    d_ *= std::pow(-1i, diff);
  }
  void left(int n) noexcept
  {
    int diff = n / 90;
    d_ *= std::pow(1i, diff);
  }
};
typedef void (Position::*MemberFunc)(int) noexcept;

int main(int argc, char **argv)
{
  std::unordered_map<char, MemberFunc> callbacks;
  callbacks['L'] = &Position::left;
  callbacks['R'] = &Position::right;
  callbacks['E'] = &Position::east;
  callbacks['S'] = &Position::south;
  callbacks['W'] = &Position::west;
  callbacks['N'] = &Position::north;
  callbacks['F'] = &Position::forward;
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Position p;
    char c;
    int n;
    while (ifs >> c >> n) {
      std::invoke(callbacks[c], p, n);
    }
    fmt::print("{}\n", std::abs(p.x_) + std::abs(p.y_));
  }
}