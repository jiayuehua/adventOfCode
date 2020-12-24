#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <fstream>
#include <cctype>
#include <iterator>
#include <fmt/format.h>
#include <string>
#include <functional>
#include <vector>
#include <numeric>

namespace views = ranges::views;
auto allchars = views::iota('\0') | views::take(256) | views::common;
struct Message
{
private:
  std::string name_;
  std::vector<int> charsCount_;
  std::vector<int> firstpos_;
  std::string allchars_;

  std::string check_;
  static constexpr int DefaultPos = 0;

public:
  int count_ = 0;
  Message() : charsCount_(256), firstpos_(256, DefaultPos), allchars_(allchars.begin(), allchars.end())
  {
  }
  std::string transform() const
  {
    auto r = name_ | views::transform([this](char c) {
      if (std::isalpha(c)) {
        c = (c - 'a' + count_) % 26 + 'a';
      }
      return c;
    }) | views::common;
    std::string s(r.begin(), r.end());
    return s;
  }

  int count() noexcept
  {
    ranges::for_each(name_, [this](char c) { ++charsCount_[c]; });
    auto pos = name_ | views::enumerate;
    ranges::for_each(pos, [this](auto p) {
      auto i = std::get<0>(p);
      auto c = std::get<1>(p);
      if (firstpos_[c] == DefaultPos) {
        firstpos_[c] = 10000 - i;
      }
    });
    auto charsCount = charsCount_;
    auto r = views::zip(charsCount_, firstpos_, allchars_);
    ranges::partial_sort(r, r.begin() + 5, std::greater{});
    ranges::sort(check_);
    int sum = 0;
    for (auto i : check_) {
      if (!charsCount[i]) {
        return 0;
      } else {
        sum += charsCount[i];
      }
    }
    auto top = std::accumulate(charsCount_.begin(), charsCount_.begin() + 5, 0);
    return (sum == top) * count_;
  }
  friend std::istream &operator>>(std::istream &is, Message &m)
  {
    m = Message{};
    return is >> m.name_ >> m.count_ >> m.check_;
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
      auto r = m.transform();
      if (r.find("north") != r.npos) {
        fmt::print("id:{}\n", m.count_);
        break;
      }
    }
    fmt::print("{}\n", cnt);
  }
}