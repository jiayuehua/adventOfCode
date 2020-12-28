#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <boost/variant.hpp>
#include <unordered_map>
#include <cstdint>
#include <vector>
#include <range/v3/algorithm.hpp>
using gint = std::int64_t;
using Coordinate = std::complex<gint>;
enum Command {
  TurnRight,
  TurnLeft,
  TurnUp,
  TurnDown
};
class Car
{
  std::complex<gint> pos_{ 1, 1 };
  std::complex<gint> turn_[4]{
    { 1, 0 },
    { -1, 0 },
    { 0, -1 },
    { 0, 1 }
  };
  int map_[3][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::vector<int> values_;
  bool validpos(Coordinate pos) const
  {
    return (0 <= pos.real() && pos.real() < 3 && 0 <= pos.imag() && pos.imag() < 3);
  }

  void process(Command command) noexcept
  {
    auto newpos = pos_ + turn_[command];
    if (validpos(newpos)) {
      pos_ = newpos;
    }
  }

public:
  void process(std::vector<Command> const &commands) noexcept
  {
    for (auto command : commands) {
      process(command);
    }
    values_.push_back(map_[pos_.imag()][pos_.real()]);
  }
  std::vector<int> codes() const
  {
    return values_;
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    char c;
    int forward;
    Car car;
    std::string s;
    while (std::getline(ifs, s)) {
      std::vector<Command> coms;
      ranges::transform(s, std::back_inserter(coms), [](char c) {
        Command com[256];
        com['L'] = Command::TurnLeft;
        com['R'] = Command::TurnRight;
        com['U'] = Command::TurnUp;
        com['D'] = Command::TurnDown;
        return com[c];
      });
      car.process(coms);
    }
    for (auto n : car.codes()) {
      fmt::print("{},", n);
    }
    fmt::print("\n");
  }
}