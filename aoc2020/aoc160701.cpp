#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <fstream>
#include <iterator>
#include <fmt/format.h>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
namespace views = ranges::views;
struct Message
{
private:
  std::string name_;
  bool sub_ = false;
  bool squaresub_ = false;
  bool insquare_ = false;

public:
  int count() noexcept
  {
    auto cs = ranges::views::ints | views::take(name_.size() - 3) | views::transform([this](auto i) {
      int onbound = false;
      if (name_[i] == '[') {
        insquare_ = true;
        onbound = true;
      } else if (name_[i] == ']') {
        insquare_ = false;
        onbound = true;
      }

      auto s = name_ | views::drop(i) | views::take(2);
      auto r = name_ | views::drop(i + 2) | views::take(2) | views::reverse;
      if (!insquare_ && ranges::equal(s, r) && s[0] != s[1]) {
        sub_ = true;
      }
      if (insquare_ && ranges::equal(s, r) && s[0] != s[1]) {
        squaresub_ = true;
      }
      return std::make_pair(sub_, squaresub_);
    });
    auto r = false;
    for (auto [sub, squaresub] : cs) {
      if (squaresub_) {
        return false;
      } else if (sub_) {
        r = true;
      }
    }
    return r;
  }
  friend std::istream &operator>>(std::istream &is, Message &m)
  {
    m = Message{};
    return is >> m.name_;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string st;
    std::string s;
    int cnt = 0;
    Message m;
    while (ifs >> m) {
      cnt += m.count();
    }
    fmt::print("{}\n", cnt);
  }
}