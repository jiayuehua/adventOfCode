#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/circular_buffer.hpp>
#include <range/v3/all.hpp>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <bit>
#include <functional>
#include <array>
namespace views = ranges::views;
using Buffer = boost::circular_buffer<std::uint8_t>;
class Knothash
{
  Buffer ring_;
  static inline constexpr int N = 256;
  void reverse(int start, int len)
  {
    for (auto i = 0; i < len / 2; ++i) {
      int b = (start + i) % ring_.size();
      int r = (start + len - 1 - i) % ring_.size();
      std::swap(ring_[b], ring_[r]);
    }
  }

public:
  Knothash() : ring_(N)
  {
  }
  std::array<std::uint8_t, 16> operator()(std::string_view input)
  {
    ranges::copy(views::ints | views::take(N), std::back_inserter(ring_));
    int skiplen_ = 0;
    int curpos_ = 0;
    auto v = input | views::transform([](char c) { return static_cast<int>(c); });
    int suffix[] = { 17, 31, 73, 47, 23 };
    auto sequencelen_ = views::concat(v, suffix);
    for (auto i = 0; i < 64; ++i) {
      for (auto l : sequencelen_) {
        reverse(curpos_, l);
        curpos_ += l + skiplen_;
        ++skiplen_;
      }
    }
    std::array<std::uint8_t, 16> result{};
    auto hexstring = ring_ | views::chunk(16) | views::transform([](auto range) {
      auto r = ranges::accumulate(
        range, 0u, std::bit_xor{});
      return r;
    });
    ranges::copy(hexstring, result.begin());
    return result;
  }
  std::string str(std::string_view s)
  {
    auto r = (*this)(s);
    auto hexstring = r | views::transform([](auto t) {
      std::string result;
      char hex[] = "0123456789abcdef";
      result += hex[(t / 16)];
      result += hex[(t % 16)];
      return result;
    });
    std::string sres;
    return ranges::accumulate(hexstring, sres);
  }
};

struct KnotPopCount
{
  template<class T>
  int operator()(const T &t)
  {
    auto r = hash_(t);
    return ranges::accumulate(r, 0, {}, [](auto a) {
      int n = std::popcount(a);
      return n;
    });
  }

private:
  Knothash hash_;
};

template<class T>
int knohhash_popCount(const T &t) noexcept
{
  return std::transform_reduce(t.begin(), t.end(), 0, std::plus{}, KnotPopCount{});
}
int main()
{
  Knothash hash_;
  auto range = views::ints | views::take(128) | views::transform([str = "stpzcrnm"](int i) {
    return str + std::string("-") + std::to_string(i);
  }) | views::common;
  auto n = knohhash_popCount(range);

  std::cout << n << std::endl;
}
