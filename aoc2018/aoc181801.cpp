#include <complex>
#include <exception>
#include <fstream>
#include <set>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <list>
#include <array>
#include <cstdint>
#include "../aoc2020/matrix.h"
namespace views = ranges::views;
template<int N>
class LumerArea
{
  FixedMatrix<char, N + 2> acresA_;
  FixedMatrix<char, N + 2> acresB_;
  FixedMatrix<char, N + 2> acresZero_;

public:
  int totalResource()
  {
    for (int i = 0; i < 9999; ++i) {
      transform();
      //std::cout << j << ":" << ranges::count(acresA_.array(), '|') * ranges::count(acresA_.array(), '#') << std::endl;
    }
    for (int j = 0; j < 101; ++j) {

      transform();
      std::cout << j << ":" << ranges::count(acresA_.array(), '|') * ranges::count(acresA_.array(), '#') << std::endl;
    }


    return ranges::count(acresA_.array(), '|') * ranges::count(acresA_.array(), '#');
  }
  friend std::ostream &operator<<(std::ostream &os, const LumerArea &la)
  {
    for (int i = 1; i < N + 1; ++i) {
      for (int j = 1; j < N + 1; ++j) {
        os << la.acresA_(i, j);
      }
      os << std::endl;
    }
    return os;
  }
  friend std::istream &operator>>(std::istream &is, LumerArea &la)
  {
    std::string s;
    for (int i = 0; is >> s; ++i) {
      ranges::copy(s, la.acresA_.row(i + 1).begin() + 1);
    }
    return is;
  }
  std::tuple<int, int, int> aroundAcreCount(int m, int n) const
  {
    std::tuple<int, int, int> acreCount;
    for (int i = -1; i < 2; ++i) {
      for (int j = -1; j < 2; ++j) {
        if (acresA_(m + i, n + j) == '.') {
          ++std::get<0>(acreCount);
        } else if (acresA_(m + i, n + j) == '|') {
          ++std::get<1>(acreCount);
        } else if (acresA_(m + i, n + j) == '#') {
          ++std::get<2>(acreCount);
        }
      }
    }
    std::get<0>(acreCount) -= (acresA_(m, n) == '.');
    std::get<1>(acreCount) -= (acresA_(m, n) == '|');
    std::get<2>(acreCount) -= (acresA_(m, n) == '#');

    return acreCount;
  }
  char convert(int i, int j) const noexcept
  {
    auto [open, tree, lumer] = aroundAcreCount(i, j);
    if (acresA_(i, j) == '.' && tree >= 3) {
      return '|';
    } else if (acresA_(i, j) == '|' && lumer >= 3) {
      return '#';
    } else if (acresA_(i, j) == '#') {
      if (!(lumer && tree)) {
        return '.';
      }
    }
    return acresA_(i, j);
  }
  void transform()
  {
    for (int i = 1; i < N + 1; ++i) {
      for (int j = 1; j < N + 1; ++j) {
        acresB_(i, j) = convert(i, j);
      }
    }
    acresA_ = std::exchange(acresB_, acresZero_);
  }
};

int main(int argc, char **argv)
{
  LumerArea<50> l;
  std::ifstream ifs(argv[1]);
  ifs >> l;
  std::cout << l.totalResource() << std::endl;
  ;
  //for (int i = 0; i < 5; ++i) {
  //  l.transform();
  //  std::cout << "=====" << (i + 1) << "=======\n";
  //  std::cout << l << std::endl;
  //}
}
