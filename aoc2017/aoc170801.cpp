#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
#include <range/v3/view.hpp>
namespace views = ranges::views;
//ebu inc 626 if iq < 0
constexpr bool lessthan(int l, int r) noexcept
{
  return l < r;
}
constexpr bool lessequal(int l, int r) noexcept
{
  return l <= r;
}
constexpr bool equal(int l, int r) noexcept
{
  return l == r;
}
constexpr bool notequal(int l, int r) noexcept
{
  return l != r;
}
constexpr bool greater(int l, int r) noexcept
{
  return l > r;
}
constexpr bool greaterequal(int l, int r) noexcept
{
  return l >= r;
}
typedef bool (*Compare)(int l, int r) noexcept;
constexpr int inc(int value, Compare c, int opl, int opr) noexcept
{
  if (c(opl, opr)) {
    return value;
  } else {
    return 0;
  }
}
constexpr int dec(int value, Compare c, int opl, int opr) noexcept
{
  if (c(opl, opr)) {
    return -value;
  } else {
    return 0;
  }
}
typedef int (*Inc)(int value, Compare c, int opl, int opr) noexcept;
struct Lineprocess
{
  std::map<std::string, int> regs_;
  std::map<std::string, Inc> ops_;
  std::map<std::string, Compare> cmp_;
  Lineprocess()
  {
    ops_["inc"] = inc;
    ops_["dec"] = dec;
    cmp_["<"] = lessthan;
    cmp_["<="] = lessequal;
    cmp_["=="] = equal;
    cmp_["!="] = notequal;
    cmp_[">"] = greater;
    cmp_[">="] = greaterequal;
  }
  friend std::istream &operator>>(std::istream &is, Lineprocess &l)
  {
    std::string reg, op;
    int value;
    std::string ignore;
    std::string lreg;
    std::string com;
    int r;
    std::string line;
    while (is >> reg >> op >> value >> ignore >> lreg >> com >> r) {
      l.regs_[reg] += (*l.ops_[op])(value, l.cmp_[com], l.regs_[lreg], r);
    }
    return is;
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    Lineprocess lines;
    std::ifstream ifs(argv[1]);
    ifs >> lines;
    std::cout << lines.regs_["ebu"] << std::endl;
    auto v = lines.regs_ | views::values;
    auto m = ranges::max_element(v);
    std::cout << *m << std::endl;
  }
}