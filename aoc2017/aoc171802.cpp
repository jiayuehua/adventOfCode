#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <optional>
#include <cctype>
#include <map>
#include <vector>
#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <boost/dynamic_bitset.hpp>
#include <complex>
using namespace std::literals::complex_literals;
#include "../aoc2020/matrix.h"
namespace views = ranges::views;
using Position = std::complex<int>;
class Game
{
  int totalsteps_ = 0;
  static inline constexpr int NX = 202;
  using Network = FixedMatrix<char, NX, NX>;
  Network networks_;
  Position dir_;
  Position cur_;
  std::string path_;
  Position left() const
  {
    return cur_ + dir_ * Position(0, 1);
  }
  Position right() const
  {
    return cur_ + dir_ * Position(0, -1);
  }

  void turnleft()
  {
    dir_ *= 1i;
  }
  void turnright()
  {
    dir_ *= -1i;
  }
  bool isEnd() const
  {
    return curch() == '+';
  }
  char curch(Position pos) const
  {
    return networks_(pos.imag(), pos.real());
  }
  char curch() const
  {
    return networks_(cur_.imag(), cur_.real());
  }
  bool valid(Position pos) const
  {
    return (curch(pos) != ' ');
  }

public:
  auto path() const
  {
    return path_;
  }
  Game() : dir_(0, 1), cur_(27, 0) {}
  friend std::istream &operator>>(std::istream &is, Game &g)
  {
    int i = 0;
    for (std::string s; std::getline(is, s); ++i) {
      ranges::copy(s, g.networks_.row(i).begin());
    }
    return is;
  }
  void onestep()
  {
    if (std::isalpha(curch())) {
      path_.push_back(curch());
    }
    if (isEnd()) {
      if (valid(left())) {
        turnleft();
      } else if (valid(right())) {
        turnright();
      }
    }
    ++totalsteps_;
    cur_ += dir_;
  }
  void walk()
  {
    while (networks_(cur_.imag(), cur_.real()) != ' ') {
      onestep();
    }
  }
  int steps() const
  {
    return totalsteps_;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    Game g;
    std::ifstream iss(argv[1]);
    iss >> g;
    g.walk();
    std::cout << g.path() << std::endl;
    std::cout << g.steps() << std::endl;
  }
}
