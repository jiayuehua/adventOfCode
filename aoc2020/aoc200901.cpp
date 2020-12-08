#include <unordered_set>
#include <utility>
#include <fstream>
#include <fmt/format.h>
#include <string>
#include <unordered_set>
#include <queue>
#include <cstdint>
using intl = std::int64_t;
struct Cache
{
  std::queue<std::int64_t> q_;
  std::unordered_set<std::int64_t> s_;
  bool push(intl l)
  {
    for (auto i : s_) {
      if (s_.contains(l - i) and (i != (l - i))) {
        s_.erase(q_.front());
        s_.insert(l);
        q_.pop();
        q_.push(l);
        return true;
      }
    }
    return false;
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    intl t;
    std::queue<std::int64_t> q;
    std::unordered_set<std::int64_t> s;


    for (int i = 0; (ifs >> t) and (i < 25); ++i) {
      q.push(t);
      s.insert(t);
    }
    Cache c;
    c.q_ = std::move(q);
    c.s_ = std::move(s);
    while (c.push(t) and (ifs >> t)) {
    }
    fmt::print("{}", t);
  }
}
