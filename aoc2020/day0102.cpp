#include <range/v3/all.hpp>
#include <unordered_set>
#include <fstream>
#include <iterator>
#include <fmt/format.h>
#include <optional>
#include <vector>
#include <iterator>
struct threenummul
{
private:
  std::vector<int> num_;
  std::optional<int> res_;
  static inline constexpr int Sum = 2020;

public:
  explicit threenummul(const char *file)
  {
    std::ifstream ifs(file);
    ranges::istream_view<int> iv(ifs);
    ranges::move(iv, std::back_inserter(num_));
    ranges::sort(num_);
    for (auto i = num_.begin(); i != num_.end() - 2; ++i) {
      for (auto j = i + 1; j != num_.end() - 1; ++j) {
        if (ranges::binary_search(j + 1, num_.end(), Sum - *i - *j)) {
          res_.emplace(*i * *j * (Sum - *i - *j));
          goto LABEL;
        }
      }
    }
  LABEL:;
  }
  auto getResult() const noexcept
  {
    return res_;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    threenummul a(argv[1]);
    if (auto option = a.getResult(); option) {
      int n = *option;
      fmt::print("{}\n", n);
    }
  }
}