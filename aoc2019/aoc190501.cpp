#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <fmt/format.h>
namespace views = ranges::views;
class Program
{
  std::vector<int> mem_;
  int value_ = 1;

public:
  friend std::istream &operator>>(std::istream &is, Program &p)
  {
    ranges::istream_view<int> iv(is);
    std::vector<int> v;
    ranges::copy(iv, std::back_inserter(p.mem_));
    return is;
  }
  int readPos(int addr, int mode)
  {
    if (mode == 1) {
      return addr;
    } else {
      return mem_[addr];
    }
  }

  void run() noexcept
  {
    auto sz = mem_.size();

    for (auto i = 0;;) {
      auto op = mem_[i] % 100;
      auto mode = mem_[i] / 100;
      int m[3]{};
      for (int k = 1; mode; ++k) {
        m[k] = mode % 10;
        mode /= 10;
      }
      if (op == 99) {
        break;
      } else if (op == 1) {
        mem_[mem_[i + 3]] = readPos(mem_[i + 1], m[1]) + readPos(mem_[i + 2], m[2]);
        i += 4;
      } else if (op == 2) {
        mem_[mem_[i + 3]] = readPos(mem_[i + 1], m[1]) * readPos(mem_[i + 2], m[2]);
        i += 4;
      } else if (op == 3) {
        mem_[mem_[i + 1]] = value_;
        i += 2;
      } else if (op == 4) {
        fmt::print("v:{},", mem_[mem_[i + 1]]);
        i += 2;
      }
    }
    //return mem_[0];
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Program p;
    ifs >> p;
    p.run();
  }
}
