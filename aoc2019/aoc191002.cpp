#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <vector>
#include <fmt/format.h>
#include <numeric>
#include <tuple>
#include "../aoc2020/matrix.h"
namespace views = ranges::views;
template<int RowNum, int ColNum>
class Station
{
  FixedMatrix<bool, RowNum, ColNum> m_;
  static constexpr inline int srci = 19, srcj = 11;

public:
  friend std::istream& operator>>(std::istream& is, Station& s)
  {
    ranges::getlines_view iv(is);
    int i = 0;
    ranges::for_each(iv, [&s, &i](std::string_view sv) {
      ranges::transform(sv, s.m_.row(i).begin(), [](char c) { return c == '#'; });
      ++i;
      });
    std::vector<std::pair<int, int>> gcds_;
    gcds_.push_back(std::pair{ 0, 1 });
    gcds_.push_back(std::pair{ -1, 0 });
    for (int i = 1; i < RowNum; ++i) {
      for (int j = i; j < ColNum; ++j) {
        auto gcd = std::gcd(i, j);
        auto ia = i / gcd;
        auto ja = j / gcd;

        gcds_.push_back(std::pair{ ia, ja });
        gcds_.push_back(std::pair{ -ia, ja });
        gcds_.push_back(std::pair{ ja, ia });
        gcds_.push_back(std::pair{ -ja, ia });
      }
    }
    auto cmp = [](std::pair<int, int> l, std::pair<int, int> r) {
      auto la = l.first * r.second;
      auto ra = r.first * l.second;
      return la < ra;
    };

    ranges::sort(gcds_, cmp);
    gcds_.erase(ranges::unique(gcds_), std::end(gcds_));
    gcds_.resize(gcds_.size() * 2);
    ranges::transform(gcds_ | views::take(gcds_.size() / 2), gcds_.begin() + gcds_.size() / 2, [](std::pair<int, int> p) { return std::pair{ -p.first, -p.second }; });
    int maxcnt = 0;
    auto between = [](auto f, auto l, auto m) {
      return (f <= m) && (m < l);
    };
    auto dstx = 0, dsty = 0;

    for (int cnt = 0; cnt < 200;) {
      for (auto pair : gcds_) {
        auto ni = s.srci + pair.first;
        auto nj = s.srcj + pair.second;
        for (int k = 1; k < std::max(RowNum, ColNum) && between(0, RowNum, ni) && between(0, ColNum, nj); ++k, ni += pair.first, nj += pair.second) {
          if (s.m_(ni, nj)) {
            ++cnt;
            if (cnt == 200) {
              fmt::print("r:{}\n", nj * 100 + ni);
            }
            s.m_(ni, nj) = false;
            dstx = ni;
            dsty = nj;
            break;
          }
        }
      }
    }
    return is;
  }
};
int main(int argc, char** argv)
{
  if (argc > 1) {
    Station<25, 25> s;
    std::ifstream ifs(argv[1]);
    ifs >> s;
  }
}
