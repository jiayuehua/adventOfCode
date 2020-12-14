#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <numeric>
#include <iomanip>
#include <execution>
#include <range/v3/all.hpp>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <utility>
typedef std::bitset<36> Bitset;
using UInt64 = std::uint64_t;
using Int64 = std::int64_t;

template<class T>
void BitsetAssign(Bitset &bs, const T &t)
{
  Bitset tmp(t);
  for (std::size_t i = 0; i < tmp.size(); ++i) {
    bs[i] = tmp[i];
  }
}
struct Address
{
private:
  Bitset maskfloat_;
  Bitset addr_;
  int total_;
  int curr_ = 0;

public:
  operator bool() const noexcept
  {
    return total_ && (curr_ < total_);
  }

  UInt64 addr() const noexcept
  {
    return addr_.to_ullong();
  }
  friend std::ostream &operator<<(std::ostream &os, const Address &add)
  {
    return os << add.addr_;
  }
  Address(std::string s, UInt64 addr) : addr_(addr)
  {
    std::string sb(s);
    std::string sc(s);
    ranges::replace(s, 'X', '0');
    Bitset maskor(s);
    addr_ |= maskor;

    ranges::replace(sb, '0', '1');
    ranges::replace(sb, 'X', '0');
    Bitset maskand(sb);
    addr_ &= maskand;

    ranges::replace(sc, '1', '0');
    ranges::replace(sc, 'X', '1');
    BitsetAssign(maskfloat_, sc);
    total_ = 1 << maskfloat_.count();
  }
  Address &operator++() &
  {
    int carry = 1;
    for (std::size_t i = 0; i < maskfloat_.size() && carry; ++i) {
      if (maskfloat_[i]) {
        int sum = carry + addr_[i];
        carry = sum / 2;
        int v = sum % 2;
        addr_.set(i, v);
      }
    }
    ++curr_;
    return *this;
  }
};
struct Code
{
private:
  std::string currmask_;

  std::unordered_map<UInt64, Int64> memory_;

public:
  void processMask(std::string &&mask)
  {
    currmask_ = std::move(mask);
  }

  void setvalue(UInt64 addr, Int64 n)
  {
    Address address(currmask_, addr);
    for (; address; ++address) {
      memory_[address.addr()] = n;
    }
  }
  auto total() const
  {
    Int64 n = 0;
    for (auto &&[k, v] : memory_) {
      n += v;
    }
    return n;
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string k, ignore, v;
    Code c;
    while (ifs >> k >> ignore >> v) {
      if (k == "mask") {
        c.processMask(std::move(v));
      } else {
        auto value = std::stol(v);
        UInt64 mem;
        std::sscanf(static_cast<const char *const>(k.c_str()), "mem[%lu]", &mem);
        c.setvalue(mem, value);
      }
    }
    fmt::print("{}", c.total());
  }
}