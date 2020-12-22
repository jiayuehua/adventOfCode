#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <fmt/format.h>
#include <numeric>
#include <string>
#include <execution>
#include <cx_md5.h>
#include <vector>
#include <functional>
#include <iomanip>
#include <range/v3/all.hpp>

namespace views = ranges::views;

int main(int argc, char **argv)
{
  std::vector<int> v{
    0,
    0,
    1,
    1,
    1,
    0,
    1,
    0,
    1,
    1,
    1,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    0,
    1,
    1,
    1,
    1,
    0,
    1,
    1,
    1,
    1,
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    0,
    1,
    0,
    1,
    1,
    1,
    0,
    0,
    1,
    1,
    0,
    1,
    0,
    1,
    1,
    0,
    0,
    1,
    0,
    1,
    0,
    0,
    1,
    1,
    0,
    0,
    0,
    1,
    0,
    1,
    1,
    0,
    1,
    1,
    1,
    0,
    0,
    0,
    1,
    1,
    0,
    1,
    0,
    1,
    1,
    1,
    0,
    0,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    0
  };
  int n = ranges::count(v, 0) - 2;
  //std::ostream_iterator<int> ost(std::cout, ",");
  for (auto i = 0; i < 39; ++i) {
    std::vector<int> vb(v.size());
    auto slicetri = v | views::sliding(3) | views::transform([](auto tri) {
      return (tri[0] && tri[1] && !tri[2])
             || (!tri[0] && tri[1] && tri[2])
             || (!tri[0] && !tri[1] && tri[2])
             || (tri[0] && !tri[1] && !tri[2]);
    });
    n += ranges::count(slicetri, 0);
    ranges::copy(slicetri, vb.begin() + 1);
    //ranges::copy(vb, ost);
    v = (vb);
  }
  fmt::print("{}\n", n);
}