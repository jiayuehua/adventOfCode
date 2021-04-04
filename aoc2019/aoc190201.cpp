#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <ranges>
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
    std::cout << p.run() << std::endl;
  }
}
