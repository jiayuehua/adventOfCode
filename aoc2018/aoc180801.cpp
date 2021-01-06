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
struct Tree
{
  int meta_;
  auto call(Iter b)
  {
    int childnum = *b;
    int metanum = *(b + 1);
    if (!childnum) {
      for (int i = 0; i < metanum; ++i) {
        meta_ += *(b + 2 + i);
      }
      return b + 2 + metanum;
    } else {
      b = b + 2;
      for (int i = 0; i < childnum; ++i) {
        b = call(b);
      }
      for (auto e = b + metanum; b != e; ++b) {
        meta_ += *b;
      }
    }
    return b;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::istream_iterator<int> b(ifs);
    std::istream_iterator<int> e;
    std::vector<int> v(b, e);
    Tree t;
    t.call(v.begin());
    std::cout << t.meta_ << std::endl;
  }
}
