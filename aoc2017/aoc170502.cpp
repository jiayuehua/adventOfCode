#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
namespace views = ranges::views;

struct Jumptable
{
  std::vector<int> table_;
  int curr_ = 0;
  int count_ = 0;
  friend std::istream &operator>>(std::istream &is, Jumptable &j)
  {
    std::istream_iterator<int> b(is);
    std::istream_iterator<int> e;
    std::copy(b, e, std::back_inserter(j.table_));
    return is;
  }

  bool jump()
  {
    if (curr_ >= table_.size() || curr_ < 0) {
      return false;
    } else {

      auto t = table_[curr_];
      if (t >= 3) {
        --table_[curr_];
      } else {
        ++table_[curr_];
      }
      ++count_;
      curr_ += t;
      return true;
    }
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string line;
    int validcount = 0;
    Jumptable j;
    ifs >> j;
    while (j.jump()) {
    }
    std::cout << j.count_ << std::endl;
  }
}