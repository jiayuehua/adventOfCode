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
    std::size_t acc = 0;

    for (std::size_t i = 0; v[i].not_runed_ && i < v.size();) {
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
    fmt::print("{}\n", acc);
  }
}