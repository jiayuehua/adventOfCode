#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <boost/circular_buffer.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
namespace views = ranges::views;
struct Memory
{
  boost::circular_buffer<int> cb_;
  std::map<boost::circular_buffer<int>, int> set_;
  int first_ = 0;
  Memory(int n) : cb_(n)
  {
    for (int i = 0; i < n; ++i) {
      cb_.push_back(0);
    }
  }
  friend std::istream &operator>>(std::istream &is, Memory &m)
  {
    std::istream_iterator<int> ib(is), ie;
    std::vector<int> v;
    std::copy(ib, ie, std::back_inserter(v));
    std::copy(v.begin(), v.end(), m.cb_.begin());
    m.set_.insert(std::make_pair(m.cb_, 0));
    return is;
  }
  auto run()
  {
    auto i = ranges::max_element(cb_);
    int origin = *i;
    int t = (*i) / cb_.size();
    int r = (*i) % cb_.size();
    ranges::for_each(cb_, [t](auto &a) { a += t; });

    int n = (i - cb_.begin());
    for (int j = 0; j < r; ++j) {
      cb_[n + j + 1] += 1;
    }
    *i -= origin;
    ++first_;
    auto [ti, b] = set_.insert(std::make_pair(cb_, first_));
    return std::make_pair(b, first_ - ti->second);
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Memory m(16);
    ifs >> m;
    int n = 0;
    for (;;) {
      if (auto [k, v] = m.run(); !k) {
        n = v;
        break;
      }
    }
    std::cout << (n) << std::endl;
  }
}