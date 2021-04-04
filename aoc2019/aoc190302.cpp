#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <complex>
#include <iterator>
#include <range/v3/algorithm.hpp>
using gint = std::int64_t;
using Point = std::complex<gint>;
enum Command {
  Right,
  Up,
  Left,
  Down
};
class Car
{
  std::vector<std::pair<std::complex<gint>, std::complex<gint>>> v_;
  std::vector<gint> roads_;
  std::vector<gint> fromOrigins_;
  std::vector<gint> distances_;
  std::complex<gint> pos_{ 0, 0 };
  std::array<std::complex<gint>, 4> direction_{ std::complex<gint>{ 1, 0 },
    std::complex<gint>{ 0, -1 },
    std::complex<gint>{ -1, 0 },
    std::complex<gint>{ 0, 1 } };
  gint distance(Point interPoint) const noexcept
  {
    return std::abs(interPoint.real()) + std::abs(interPoint.imag());
  }
  Command com[256];
  int LenB_ = 0;

public:
  Car()
  {
    com['L'] = Command::Left;
    com['R'] = Command::Right;
    com['U'] = Command::Up;
    com['D'] = Command::Down;
  }
  auto min_distance() const noexcept
  {
    return *ranges::min_element(distances_);
  }
  void inter(std::pair<Point, Point> l, std::pair<Point, Point> r, int LenA)
  {
    auto len = LenA + LenB_;

    auto linestart = l.first;
    auto rstart = r.first;
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
      auto interPoint = Point(r.first.real(), l.first.imag());
      if (interPoint != linestart) {
        len += distance(interPoint - linestart) + distance(interPoint - rstart);

        distances_.push_back(len);
      }
    } else {
      swap(l, r);
      if (l.first.imag() == l.second.imag() && r.first.real() == r.second.real() && between(l.first.real(), l.second.real(), r.first.real()) && between(r.first.imag(), r.second.imag(), l.first.imag())) {
        auto interPoint = Point(r.first.real(), l.first.imag());
        if (interPoint != linestart) {
          len += distance(interPoint - linestart) + distance(interPoint - rstart);
          distances_.push_back(len);
          swap(l, r);
        }
      }
    }
  }
  void findinter(std::pair<Point, Point> l)
  {
    for (int i = 0; i < v_.size(); ++i) {
      inter(l, v_[i], fromOrigins_[i]);
    }
  }

  void processA(char c, gint value) noexcept
  {
    roads_.push_back(value);
    auto newpos = pos_ + direction_[com[c]] * value;
    auto road = std::make_pair(pos_, newpos);
    v_.push_back(road);
    pos_ = newpos;
  }
  void resetPos() noexcept
  {
    pos_ = Point{ 0, 0 };
    fromOrigins_.resize(roads_.size());
    std::exclusive_scan(roads_.begin(), roads_.end(), fromOrigins_.begin(), 0);
  }
  void processB(char c, gint value) noexcept
  {
    auto newpos = pos_ + direction_[com[c]] * value;
    auto road = std::make_pair(pos_, newpos);
    findinter(road);
    LenB_ += value;
    pos_ = newpos;
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string sa, sb;
    std::getline(ifs, sa);
    std::getline(ifs, sb);
    std::istringstream isa(sa);
    std::istringstream isb(sb);
    char c;
    int forward;
    Car car;
    while (isa >> c >> forward) {
      car.processA(c, forward);
    }
    car.resetPos();
    while (isb >> c >> forward) {
      car.processB(c, forward);
    }
    std::cout << car.min_distance() << std::endl;
  }
}