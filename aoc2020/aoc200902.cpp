#include <unordered_set>
#include <utility>
#include <fstream>
#include <fmt/format.h>
#include <string>
#include <set>
#include <queue>
#include <cstdint>
#include <numeric>
using intl = std::int64_t;
struct Subset
{
  static constexpr intl expected_ = 167829540;
  bool push(intl n)
  {
    if (sum + n == expected_) {
      sum += n;
      s_.insert(n);
      q_.push_back(n);
      return true;
    } else if (sum + n < expected_) {
      s_.insert(n);
      q_.push_back(n);
      sum += n;
      return false;
    } else {
      while (sum + n > expected_ && !q_.empty()) {
        s_.erase(q_.front());
        sum -= q_.front();
        q_.pop_front();
      }
      if (sum + n == expected_) {
        s_.insert(n);
        sum += n;
        q_.push_back(n);
        return true;
      }
      if (sum + n < expected_) {
        s_.insert(n);
        q_.push_back(n);
        sum += n;
        return false;
      }
      return false;
    }
  }
  intl min() const
  {
    return *s_.begin();
  }
  intl max() const
  {
    auto i = s_.end();
    --i;
    return *i;
  }
  intl sum = 0;
  std::deque<intl> q_;
  std::set<intl> s_;
};
int main(int argc, char **argv)
{
  Subset s;
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    intl t;
    while (ifs >> t && !s.push(t)) {
    }
    fmt::print("{}\n", s.min() + s.max());
  }
}
