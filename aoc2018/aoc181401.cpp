#include <complex>
#include <exception>
#include <fstream>
#include <set>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <list>
#include <array>
#include <cstdint>
namespace views = ranges::views;
using Iter = std::vector<int>::iterator;
class Marble
{
  std::list<int> recipes_;
  int startId_;
  auto nextRecipeIndex(std::list<int>::iterator it)
  {
    auto n = *it;
    ++n;
    for (int i = 0; i < n; ++i) {
      ++it;
      if (it == recipes_.end()) {
        it = recipes_.begin();
      }
    }
    return it;
  }

public:
  Marble(int n) : startId_(n), recipes_{ 3, 7 }
  {
    auto ia = recipes_.begin();
    auto ib = std::next(ia, 1);
    for (int i = 0; i < n + 10; ++i) {
      auto na = (*ia + *ib) / 10;
      auto nb = (*ia + *ib) % 10;
      if (na > 0) {
        recipes_.push_back(na);
      }
      recipes_.push_back(nb);
      //ranges::copy(recipes_, std::ostream_iterator<int>(std::cout, ","));
      //std::cout << " \n";
      ia = nextRecipeIndex(ia);
      ib = nextRecipeIndex(ib);
      //std::cout << "ia:" << *ia;
      //std::cout << ",ib" << *ib << std::endl;
      //std::cout << recipes_.size() << std::endl;
    }
  }
  friend std::ostream &operator<<(std::ostream &os, const Marble &m)
  {
    auto i = m.recipes_.cbegin();
    auto b = std::next(i, m.startId_);
    for (int i = 0; i < 10; ++i, ++b) {
      os << *b;
    }
    return os;
  }
};

int main(int argc, char **argv)
{
  {

    Marble m(9);
    std::cout << m << std::endl;
  }
  {

    Marble m(5);
    std::cout << m << std::endl;
  }
  {

    Marble m(18);
    std::cout << m << std::endl;
  }
  {

    Marble m(2018);
    std::cout << m << std::endl;
  }
  {

    Marble m(824501);
    std::cout << m << std::endl;
  }
}
