#include <range/v3/all.hpp>
#include <unordered_set>
#include <fstream>
#include <iterator>
#include <fmt/format.h>
#include <optional>
struct TwoNumMul
{
private:
  std::unordered_set<int> num_;
  std::optional<int> res_;

public:
  explicit TwoNumMul(const char *file)
  {
    std::ifstream ifs(file);
    ranges::istream_view<int> iv(ifs);
    for (auto i = iv.begin(); i != iv.end(); ++i) {
      int v = *i;
      if (auto it = num_.find(2020 - v); it != num_.end()) {
        res_.emplace(v * *it);
        break;
      } else {
        num_.insert(v);
      }
    }
  }
  auto getResult() const noexcept
  {
    return res_;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    TwoNumMul a(argv[1]);
    int n = a.getResult().value_or(0);
    fmt::print("{}\n", n);
  }
}