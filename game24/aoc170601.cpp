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
  std::set<boost::circular_buffer<int>> set_;
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
    m.set_.insert(m.cb_);
    return is;
  }
  bool run()
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
    auto [ti, b] = set_.insert(cb_);
    return b;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Memory m(16);
    ifs >> m;
    int n = 0;
    for (; m.run(); ++n) {
    }
    std::cout << (n + 1) << std::endl;
  }
}