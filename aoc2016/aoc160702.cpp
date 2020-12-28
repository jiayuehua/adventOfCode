#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <fmt/format.h>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <set>
#include <string_view>
namespace views = ranges::views;
struct Message
{
private:
  std::string name_;
  bool insquare_ = false;
  std::set<std::string_view> squaresv_[2];

public:
  bool count() noexcept
  {
    auto cs = ranges::views::ints | views::take(name_.size() - 2);
    ranges::for_each(cs, [this](auto i) {
      int onbound = false;
      if (name_[i] == '[') {
        insquare_ = true;
        onbound = true;
        return;
      } else if (name_[i] == ']') {
        insquare_ = false;
        onbound = true;
        return;
      }
      if (name_[i] == name_[i + 2] && name_[i] != name_[i + 1] && name_[i + 1] != ']' && name_[i + 1] != '[') {
        std::string_view s(name_.c_str() + i + insquare_, 2);
        squaresv_[insquare_].insert(s);
      }
    });
    std::vector<std::string_view> out;
    ranges::set_intersection(squaresv_[0], squaresv_[1], std::back_inserter(out));
    return !out.empty();
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