#include <fstream>
#include <sstream>
#include <iostream>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <deque>
#include <algorithm>
#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
namespace views = ranges::views;
class Op
{
  std::string s_;

public:
  friend std::ostream &operator<<(std::ostream &os, const Op &op)
  {
    os << op.s_;
    return os;
  }
  auto str() const
  {
    return s_;
  }
  Op(std::string l) : s_(std::move(l)) {}
  void swapposition(std::string l, std::string r)
  {
    auto x = std::stoi(l);
    auto y = std::stoi(r);
    std::swap(s_[x], s_[y]);
  }

  void swapletter(std::string x, std::string y)
  {
    int l = s_.find(x);
    int r = s_.find(y);
    std::iter_swap(s_.begin() + l, s_.begin() + r);
  }
  void rotateleft(std::string l, std::string)
  {
    auto x = std::stoi(l);
    x %= s_.size();
    ranges::rotate(s_, s_.begin() + x);
  }
  void rotateright(std::string l, std::string)
  {
    auto x = std::stoi(l);
    x %= s_.size();
    ranges::rotate(s_, s_.begin() + s_.size() - x);
  }
  void rotaterightImpl(int x)
  {
    x %= s_.size();
    ranges::rotate(s_, s_.begin() + s_.size() - x);
  }
  void reversepositions(std::string l, std::string r)
  {
    auto x = std::stoi(l);
    auto y = std::stoi(r);

    ++y;
    ranges::reverse(s_ | views::drop(x) | views::take(y - x));
  }
  void moveposition(std::string l, std::string r)
  {
    auto x = std::stoi(l);
    auto y = std::stoi(r);
    if (x < y) {
      ranges::rotate(s_ | views::drop(x) | views::take(y - x + 1) | views::common, s_.begin() + x + 1);
    } else {
      std::swap(x, y);
      ranges::rotate(s_ | views::drop(x) | views::take(y - x + 1) | views::common, s_.begin() + x + y - x);
    }
  }
  void rotatebased(std::string c, std::string r)
  {
    auto i = s_.find(r);
    if (i != s_.npos) {
      rotaterightImpl(1 + i + (i >= 4));
    }
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {

    typedef void (Op::*Call)(std::string, std::string);
    std::map<std::string, Call> m;
    m["swapposition"] = &Op::swapposition;
    m["swapletter"] = &Op::swapletter;
    m["reversepositions"] = &Op::reversepositions;
    m["rotateleft"] = &Op::rotateleft;
    m["rotateright"] = &Op::rotateright;
    m["moveposition"] = &Op::moveposition;
    m["rotatebased"] = &Op::rotatebased;
    std::ifstream ifs(argv[1]);
    std::string line;
    std::string call, arga, argb;
    std::string s("abcdefgh");
    std::vector<std::string> vs;
    for (; std::getline(ifs, line);) {
      vs.push_back(line);
    }
    while (ranges::next_permutation(s)) {
      std::string sb(s);

      Op op(s);
      for (auto oneline : vs) {
        std::istringstream iss(oneline);
        while (iss >> call >> arga >> argb) {
          //std::cout << oneline << std::endl;
          (op.*m[call])(arga, argb);
        }
      }
      if (op.str() == "fbgdceah") {
        std::cout << sb << std::endl;
        break;
      }
    }
  }
}
