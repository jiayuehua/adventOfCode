#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <fmt/format.h>
namespace views = ranges::views;
class Image
{
  std::string s;
  int cnt_;

public:
  friend std::istream &operator>>(std::istream &is, Image &m)
  {
    is >> m.s;
    int n = m.s.size();
    int mincnt = 1000;
    for (int i = 0; i < n / 150; ++i) {
      auto l = m.s | views::slice(i * 150, i * 150 + 25 * 6);
      if (auto cnt = ranges::count(l, '0'); cnt < mincnt) {
        mincnt = cnt;
        m.cnt_ = ranges::count(l, '1') * ranges::count(l, '2');
      }
    }
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Image &m)
  {
    int n = m.s.size();
    std::string s(150, '#');
    for (int i = 0; i < 150; ++i) {
      auto l = m.s | views::drop(i) | views::stride(150);
      auto it = ranges::find_if(l, [](char c) { return c != '2'; });
      s[i] = *it;
    }
    auto cnk = s | views::transform([](char c) {
      char ch[] = { ' ', '#' };
      return ch[c - '0'];
    }) | views::chunk(25);
    ranges::for_each(cnk, [&os](auto t) {
      ranges::copy(t, std::ostream_iterator<char>(os, ""));
      os << "\n";
    });

    return os;
  }
  int Count() const
  {
    return cnt_;
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Image img;
    ifs >> img;
    std::cout << img << std::endl;
  }
}
