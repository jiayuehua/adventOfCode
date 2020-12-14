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

struct Code
{
  std::bitset<36> maskor_;
  std::bitset<36> maskand_;
  std::unordered_map<int, std::bitset<36>> memory_;
  void setmask(std::string s) noexcept
  {
    //std::cout << s << std::endl;
    std::string sb(s);
    ranges::replace(s, 'X', '0');
    std::bitset<36> mask_or(s);
    for (std::size_t i = 0; i < maskor_.size(); ++i) {
      maskor_[i] = mask_or[i];
    }
    fmt::print("maskor_:");
    std::cout << maskor_ << std::endl;
    ranges::replace(sb, 'X', '1');
    std::bitset<36> maskand(sb);
    for (std::size_t i = 0; i < maskand_.size(); ++i) {
      maskand_[i] = maskand[i];
    }
    fmt::print("maskand_:");
    std::cout << maskand_ << std::endl;
  }
  void setvalue(int addr, long n) noexcept
  {
    fmt::print("addr:{},n:{}\n", addr, n);
    std::bitset<36> bset = static_cast<unsigned long long>(n);
    bset &= maskand_;
    bset |= maskor_;
    memory_[addr] = bset;
  }
  auto total() const
  {
    std::uint64_t n = 0;
    for (auto [k, v] : memory_) {
      n += v.to_ullong();
    }
    return n;
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    //mask = 00000X110010111111X000100XX01010000X
    //mem[20690] = 435
    std::string k, ignore, v;
    Code c;
    while (ifs >> k >> ignore >> v) {
      if (k == "mask") {
        c.setmask(v);
      } else {
        auto value = std::stol(v);
        int mem;
        std::sscanf(static_cast<const char *const>(k.c_str()), "mem[%d]", &mem);
        c.setvalue(mem, value);
      }
    }
    fmt::print("{}", c.total());
  }
}