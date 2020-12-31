#include <complex>
#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <boost/icl/split_interval_set.hpp>
#include <boost/icl/interval_set.hpp>
#include <../aoc2020/matrix.h>
#include <../aoc2020/combinations_algo.h>
namespace icl = boost::icl;
typedef FixedMatrix<bool, 1000> Mat;
typedef icl::interval<int>::type Interval;
class Fab
{
  Mat m_;
  int value_;
  int id_;

public:
  int count() const
  {
    return value_;
  }
  int id() const
  {
    return id_;
  }
  friend std::istream &operator>>(std::istream &is, Fab &fab)
  {
    std::vector<std::tuple<int, Interval, Interval>> interval;
    int top, left, h, w;
    int i = 0;
    while (is >> top >> left >> h >> w) {
      icl::interval<int>::type p(top, top + h);
      icl::interval<int>::type pb(left, left + w);
      interval.emplace_back(i, p, pb);
      ++i;
    }
    std::vector<bool> ids(interval.size());
    for_each_combination(interval.begin(), interval.begin() + 2, interval.end(), [&fab, &ids](auto b, auto e) {
      auto [aid, afirst, asecond] = *b;
      auto [bid, bfirst, bsecond] = *(b + 1);

      auto atop = afirst.lower();
      auto abottem = afirst.upper();
      auto btop = bfirst.lower();
      auto bbottem = bfirst.upper();
      auto aleft = asecond.lower();
      auto aright = asecond.upper();
      auto bleft = bsecond.lower();
      auto bright = bsecond.upper();
      for (auto i = std::max(atop, btop); i < std::min(abottem, bbottem); ++i) {
        for (auto j = std::max(aleft, bleft); j < std::min(aright, bright); ++j) {
          fab.m_(i, j) = true;
          ids[aid] = true;
          ids[bid] = true;
        }
      }
      return false;
    });
    fab.value_ = ranges::count(fab.m_.array(), true);
    fab.id_ = ranges::find(ids, false) - ids.begin();
    return is;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Fab fab;
    ifs >> fab;
    std::cout << fab.count() << std::endl;
    std::cout << fab.id() + 1 << std::endl;
    return 0;
  }
}
