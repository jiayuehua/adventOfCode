#include <complex>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/circular_buffer.hpp>
#include <range/v3/all.hpp>
#include <cstdint>
#include <initializer_list>
#include <iterator>
namespace views = ranges::views;
using Buffer = boost::circular_buffer<int>;
class Knothash
{
  Buffer ring_;
  std::vector<int> sequencelen_;
  int skiplen_ = 0;
  int curpos_ = 0;
  void reverse(int start, int len)
  {
    for (auto i = 0; i < len / 2; ++i) {
      int b = (start + i) % ring_.size();
      int r = (start + len - 1 - i) % ring_.size();
      std::swap(ring_[b], ring_[r]);
    }
  }

public:
  Knothash(int n, std::initializer_list<int> l) : ring_(n), sequencelen_(l)
  {
    for (int i = 0; i < n; ++i) {
      ring_.push_back(i);
    }
  }
  void hash()
  {
    for (auto l : sequencelen_) {
      reverse(curpos_, l);
      curpos_ += l + skiplen_;
      ++skiplen_;
    }
  }
  int final() const
  {
    return ring_[0] * ring_[1];
  }
};
int main()
{
  //Knothash h(5, { 3, 4, 1, 5 });
  Knothash h(256, { 187, 254, 0, 81, 169, 219, 1, 190, 19, 102, 255, 56, 46, 32, 2, 216 });
  h.hash();
  int n = h.final();
  std::cout << n << std::endl;
}
