#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <optional>
#include <complex>
#include <bitset>
#include <set>
#include "matrix.h"
constexpr bool road(int x, int y)
{
  constexpr int i = 1352;
  std::bitset<128> b = y * y + 3 * y + 2 * y * x + x + x * x + i;
  return b.count() % 2 == 0;
}
struct Game
{
private:
  static inline constexpr int NX = 100 + 2;
  static inline constexpr int NY = 100 + 2;
  FixedMatrix<int, NX, NY> networks_;
  std::set<std::pair<int, int>> locations_;
  std::array<std::complex<int>, 4> step_ = {
    std::complex{ 0, -1 },
    std::complex{ 0, 1 },
    std::complex{ -1, 0 },
    std::complex{ 1, 0 }
  };

public:
  auto size() const
  {
    return locations_.size();
  }
  Game()
  {
    for (auto i = 0; i < NX - 2; ++i) {
      for (auto j = 0; j < NY - 2; ++j) {
        networks_(i + 1, j + 1) = road(i, j);
      }
    }
  }
  bool isroad(std::complex<int> pos) const
  {
    return networks_(pos.imag(), pos.real());
  }
  struct PaintColor
  {
    FixedMatrix<int, NX, NY> *networks_;
    std::complex<int> pos_;
    PaintColor(FixedMatrix<int, NX, NY> *p, std::complex<int> pos) : networks_(p), pos_(pos)
    {
      (*networks_)(pos.imag(), pos.real()) = 0;
    }
    ~PaintColor()
    {
      (*networks_)(pos_.imag(), pos_.real()) = 1;
    }
  };

  std::optional<std::string> shortestpath(const std::string &path, std::complex<int> pos)
  {
    if (path.size() > 50) {
      return std::string{};
    } else {
      locations_.insert(std::make_pair(pos.imag(), pos.real()));
      PaintColor pc(&networks_, pos);
      std::optional<std::string> result;

      std::string s("UDLR");
      for (int i = 0; i < 4; ++i) {
        if (isroad(pos + step_[i])) {
          auto nextshort = shortestpath(path + s[i], pos + step_[i]);
          if (nextshort) {
            if (result) {
              if ((*nextshort).size() + 1 < (*result).size()) {
                result = s[i] + *nextshort;
              }
            } else {
              result = s[i] + *nextshort;
            }
          }
        }
      }
      return result;
    }
  }
};
int main()
{
  Game g;
  std::complex a{ 2, 2 };
  g.shortestpath("", a);
  std::cout << g.size() << std::endl;
}