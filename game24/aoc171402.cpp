#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <optional>
#include <cctype>
#include <map>
#include <vector>
#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <boost/dynamic_bitset.hpp>
#include "knothash.h"
#include "../aoc2020/matrix.h"
#include "../aoc2020/mypair.h"
#include "../aoc2020/combinations_algo.h"
namespace views = ranges::views;
using mybitset = boost::dynamic_bitset<std::uint8_t>;
using uint8 = std::uint8_t;
std::string to_str(std::array<std::uint8_t, 16> &r)
{
  //auto r = (*this)(s);
  auto hexstring = r | views::transform([](auto t) {
    std::string result;
    char hex[] = "0123456789abcdef";
    result += hex[(t / 16)];
    result += hex[(t % 16)];
    return result;
  });
  std::string sres;
  return ranges::accumulate(hexstring, sres);
}
struct Game
{
  static inline constexpr int NX = 130;
  using Network = FixedMatrix<bool, NX, NX>;

private:
  Network networks_;

public:
  friend std::istream &operator>>(std::istream &is, Game &g)
  {
    std::string str;
    is >> str;

    Knothash hash_;
    auto range = views::ints | views::take(128) | views::transform([str, hash_](int i) {
      auto vec = hash_(str + std::string("-") + std::to_string(i));
      mybitset bitset(vec.begin(), vec.end());

      return bitset;
    }) | views::common;

    int i = 1;
    for (auto row : range) {
      for (int j = 1; j < NX - 1; ++j) {
        auto blocknum = (j - 1) / 8;
        auto inblockpos = (j - 1) % 8;
        auto index = blocknum * 8 + (8 - 1 - inblockpos);
        bool t = row[index];
        g.networks_(i, j) = t;
      }
      ++i;
    }
    return is;
  }
  std::array<Mypair, 4> step_ = {
    Mypair{ 0, -1 },
    Mypair{ 0, 1 },
    Mypair{ -1, 0 },
    Mypair{ 1, 0 }
  };
  void setbrick(Network &n, Mypair pos)
  {
    n(pos.x, pos.y) = 0;
  }
  bool isroad(Mypair p) const
  {
    return networks_(p.x, p.y);
  }
  bool isroad(int i, int j) const
  {
    return isroad(Mypair(i, j));
  }
  int CountGroup()
  {
    int n = 0;
    for (int i = 1; i < 129; ++i) {
      for (int j = 1; j < 129; ++j) {
        if (isroad(i, j)) {
          shortestpath(Mypair(i, j));
          ++n;
        }
      }
    }
    return n;
  }

  void shortestpath(Mypair pos)
  {
    std::vector<Mypair> curr;
    curr.push_back(pos);
    setbrick(networks_, pos);
    for (int j = 0;; ++j) {
      std::vector<Mypair> adjs;
      for (auto cur : curr) {
        for (int i = 0; i < 4; ++i) {
          if (isroad(cur + step_[i])) {
            setbrick(networks_, cur + step_[i]);
            adjs.push_back(cur + step_[i]);
          }
        }
      }
      curr = adjs;
      if (adjs.empty()) {
        break;
      }
    }
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    Game g;
    std::string s(argv[1]);
    std::istringstream iss(s);
    iss >> g;
    std::cout << g.CountGroup() << std::endl;
  }
}
