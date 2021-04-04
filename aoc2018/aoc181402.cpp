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
  Marble(std::initializer_list<int> sub) : recipes_{ 3, 7 }
  {
    auto ia = recipes_.begin();
    auto ib = std::next(ia, 1);
    for (int i = 0;; ++i) {
      auto na = (*ia + *ib) / 10;
      auto nb = (*ia + *ib) % 10;
      if (na > 0) {
        recipes_.push_back(na);
      }
      recipes_.push_back(nb);
      if (i % 10000 == 99) {
        if (auto subrange = ranges::search(recipes_, sub); !subrange.empty()) {
          std::cout << std::distance(recipes_.begin(), subrange.begin()) << std::endl;
          break;
        }
      }
      ia = nextRecipeIndex(ia);
      ib = nextRecipeIndex(ib);
    }
  }
  friend std::ostream &operator<<(std::ostream &os, const Marble &m)
  {
  }
};

int main(int argc, char **argv)
{
  Marble m{ 8, 2, 4, 5, 0, 1 };
}
