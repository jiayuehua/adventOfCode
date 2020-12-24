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

struct Mypair
{
  int x = 0;
  int y = 0;
  constexpr Mypair(int tx, int ty) : x(tx), y(ty) {}
  constexpr Mypair() {}
  auto operator<=>(const Mypair &) const = default;

  constexpr Mypair operator+=(Mypair r) noexcept
  {
    *this = (*this) + r;
    return *this;
  }
  friend constexpr Mypair operator+(Mypair l, Mypair r) noexcept
  {
    Mypair t(l);
    t.x += r.x;
    t.y += r.y;
    return t;
  }
};

class Lobby
{
  std::set<Mypair> blackbricks_;
  std::map<std::string_view, Mypair> directions_;
  std::string_view vs_[6] = { "e"sv, "se"sv, "sw"sv, "w"sv, "nw"sv, "ne"sv };

  void insertpair(Mypair l)
  {
    if (auto i = blackbricks_.find(l); i != blackbricks_.end()) {
      blackbricks_.erase(i);
    } else {
      blackbricks_.insert(l);
    }
  }
  bool isblack(Mypair l) const
  {
    return blackbricks_.contains(l);
  }

  std::set<Mypair> getaroundjwhitegrids() const
  {
    auto sixdirects = directions_ | views::values;
    std::set<Mypair> v;
    for (auto p : blackbricks_) {

      for (auto dir : sixdirects) {
        if (!isblack(p + dir)) {
          v.insert(p + dir);
        }
      }
    }
    return v;
  }


public:
  int blackbrickssize() const
  {
    return blackbricks_.size();
  }
  Lobby()
  {
    directions_["e"] = Mypair(2, 0);
    directions_["se"] = Mypair(1, 1);
    directions_["sw"] = Mypair(-1, 1);
    directions_["w"] = Mypair(-2, 0);
    directions_["ne"] = Mypair(1, -1);
    directions_["nw"] = Mypair(-1, -1);
  }
  void processoneline(std::string_view s)
  {
    Mypair startpoint{ 0, 0 };
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
  int aroundblacks(Mypair p) const
  {
    auto sixdirects = directions_ | views::values;
    int n = 0;
    for (auto dir : sixdirects) {
      n += (isblack(p + dir));
    }
    return n;
  }
  bool canturnblack(Mypair p) const
  {
    return aroundblacks(p) == 2;
  }
  bool canturnwhite(Mypair p) const
  {
    int n = aroundblacks(p);
    return (n == 0) || (n > 2);
  }
  void daywork()
  {
    auto oldwhitegrids = getaroundjwhitegrids();

    std::set<Mypair> newblacks;
    for (auto white : oldwhitegrids) {
      if (canturnblack(white)) {
        newblacks.insert(white);
      }
    }
    for (auto black : blackbricks_) {
      if (!canturnwhite(black)) {
        newblacks.insert(black);
      }
    }
    blackbricks_ = newblacks;
  }
  int nthdaywork(int n)
  {
    for (int i : views::ints | views::take(n)) {
      daywork();
    }
    return blackbricks_.size();
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
    fmt::print("nthdayblackgrids:{}\n", l.nthdaywork(100));
  }
}