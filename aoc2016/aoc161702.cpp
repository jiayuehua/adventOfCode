#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <range/v3/all.hpp>
#include <optional>
#include <complex>
#include <cx_md5.h>
#include "matrix.h"
namespace views = ranges::views;
auto md5 = [init = std::string("pslxynzg")](const std::string &s) {
  auto sum = cx::md5_new((init + s).c_str());
  const uint8_t *m = reinterpret_cast<const uint8_t *>(sum.h);
  std::string sumstr;
  std::ostringstream ost(sumstr);
  ost << std::hex << std::setfill('0');
  for (size_t i = 0; i < sizeof(sum.h); ++i) {
    ost << std::setw(2) << +m[i];
  }
  return ost.str();
};
struct Game
{
  FixedMatrix<int, 4, 4> networks_;
  std::array<std::complex<int>, 4> step_ = {
    std::complex{ 0, -1 },
    std::complex{ 0, 1 },
    std::complex{ -1, 0 },
    std::complex{ 1, 0 }
  };
  Game()
  {
    //step_[0]=
  }
  std::optional<std::string> shortestpath(const std::string &path, std::complex<int> pos)
  {
    if (pos.real() < 0 || pos.real() >= 4 || pos.imag() < 0 || pos.imag() >= 4) {
      return std::nullopt;
    }
    if (pos == std::complex{ 3, 3 }) {
      return std::string{};
    } else {
      std::optional<std::string> result = std::nullopt;
      auto hashresult = md5(path);
      auto d = hashresult | views::take(4) | views::transform([](char c) {
        return ('b' <= c && c <= 'f');
      });

      std::string s("UDLR");
      for (int i = 0; i < 4; ++i) {
        if (d[i]) {
          auto nextshort = shortestpath(path + s[i], pos + step_[i]);
          if (nextshort) {
            if (result) {
              if ((*nextshort).size() + 1 > (*result).size()) {
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
  std::complex a{ 0, 0 };
  auto r = g.shortestpath("", a);
  if (r) {

    std::cout << (*r).length() << std::endl;
  }
}