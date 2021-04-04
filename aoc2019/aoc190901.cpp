#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <fmt/format.h>
using gint = std::int64_t;
namespace views = ranges::views;
class Program
{
  std::vector<gint> mem_;
  int value_ = 2;
  int relativeBase_ = 0;

public:
  Program() : mem_(1000 * 1000 * 10)
  {
  }
  friend std::istream &operator>>(std::istream &is, Program &p)
  {
    ranges::istream_view<gint> iv(is);
    ranges::copy(iv, p.mem_.begin());
    return is;
  }
  gint readPos(gint addr, int mode)
  {
    if (mode == 1) {
      return addr;
    } else if (mode == 0) {
      return mem_[addr];
    } else if (mode == 2) {
      return mem_[addr + relativeBase_];
    }
  }
  void writePos(gint value, gint addr, int mode)
  {
    if (mode == 1) {
      std::cerr << "error!\n";
    } else if (mode == 0) {
      mem_[addr] = value;
    } else if (mode == 2) {
      mem_[addr + relativeBase_] = value;
    }
  }

  void run() noexcept
  {
    auto sz = mem_.size();

    for (auto i = 0;;) {
      auto op = mem_[i] % 100;
      auto mode = mem_[i] / 100;
      int parammodes[5]{};
      for (int k = 1; mode; ++k) {
        parammodes[k] = mode % 10;
        mode /= 10;
      }
      if (op == 99) {
        break;
      } else if (op == 1) {
        auto n = readPos(mem_[i + 1], parammodes[1]) + readPos(mem_[i + 2], parammodes[2]);
        writePos(n, mem_[i + 3], parammodes[3]);
        i += 4;
      } else if (op == 2) {
        auto n = readPos(mem_[i + 1], parammodes[1]) * readPos(mem_[i + 2], parammodes[2]);
        writePos(n, mem_[i + 3], parammodes[3]);
        i += 4;
      } else if (op == 3) {
        writePos(value_, mem_[i + 1], parammodes[1]);
        i += 2;
      } else if (op == 4) {
        fmt::print("out:{}\n", readPos(mem_[i + 1], parammodes[1]));
        i += 2;
      } else if (op == 5) {
        if (readPos(mem_[i + 1], parammodes[1])) {
          i = readPos(mem_[i + 2], parammodes[2]);
        } else {
          i += 3;
        }
      } else if (op == 6) {
        if (!readPos(mem_[i + 1], parammodes[1])) {
          i = readPos(mem_[i + 2], parammodes[2]);
        } else {
          i += 3;
        }
      } else if (op == 7) {
        auto n = readPos(mem_[i + 1], parammodes[1]) < readPos(mem_[i + 2], parammodes[2]);
        writePos(n, mem_[i + 3], parammodes[3]);
        i += 4;
      } else if (op == 8) {
        auto n = readPos(mem_[i + 1], parammodes[1]) == readPos(mem_[i + 2], parammodes[2]);
        writePos(n, mem_[i + 3], parammodes[3]);
        i += 4;
      } else if (op == 9) {
        relativeBase_ += readPos(mem_[i + 1], parammodes[1]);
        i += 2;
      }
    }
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
