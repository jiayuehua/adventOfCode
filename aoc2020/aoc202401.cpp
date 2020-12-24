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
  std::set<std::pair<int, int>> blackbricks_;
  std::map<std::string_view, std::complex<int>> directions_;
  std::string_view vs_[6] = { "e"sv, "se"sv, "sw"sv, "w"sv, "nw"sv, "ne"sv };

  void insertpair(std::complex<int> l)
  {
    std::pair pl(l.imag(), l.real());
    if (auto i = blackbricks_.find(pl); i != blackbricks_.end()) {
      blackbricks_.erase(i);
    } else {
      blackbricks_.insert(pl);
    }
  }


public:
  int blackbrickssize() const
  {
    return blackbricks_.size();
  }
  Lobby()
  {
    directions_["e"] = std::complex<int>(2, 0);
    directions_["se"] = std::complex<int>(1, 1);
    directions_["sw"] = std::complex<int>(-1, 1);
    directions_["w"] = std::complex<int>(-2, 0);
    directions_["ne"] = std::complex<int>(1, -1);
    directions_["nw"] = std::complex<int>(-1, -1);
  }
  void processoneline(std::string_view s)
  {
    std::complex<int> startpoint{ 0, 0 };
    while (s.size()) {
      for (auto sb : vs_) {
        if (s.starts_with(sb)) {
          startpoint += directions_[sb];
          s.remove_prefix(sb.size());
          break;
        }
      }
    }
    insertpair(startpoint);
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    Lobby l;
    std::ifstream ifs(argv[1]);
    std::string line;
    while (std::getline(ifs, line)) {
      l.processoneline(line);
    }
    fmt::print("{}\n", l.blackbrickssize());
  }
}