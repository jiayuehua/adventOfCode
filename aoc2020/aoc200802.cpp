#include <unordered_set>
#include <fstream>
#include <sstream>
#include <fmt/format.h>
#include <string>
#include <unordered_map>
#include <execution>
#include <tuple>
#include <functional>
#include <limits>
#include <numeric>
#include <range/v3/all.hpp>
struct Instuction
{
  bool not_runed_ = true;
  std::string op_;
  std::size_t opand_;
};


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    std::vector<Instuction> v;

    while (std::getline(ifs, s)) {
      std::istringstream iss(s);
      Instuction instruct;
      iss >> instruct.op_ >> instruct.opand_;
      v.push_back(std::move(instruct));
    }
    for (std::size_t k = 0; k < v.size(); ++k) {
      std::string oldop;
      if (v[k].op_ == "jmp") {
        oldop = std::exchange(v[k].op_, "nop");
      } else if (v[k].op_ == "nop") {
        oldop = std::exchange(v[k].op_, "jmp");
      } else {
        continue;
      }
      std::size_t acc = 0;
      std::size_t i = 0;
      for (; v[i].not_runed_ && i < v.size();) {
        v[i].not_runed_ = false;
        if (v[i].op_ == "nop") {
          ++i;
        } else if (v[i].op_ == "acc") {
          acc += v[i].opand_;
          ++i;
        } else if (v[i].op_ == "jmp") {
          i += v[i].opand_;
        }
      }
      if (i >= v.size()) {
        fmt::print("{}", acc);
        break;
      }
      v[k].op_ = oldop;
      for (i = 0; i < v.size(); ++i) {
        v[i].not_runed_ = true;
      }
    }
  }
}