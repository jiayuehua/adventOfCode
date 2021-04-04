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
    std::cout << img.Count() << std::endl;
  }
}
