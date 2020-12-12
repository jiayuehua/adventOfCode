#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <numeric>
#include <iomanip>
#include <cstdint>
#include <utility>
#include <iterator>

#include <range/v3/all.hpp>
using std::int64_t;
struct Fibonacci
{
  std::vector<int> vd_;

  int64_t get() noexcept
  {
    std::vector<int64_t> vr_(vd_.size());
    vr_[0] = 1;
    vr_[1] = 1 + ((vd_[0] + vd_[1]) <= 3);
    vr_[2] = vr_[1] + ((vd_[0] + vd_[1] + vd_[2]) <= 3) + ((vd_[1] + vd_[2]) <= 3) * vr_[0];
    for (int i = 3; i < vd_.size(); ++i) {
      vr_[i] = vr_[i - 1] + ((vd_[i - 1] + vd_[i]) <= 3) * vr_[i - 2] + ((vd_[i] + vd_[i - 2] + vd_[i - 1]) <= 3) * vr_[i - 3];
    }
    return vr_.back();
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    int i;
    std::vector<int> v;
    v.reserve(500);
    while (ifs >> i) {
      v.push_back(i);
    }
    std::vector<int> vd(v);
    ranges::sort(v);
    ranges::adjacent_difference(v, vd.begin());
    std::ostream_iterator<int> ost(std::cout, ",");
    vd.push_back(3);
    ranges::copy(vd, ost);
    fmt::print(" \n");
    Fibonacci f;
    f.vd_ = std::move(vd);
    fmt::print("{}\n", f.get());
  }
}