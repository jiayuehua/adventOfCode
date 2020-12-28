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
  std::vector<std::pair<std::complex<gint>, std::complex<gint>>> v_;
  std::complex<gint> pos_{ 0, 0 };
  std::complex<gint> direction_{ 1, 0 };
  std::complex<gint> turn_[2]{
    { 0, -1 },
    { 0, 1 }
  };
  Coordinate interPoint_{ 0, 0 };

public:
  constexpr gint distance() const noexcept
  {
    return std::abs(interPoint_.real()) + std::abs(interPoint_.imag());
  }
  bool inter(std::pair<Coordinate, Coordinate> l, std::pair<Coordinate, Coordinate> r)
  {
    auto linestart = l.first;
    if (l.first.real() > l.second.real()) {
      std::swap(l.first, l.second);
    } else if (l.first.imag() > l.second.imag()) {
      std::swap(l.first, l.second);
    }
    if (r.first.real() > r.second.real()) {
      std::swap(r.first, r.second);
    } else if (r.first.imag() > r.second.imag()) {
      std::swap(r.first, r.second);
    }
    auto between = [](auto f, auto l, auto m) {
      return (f <= m) && (m <= l);
    };
    if (l.first.imag() == l.second.imag() && r.first.real() == r.second.real() && between(l.first.real(), l.second.real(), r.first.real()) && between(r.first.imag(), r.second.imag(), l.first.imag())) {
      interPoint_ = Coordinate(r.first.real(), l.first.imag());
      if (interPoint_ != linestart) {
        return true;
      }
    } else {
      swap(l, r);
      if (l.first.imag() == l.second.imag() && r.first.real() == r.second.real() && between(l.first.real(), l.second.real(), r.first.real()) && between(r.first.imag(), r.second.imag(), l.first.imag())) {
        interPoint_ = Coordinate(r.first.real(), l.first.imag());
        if (interPoint_ != linestart) {
          return true;
        }
      }
    }
    return false;
  }
  bool findinter(std::pair<Coordinate, Coordinate> l)
  {
    for (auto r : v_) {
      if (inter(l, r)) {

        return true;
      }
    }
    return false;
  }


  bool process(Command command, gint value) noexcept
  {
    direction_ *= turn_[command];

    auto newpos = pos_ + direction_ * value;

    auto road = std::make_pair(pos_, newpos);
    if (findinter(road)) {
      return true;
    } else {
      v_.push_back(std::make_pair(pos_, newpos));
      pos_ = newpos;
      return false;
    }
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
      auto r = car.process(com[c], forward);
      if (r) {
        fmt::print("d:{}\n", car.distance());
        break;
      }
    }
  }
}