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

public:
  friend std::istream &operator>>(std::istream &is, Program &p)
  {
    ranges::istream_view<int> iv(is);
    std::vector<int> v;
    ranges::copy(iv, std::back_inserter(p.mem_));
    p.mem_[1] = 12;
    p.mem_[2] = 2;
    return is;
  }
  void setN(int n)
  {
    mem_[1] = n;
  }
  void setV(int v)
  {
    mem_[2] = v;
  }
  int run() noexcept
  {
    auto v = mem_ | views::chunk(4);
    for (auto sub : v) {
      if (sub[0] == 99) {
        break;
      } else if (sub[0] == 1) {
        mem_[sub[3]] = mem_[sub[1]] + mem_[sub[2]];
      } else if (sub[0] == 2) {
        mem_[sub[3]] = mem_[sub[1]] * mem_[sub[2]];
      }
    }
    return mem_[0];
  }
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Program p;
    ifs >> p;
    for (int i = 0; i < 100; ++i) {
      for (int j = 0; j < 100; ++j) {
        Program b = p;
        b.setN(i);
        b.setV(j);
        if (b.run() == 19690720) {
          fmt::print("{}\n", i * 100 + j);
          break;
        }
      }
    }
    //std::cout << p.run() << std::endl;
  }
}
