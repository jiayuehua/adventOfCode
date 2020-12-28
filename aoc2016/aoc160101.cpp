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
using gint = std::int64_t;
using Coordinate = std::complex<gint>;
enum Command {
  TurnRight,
  TurnLeft
};
class Car
{
  std::complex<gint> pos_{ 0, 0 };
  std::complex<gint> direction_{ 1, 0 };
  std::complex<gint> turn_[2]{
    { 0, -1 },
    { 0, 1 }
  };

public:
  constexpr gint distance() const noexcept
  {
    return std::abs(pos_.real()) + std::abs(pos_.imag());
  }

  void process(Command command, gint value) noexcept
  {
    direction_ *= turn_[command];
    pos_ += direction_ * value;
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    char c;
    int forward;
    Car car;
    Command com[256];
    com['L'] = Command::TurnLeft;
    com['R'] = Command::TurnRight;
    while (ifs >> c >> forward) {
      car.process(com[c], forward);
    }
    fmt::print("d:{}\n", car.distance());
  }
}