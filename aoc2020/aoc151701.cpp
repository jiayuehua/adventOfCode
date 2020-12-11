#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <numeric>
#include <iomanip>
#include <execution>
#include <range/v3/all.hpp>
#include "matrix.h"

struct Property
{
  int cap_;
  int dur_;
  int fla_;
  int txt_;
};
namespace views = ranges::views;
struct Combination
{
private:
  std::vector<int> base_;
  std::vector<int> id_;
  std::vector<int> sizevec_;

  int count_ = 0;
  int size_ = 0;

  void combinationCounts(std::size_t j, int n) noexcept
  {
    if (base_.size() - 1 == j) {
      bool valid = (n == base_[j]) || !n;

      if (valid) {
        if (n) {
          id_.push_back(n);
        }
        sizevec_.push_back(id_.size());
        //std::ostream_iterator<int> osi(std::cout, ",");
        //ranges::copy(id_, osi);
        if (n) {
          id_.pop_back();
        }
        //std::cout << std::endl;
      }
      count_ += (valid);
    } else {
      int cnt = (base_[j] <= n);
      for (int i = 0; i <= cnt; ++i) {

        if (i) {
          id_.push_back(
            base_[j]);
        }
        combinationCounts(j + 1, n - i * base_[j]);
        if (i) {
          id_.pop_back();
        }
      }
    }
  }

public:
  Combination(std::vector<int> &&base, int sum) noexcept : base_(std::move(base))
  {
    combinationCounts(0, sum);
    auto minit = ranges::min_element(sizevec_);
    size_ = ranges::count(sizevec_, *minit);
  }
  int count() const noexcept
  {
    return count_;
  }
  int size() const noexcept
  {
    return size_;
  }
};

int main(int argc, char **argv)
{

  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    int i;
    std::vector<int> v;
    while (ifs >> i) {
      v.push_back(i);
    }
    ranges::sort(v);
    std::vector vb(v);
    Combination com(std::move(v), 150);
    fmt::print("{}\n", com.size());
    fmt::print("{}\n", com.count());
  }
}