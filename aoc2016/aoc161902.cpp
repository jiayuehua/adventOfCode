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
#include <set>
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
  auto getnext(std::list<int>::iterator it, int n = 1)
  {
    auto next = it;

    for (; n; --n) {
      next = std::next(it);
      if (next == l_.end()) {
        next = l_.begin();
      }
      it = next;
    }
    return next;
  }
  int getleft()
  {
    while (l_.size() > 3) {
      erasebig();
    }
    while (erasesmall()) {
    }
    return last();
  }

private:
  bool erasesmall()
  {
    if (l_.size() == 1) {
      return false;
    } else {
      auto next = getnext();
      std::cout << *next << std::endl;
      l_.erase(next);
      curr_ = getnext();
      return true;
      ;
    }
  }
  void erasebig()
  {
    auto next = getnext(curr_, 2);
    //std::cout << *next << std::endl;
    l_.erase(next);
    curr_ = getnext();
  }
};
int test()
{
  auto v = views::ints(1) | views::take(3012210) | views::common;
  //auto v = views::ints(1) | views::take(7) | views::common;
  std::list<int> a(v.begin(), v.end());
  Joseph joseph(std::move(a));
  //while (joseph.erase()) {
  //}

  std::cout << joseph.getleft() << std::endl;
  return 0;
}
struct Node
{
  int value;
  std::vector<Node> child;
};
int main()
{
  std::int64_t n = 1;
  //12578151;
  for (int i = 0; i < 10000000; ++i) {
    n = n * 7;
    n = n % 20201227;
    if (n == 12578151) {
      fmt::print("B{},{}\n", i, n);
      break;
    }
  }
  n = 1;
  for (int i = 0; i < 10000000; ++i) {
    n = n * 7;
    n = n % 20201227;
    if (n == 5051300) {
      fmt::print("B{},{}\n", i, n);
      break;
    }
  }
  std::int64_t k = 1;
  for (int i = 0; i < 5497777; ++i) {
    k = k * 12578151;

    k = k % 20201227;
  }
  fmt::print("{}\n", k);
  k = 1;
  for (int i = 0; i < 538014; ++i) {
    k = k * 5051300;
    k = k % 20201227;
  }
  fmt::print("{}\n", k);
}
