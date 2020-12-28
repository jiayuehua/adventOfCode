#include <fstream>
#include <sstream>
#include <iostream>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <deque>
#include <complex>
#include <algorithm>
#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <string_view>
#include <set>
namespace views = ranges::views;
using namespace std::literals::string_view_literals;

class Lobby
{
  std::complex<int> curr_;
  int maxdistance_ = 0;
  std::map<std::string_view, std::complex<int>> directions_;

public:
  int getmaxdistance() const
  {
    return maxdistance_;
  }
  std::complex<int> getcurr() const
  {
    return curr_;
  }
  friend std::istream &operator>>(std::istream &is, Lobby &l)
  {
    std::string line;
    while (is >> line) {
      l.curr_ += l.directions_[line];
      auto x = abs(l.curr_.real());
      auto y = abs(l.curr_.imag());
      int n = 0;
      if (y > 2 * x) {
        n = (y - x) / 2 + x;
      } else {
        n = x;
      }
      l.maxdistance_ = std::max(n, l.maxdistance_);
    }
    return is;
  }
  Lobby() : curr_(0, 0)
  {
    directions_["s"] = std::complex<int>(0, 2);
    directions_["n"] = std::complex<int>(0, -2);
    directions_["se"] = std::complex<int>(1, 1);
    directions_["sw"] = std::complex<int>(-1, 1);
    directions_["ne"] = std::complex<int>(1, -1);
    directions_["nw"] = std::complex<int>(-1, -1);
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    Lobby l;
    std::ifstream ifs(argv[1]);
    ifs >> l;
    auto d = l.getmaxdistance();
    fmt::print("{}\n", d);
  }
}