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
#include <utility>
#include <range/v3/all.hpp>
namespace views = ranges::views;

struct Joseph
{
  std::list<int> l_;
  std::list<int>::iterator curr_;
  Joseph(std::list<int> l) : l_(std::move(l))
  {
    curr_ = l_.begin();
  }
  auto last() const
  {
    return l_.front();
  }
  auto getnext()
  {
    auto next = std::next(curr_);
    if (next == l_.end()) {
      next = l_.begin();
    }
    return next;
  }
  bool erase()
  {
    if (l_.size() == 1) {
      return false;
    } else {
      auto next = getnext();
      l_.erase(next);
      curr_ = getnext();
      return true;
    }
  }
};
int main()
{
  auto v = views::ints(1) | views::take(3012210) | views::common;
  std::list<int> a(v.begin(), v.end());
  Joseph joseph(std::move(a));
  while (joseph.erase()) {
  }

  std::cout << joseph.last() << std::endl;
}
