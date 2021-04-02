#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <string_view>
namespace views = ranges::views;
class Pots
{
  std::map<std::string, char> m;
  std::string origin;
  std::string sa;
  std::string sb;
  std::string sc;
  void foo()
  {
    auto v = sa | views::sliding(5) | views::transform([this](auto v) {
      std::string s(v.begin(), v.end());
      if (m.find(s) == m.end()) {
        return '.';
      } else {
        return m[s];
      }
    }) | views::common;
    ranges::copy(v, sb.begin() + 2);
    sa = std::exchange(sb, sc);
  }
  static inline constexpr int N = 2000;

public:
  int Round(int n)
  {
    for (int i = 0; i < n; ++i) {
      foo();
    }
    auto v = sa | views::enumerate | views::filter([](auto pair) {
      return std::get<1>(pair) == '#';
    }) | views::transform([](auto pair) { return std::get<0>(pair) - N; });
    return ranges::accumulate(v, 0);
  }
  Pots(std::string_view s = "") : sa(N * 2 + 100, '.'), sb(sa), sc(sa)
  {
    ranges::copy(s, sa.begin() + N);
  }
  friend std::istream &operator>>(std::istream &is, Pots &p)
  {
    is >> p.origin;
    ranges::copy(p.origin, p.sa.begin() + p.N);
    std::string key;
    char v;
    std::cout << p.origin << std::endl;

    while (is >> key >> v) {
      p.m[key] = v;
      std::cout << key << v << std::endl;
    }
    return is;
  }
};

int main(int argc, char **argv)
{
  Pots p;
  std::ifstream ifs(argv[1]);
  ifs >> p;
  for (int i = 0; i < 200; ++i) {
    std::cout << p.Round(1) << std::endl;
  }
}
