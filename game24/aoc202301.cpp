#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <string>
#include <range/v3/all.hpp>
#include <cstdint>
#include <boost/circular_buffer.hpp>
#include <initializer_list>
using Ring = boost::circular_buffer<int>;
namespace views = ranges::views;
struct CrabCup
{
private:
  Ring ring_;

public:
  CrabCup(std::initializer_list<int> l, int n) : ring_(n)
  {
    ranges::copy(l, std::back_inserter(ring_));

    auto indexs = views::ints | views::drop(l.size() + 1) | views::take(n - l.size()) | views::common;
    ranges::copy(indexs, std::back_inserter(ring_));
  }
  CrabCup(std::initializer_list<int> l) : ring_(l.begin(), l.end())
  {
  }

  friend std::ostream &operator<<(std::ostream &os, const CrabCup &crabcup)
  {
    std::ostream_iterator<int> oit(std::cout, "");
    ranges::copy(crabcup.ring_, oit);
    return os;
  }
  void round()
  {
    std::ostream_iterator<int> oit(std::cout, ",");
    auto n = ring_.front();
    std::vector<int> v(ring_.begin() + 4, ring_.end());
    auto indexs = views::ints | views::take(ring_.size()) | views::drop(4) | views::common;
    std::vector<int> vi(indexs.begin(), indexs.end());
    ranges::zip_view flatmap(v, vi);
    ranges::sort(flatmap);
    auto dstpos = ranges::lower_bound(v, n);
    if (dstpos == v.begin()) {
      dstpos = v.end();
    }
    --dstpos;
    int len = dstpos - v.begin();
    auto id = vi[len];
    std::rotate(ring_.begin() + 1, ring_.begin() + 4, ring_.begin() + id + 1);

    ring_.push_back(n);
  }
  void findone()
  {
    while (ring_.front() != 1) {
      ring_.push_back(ring_.front());
    }
    ring_.pop_front();
  }
};


int main()
{
  CrabCup c({ 4, 6, 7, 5, 2, 8, 1, 9, 3 }, 20);
  for (auto i : views::ints | views::take(30) | views::common) {
    c.round();
  }
  c.findone();
  std::cout << c << std::endl;
  return 0;
}
