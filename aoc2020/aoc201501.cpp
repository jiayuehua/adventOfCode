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
  std::vector<int> numbers_;

public:
  NumberList(std::initializer_list<int> l) : numbers_(l.begin(), l.end())
  {
    for (int i = 0; i < static_cast<int>(numbers_.size()); ++i) {
      numlastPos_[numbers_[static_cast<std::size_t>(i)]] = i;
    }
  }
  void push_back()
  {
    auto last = numbers_.back();
    auto itsecond = numsecondlastPos_.find(last);
    if (itsecond == numsecondlastPos_.end()) {
      numbers_.push_back(0);
      if (numlastPos_.find(0) != numlastPos_.end()) {

        numsecondlastPos_[0] = numlastPos_[0];
      }
      numlastPos_[0] = static_cast<int>(numbers_.size()) - 1;
    } else {
      auto diff = numlastPos_[last] - numsecondlastPos_[last];
      numbers_.push_back(diff);
      if (numlastPos_.find(diff) != numlastPos_.end()) {

        numsecondlastPos_[diff] = numlastPos_[diff];
      }
      numlastPos_[diff] = static_cast<int>(numbers_.size()) - 1;
    }
  }
  auto const &getnumbers() const
  {
    return numbers_;
  }
};


int main()
{
  NumberList nl{ 5, 1, 9, 18, 13, 8, 0 };
  for (int i = 0; i < 2020 - 7; ++i) {
    nl.push_back();
  }
  auto const &numbers = nl.getnumbers();
  //for (auto i : numbers) {
  fmt::print("{} ", numbers.back());
  //}
  fmt::print("===\n");
}