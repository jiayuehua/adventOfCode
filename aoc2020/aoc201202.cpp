#include <iostream>
#include <fstream>

#include <fmt/format.h>
#include <string>
#include <utility>
#include <unordered_map>
#include <functional>
#include <cstdint>
#include <complex>
#include <cmath>

using namespace std::complex_literals;


struct Position
{
  std::complex<int> pos_{ 0, 0 };
  std::complex<int> waypoint_{ 10, 1 };
  constexpr static inline std::complex<int> Imaginary_{ 0, 1 };

  void north(int n) noexcept
  {
    waypoint_ += n * Imaginary_;
  }
  void south(int n) noexcept
  {
    waypoint_ -= n * Imaginary_;
  }
  void east(int n) noexcept
  {
    waypoint_ += n * 1;
  }

  void west(int n) noexcept
  {
    waypoint_ -= n * 1;
  }
  void forward(int n) noexcept
  {
    auto d = waypoint_ - pos_;
    pos_ += n * (d);
    waypoint_ = pos_ + d;
  }
  void right(int n) noexcept
  {
    int diff = n / 90;
    auto d = waypoint_ - pos_;
    d *= std::pow(-1i, diff);
    waypoint_ = pos_ + d;
  }
  void left(int n) noexcept
  {
    int diff = n / 90;
    auto d = waypoint_ - pos_;
    d *= std::pow(1i, diff);
    waypoint_ = pos_ + d;
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
    fmt::print("{}\n", std::abs(p.pos_.real()) + std::abs(p.pos_.imag()));
  }
}