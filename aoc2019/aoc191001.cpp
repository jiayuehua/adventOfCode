#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <set>
#include <fmt/format.h>
#include <numeric>
#include "../aoc2020/matrix.h"
namespace views = ranges::views;
template<int RowNum, int ColNum>
class Station
{
  FixedMatrix<bool, RowNum, ColNum> m_;

public:
  friend std::istream &operator>>(std::istream &is, Station &s)
  {
    ranges::getlines_view iv(is);
    int i = 0;
    ranges::for_each(iv, [&s, &i](std::string_view sv) {
      ranges::transform(sv, s.m_.row(i).begin(), [](char c) { return c == '#'; });
      ++i;
    });
    //std::cout << s.m_ << std::endl;
    std::set<std::pair<int, int>> gcds_;
    gcds_.insert(std::pair{ 0, 1 });
    gcds_.insert(std::pair{ 0, -1 });
    gcds_.insert(std::pair{ 1, 0 });
    gcds_.insert(std::pair{ -1, 0 });
    for (int i = 1; i < RowNum; ++i) {
      for (int j = i; j < ColNum; ++j) {
        auto gcd = std::gcd(i, j);
        auto ia = i / gcd;
        auto ja = j / gcd;

        gcds_.insert(std::pair{ ia, ja });
        gcds_.insert(std::pair{ -ia, ja });
        gcds_.insert(std::pair{ ia, -ja });
        gcds_.insert(std::pair{ -ia, -ja });
        gcds_.insert(std::pair{ ja, ia });
        gcds_.insert(std::pair{ -ja, ia });
        gcds_.insert(std::pair{ ja, -ia });
        gcds_.insert(std::pair{ -ja, -ia });
      }
    }
    int maxcnt = 0;
    auto between = [](auto f, auto l, auto m) {
      return (f <= m) && (m < l);
    };
    for (int i = 0; i < RowNum; ++i) {
      for (int j = 0; j < ColNum; ++j) {
        if (s.m_(i, j)) {
          int cnt = 0;
          for (auto pair : gcds_) {
            //fmt::print("pair:{},{}:", pair.first, pair.second);

            auto ni = i + pair.first;
            auto nj = j + pair.second;
            //bool found=false;
            for (int k = 1; k < std::max(RowNum, ColNum) && between(0, RowNum, ni) && between(0, ColNum, nj); ++k, ni += pair.first, nj += pair.second) {
              if (s.m_(ni, nj)) {
                cnt += 1;
                break;
              }
              //cnt += s.m_(ni, nj);
            }
          }
          //fmt::print("cnt:{}\n", cnt);
          if (cnt > maxcnt) {
            fmt::print("i:{},j:{}:", i, j);
            fmt::print("cnt:{}\n", cnt);
            maxcnt = cnt;
          }
        }
      }
    }
    fmt::print("max:{}\n", maxcnt);
    return is;
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    Station<25, 25> s;
    std::ifstream ifs(argv[1]);
    ifs >> s;
  }
}
