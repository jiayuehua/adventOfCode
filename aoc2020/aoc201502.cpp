#include <fstream>
#include <sstream>
#include <iostream>
#include <fmt/format.h>
#include <string>
#include <numeric>
#include <iomanip>
#include <execution>
#include <range/v3/all.hpp>
#include <algorithm>
#include <unordered_map>
#include <initializer_list>

struct NumberList
{
private:
  std::unordered_map<int, int> numlastPos_;
  std::unordered_map<int, int> numsecondlastPos_;
  int sz_ = 0;
  int last_ = 0;

public:
  NumberList(const std::vector<int> &l) : sz_(static_cast<int>(l.size()))
  {
    auto b = l.begin();

    for (int i = 0; i < sz_; ++i, ++b) {
      numlastPos_[*b] = i;
      last_ = *b;
    }
  }
  void push_back()
  {
    auto itsecond = numsecondlastPos_.find(last_);
    ++sz_;
    if (itsecond == numsecondlastPos_.end()) {
      last_ = 0;
      if (numlastPos_.find(last_) != numlastPos_.end()) {

        numsecondlastPos_[last_] = numlastPos_[last_];
      }
      numlastPos_[last_] = sz_ - 1;
    } else {
      auto diff = numlastPos_[last_] - numsecondlastPos_[last_];
      if (numlastPos_.find(diff) != numlastPos_.end()) {
        numsecondlastPos_[diff] = numlastPos_[diff];
      }
      numlastPos_[diff] = sz_ - 1;
      last_ = diff;
    }
  }
  int getnumber() const noexcept
  {
    return last_;
  }
};
struct NthNumber
{
  int operator()(int n, const std::vector<int> &l) const
  {
    NumberList nl(l);
    if (static_cast<std::size_t>(n) > l.size()) {

      for (int i = 0; i < n - static_cast<int>(l.size()); ++i) {
        nl.push_back();
      }
      return nl.getnumber();
    } else {
      return l[static_cast<std::size_t>(n) - 1];
    }
  }
};


int main()
{
  NthNumber n;
  std::vector<int> v{ 5, 1, 9, 18, 13, 8, 0 };
  auto num = n(30000000, v);
  fmt::print("{} ", num);
  fmt::print("===\n");
}