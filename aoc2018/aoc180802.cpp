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
namespace views = ranges::views;

using Iter = std::vector<int>::iterator;
std::pair<Iter, int> call(Iter b)
{
  int childnum = *b;
  int metanum = *(b + 1);
  if (!childnum) {
    int meta_ = 0;
    for (int i = 0; i < metanum; ++i) {
      meta_ += *(b + 2 + i);
    }
    return { b + 2 + metanum, meta_ };
  } else {
    b = b + 2;
    std::vector<int> metas(childnum);
    for (int i = 0; i < childnum; ++i) {
      auto [k, v] = call(b);
      b = k;
      metas[i] = v;
    }
    int meta = 0;
    for (auto e = b + metanum; b != e; ++b) {
      if (*b < metas.size() + 1 && (*b >= 1)) {
        meta += metas[*b - 1];
      }
    }
    return { b, meta };
  }
}

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::istream_iterator<int> b(ifs);
    std::istream_iterator<int> e;
    std::vector<int> v(b, e);
    auto [k, value] = call(v.begin());
    std::cout << value << std::endl;
  }
}
