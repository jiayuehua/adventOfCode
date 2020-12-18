
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
    thirdweight_ = std::accumulate(packages_.begin(), packages_.end(), 0) / 4;
  }
  std::int64_t maxhappiness() noexcept
  {
    bool found = false;
    int n = 0;
    auto end = this->packages_.end();

    auto fab = [this, end, n, &found](auto ia, auto ib) mutable {
      if (thirdweight_ != std::accumulate(ia, ib, 0)) { return false; }

      auto fbc = [&found, this](auto ib, auto ic) {
        if (std::accumulate(ib, ic, 0) != this->thirdweight_) {
          return false;
        } else {
          //std::ostream_iterator<int> outit(std::cout, ",");
          //std::cout << "ib-ic:";
          //std::copy(ib, ic, outit);
          //std::cout << std::endl;
          auto fcd = [&found, this, ibn = ib](auto ic, auto id) {
            if (std::accumulate(ic, id, 0) != this->thirdweight_) {
              return false;
            } else {
              std::int64_t sum = 1;
              auto minp = std::accumulate(this->packages_.begin(), ibn, sum, std::multiplies{});
              this->minproduct_ = std::min(this->minproduct_, minp);
              found = true;
              return true;
            }

            return false;
          };
          for (auto c = ic + 3; c != (this->packages_.end() - 2) && !found; ++c) {
            for_each_combination(ic, c, this->packages_.end(), fcd);
          }
        }

        return false;
      };
      for (auto b = ib + 3; (b != end - 5) && !found; ++b) {
        for_each_combination(ib, b, end, fbc);
      }
      return false;
    };

    for (auto a = packages_.begin() + 3; (a != end - 8) && !found; ++a) {
      for_each_combination(packages_.begin(), a, end, fab);
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