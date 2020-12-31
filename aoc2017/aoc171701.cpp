#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <fmt/format.h>
#include <numeric>
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <iomanip>
#include <iterator>
#include <utility>
#include <range/v3/all.hpp>
namespace views = ranges::views;

struct Joseph
{
  friend std::ostream &operator<<(std::ostream &os, Joseph const &joseph)
  {
    std::ostream_iterator<int> oit(os, ",");
    ranges::copy(joseph.l_, oit);
    return os;
  }
  std::list<int> l_;
  int i_ = 1;
  std::list<int>::iterator curr_;
  Joseph() : l_{ 0 }
  {
    curr_ = l_.begin();
  }

  void next()
  {
    ++curr_;
    if (curr_ == l_.end()) {
      curr_ = l_.begin();
    }
  }
  void next(int n)
  {
    for (; n; --n) {
      next();
    }
  }
  int valueafter2017()
  {
    auto p = std::next(curr_);
    if (p == l_.end()) {
      p = l_.begin();
    }
    return *p;
  }
  void insert()
  {
    next(386);
    auto p = std::next(curr_);
    l_.insert(p, i_);
    ++i_;
    next();
  }
};
int main()
{
  Joseph joseph;
  auto v = views::ints(0) | views::take(50000000) | views::common;
  for (auto i : v) {
    joseph.insert();
  }
  std::cout << joseph.valueafter2017() << std::endl;
}
