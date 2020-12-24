#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <string>
#include <array>
#include <range/v3/all.hpp>
#include <cstdint>
#include <boost/intrusive/slist.hpp>
#include <boost/intrusive/list.hpp>
#include <initializer_list>
using gint = std::int64_t;
namespace intrusive = boost::intrusive;
namespace views = ranges::views;
template<class Rng>
int finddst(Rng rng, int n, int N)
{
  auto b = rng.begin();
  for (int i = 0;; ++i) {
    int next = (n - i - 1) + (n - i - 1 < 1) * N;
    if (ranges::find_if(rng, [next](const auto &mc) { return mc.int_ == next; }) == rng.end()) {
      return next;
    }
  }
  return N;
}
class MyClass : public boost::intrusive::list_base_hook<>
{
public:
  int int_;
  friend std::ostream &operator<<(std::ostream &os, const MyClass &mc)
  {
    os << mc.int_;
    return os;
  }
  auto operator<=>(int r) const
  {
    return int_ <=> r;
  }

  auto operator<=>(MyClass r) const
  {
    return int_ <=> r.int_;
  }
  MyClass(int i) : int_(i) {}
  MyClass() {}
};
struct CrabCup
{
public:
  typedef intrusive::list<MyClass> BaseList;

private:
  std::vector<MyClass> values;
  BaseList baselist;

public:
  CrabCup(std::initializer_list<int> l, int n) : values(n)
  {
    auto idsbegin = views::ints | views::drop(1) | views::take(l.size()) | views::common;

    int i = 0;
    for (auto t : idsbegin) {
      values[i].int_ = t;
      ++i;
    }
    for (auto t : l) {
      baselist.push_back(values[t - 1]);
    }

    auto indexs = views::ints | views::drop(l.size() + 1) | views::take(values.size() - l.size()) | views::common;
    for (auto t : indexs) {
      values[i].int_ = t;
      baselist.push_back(values[i]);
      ++i;
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const CrabCup &crabcup)
  {
    std::ostream_iterator<int> oit(std::cout, ",");
    ranges::transform(crabcup.baselist, oit, [](auto const &mc) { return mc.int_; });
    return os;
  }
  void round()
  {
    auto &n = baselist.front();
    auto rng = baselist | views::drop(1) | views::take(3);
    auto id = finddst(rng, n.int_, values.size());
    auto iter = baselist.iterator_to(values[id - 1]);
    ++iter;
    auto b = std::next(baselist.begin(), 1);
    auto e = std::next(b, 3);
    baselist.splice(iter, baselist, b, e);
    baselist.pop_front();
    baselist.push_back(n);
  }
  gint findone()
  {
    auto iter = baselist.iterator_to(values[1 - 1]);
    auto n1i = ++iter;
    auto n2i = ++iter;
    return gint(n1i->int_) * (n2i->int_);
  }
};


int main()
{
  CrabCup c({ 4, 6, 7, 5, 2, 8, 1, 9, 3 }, 1000000);
  for (auto i : views::ints | views::take(10000000) | views::common) {
    c.round();
  }
  std::cout << c.findone() << std::endl;
  return 0;
}
