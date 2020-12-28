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
#include <functional>
namespace views = ranges::views;
using Buffer = boost::circular_buffer<unsigned char>;
class Knothash
{
  static inline constexpr int N = 256;
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
  Knothash(std::string_view input) : ring_(N)
  {
    ranges::copy(views::ints | views::take(N), std::back_inserter(ring_));
    auto v = input | views::transform([](char c) { return static_cast<int>(c); });
    int suffix[] = { 17, 31, 73, 47, 23 };
    auto origin = views::concat(v, suffix);
    ranges::copy(origin, std::back_inserter(sequencelen_));
  }
  void hash()
  {
    for (auto i = 0; i < 64; ++i) {
      for (auto l : sequencelen_) {
        reverse(curpos_, l);
        curpos_ += l + skiplen_;
        ++skiplen_;
      }
    }
  }
  std::string final() const
  {
    auto
      hexstring = ring_ | views::chunk(16) | views::transform([](auto range) {
        std::string result;
        char hex[] = "0123456789abcdef";
        auto r = ranges::accumulate(
          range, 0, std::bit_xor{});
        result += hex[(r / 16)];
        result += hex[(r % 16)];
        return result;
      });
    std::string s;
    return ranges::accumulate(hexstring, s);
  }
};
int main()
{
  Knothash h("187,254,0,81,169,219,1,190,19,102,255,56,46,32,2,216");
  h.hash();
  auto n = h.final();
  std::cout << n << std::endl;
}
