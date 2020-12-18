
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <numeric>
#include <cstdint>

#include <unordered_map>
#include <functional>
#include "combinations_algo.h"
#include <iterator>
struct Combinations
{
  Combinations(std::vector<std::int64_t> v) : packages_(std::move(v))
  {
    thirdweight_ = std::accumulate(packages_.begin(), packages_.end(), 0) / 3;
  }
  std::int64_t maxhappiness() noexcept
  {
    bool found = false;
    int n = 0;
    auto end = this->packages_.end();

    auto fab = [this, end, n, &found](auto ia, auto ib) mutable {
      //std::ostream_iterator<int> outit(std::cout, ",");
      //std::cout << "ia-ib:";
      //std::copy(ia, ib, outit);
      //std::cout << std::endl;
      if (thirdweight_ != std::accumulate(ia, ib, 0)) { return false; }

      auto fbc = [&found, this](auto ib, auto ic) {
        //  std::cout << "fbc\n";
        if (std::accumulate(ib, ic, 0) == this->thirdweight_) {
          std::int64_t sum = 1;
          auto minp = std::accumulate(this->packages_.begin(), ib, sum, std::multiplies{});
          //fmt::print("{}\n", minp);
          //std::ostream_iterator<int> outit(std::cout, ",");
          //std::cout << "valid :";
          //std::copy(this->packages_.begin(), ib, outit);
          //std::cout << std::endl;

          //std::cout << "fbc\n";
          this->minproduct_ = std::min(this->minproduct_, minp);
          found = true;
          return true;
        }

        return false;
      };
      for (auto m = ib; m != end; ++m) {
        for_each_combination(ib, m, end, fbc);
      }
      return false;
    };

    for (auto m = packages_.begin(); m != end && !found; ++m) {
      for_each_combination(packages_.begin(), m, end, fab);
    }
    return minproduct_;
  }

private:
  std::int64_t minproduct_ = std::numeric_limits<std::int64_t>::max();
  std::vector<std::int64_t> packages_;
  int thirdweight_;
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::vector<std::int64_t> packages;
    std::ifstream ifs(argv[1]);
    int i = 0;
    std::string s;
    fmt::print("packages_\n");
    for (; ifs >> i;) {
      packages.push_back(i);
    }
    fmt::print("{}\n", std::accumulate(packages.begin(), packages.end(), 0));
    Combinations com(std::move(packages));

    fmt::print("{}\n", com.maxhappiness());
  }
}