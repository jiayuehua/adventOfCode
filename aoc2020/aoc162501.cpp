#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <cctype>
#include <execution>
#include <unordered_map>
#include <map>
#include <range/v3/all.hpp>
namespace views = ranges::views;
struct Machine
{
  int ValidCount = 20;
  typedef void (Machine::*MemFunc)(const std::string &l, const std::string &r);
  //std::array<int, 6> out_;
  int outid_ = 0;
  int expected_ = 0;
  bool outputvalid_ = false;

  std::map<std::string, MemFunc> calls_;
  Machine()
  {
    m["a"] = 0;
    m["b"] = 0;
    m["c"] = 0;
    m["d"] = 0;
    calls_["cpy"] = &Machine::cpy;
    calls_["dec"] = &Machine::dec;
    calls_["inc"] = &Machine::inc;
    calls_["jnz"] = &Machine::jnz;
    calls_["out"] = &Machine::out;
  }
  void setA(int n)
  {
    m["a"] = n;
  }

  friend std::istream &operator>>(std::istream &is, Machine &m)
  {
    std::string op, opanda, opandb;
    std::string line;
    while (std::getline(is, line)) {
      std::istringstream iss(line);
      iss >> op >> opanda >> opandb;
      {
        m.ops_.push_back(std::make_tuple(op, std::move(opanda), std::move(opandb)));
      }
    }
    return is;
  }

  int pos_ = 0;
  std::unordered_map<std::string, int> m;
  std::vector<std::tuple<std::string, std::string, std::string>> ops_;
  void jnz(const std::string &operand, const std::string &v)
  {
    if (pos_ == 5) {
      m["d"] += m["b"];
      m["b"] = 0;
      ++pos_;
      return;
    }
    if (pos_ == 7) {
      m["d"] += m["c"] * 365;
      m["c"] = 0;
      m["b"] = 0;
      ++pos_;
      return;
    }
    if (pos_ == 17) {
      auto minnum = std::min(m["b"], m["c"]);
      m["c"] -= minnum;
      m["b"] -= minnum;
    }
    int n = getvalue(operand);
    int value = getvalue(v);
    if (n) {
      pos_ += value;
    } else {
      ++pos_;
    }
  }

  int getvalue(const std::string &operand)
  {
    int n;
    if (std::isdigit(operand[0]) || operand[0] == '-') {
      n = std::stoi(operand);
    } else {
      n = m[operand];
    }
    return n;
  }
  bool isnumber(const std::string &s) const
  {
    return std::isdigit(s[0]) || s[0] == '-';
  }
  void cpy(const std::string &lhs, const std::string &rhs)
  {
    if (!isnumber(rhs)) {

      auto value = getvalue(lhs);
      m[rhs] = value;
    }
    ++pos_;
  }

  void out(const std::string &lhs, const std::string &)
  {
    if (outid_ < ValidCount) {
      if (m[lhs] == expected_) {
        ++outid_;
        expected_ = !expected_;

      } else {
        outid_ = 100;
      }
    }
    ++pos_;
    outputvalid_ = (outid_ == ValidCount);
  }
  void inc(const std::string &lhs, const std::string &)
  {
    ++m[lhs];
    ++pos_;
  }
  void dec(const std::string &lhs, const std::string &)
  {
    --m[lhs];
    ++pos_;
  }
  void outputreg() noexcept
  {
    fmt::print("pos:{},{} {} {}\n", pos_, std::get<0>(this->ops_[pos_]), std::get<1>(this->ops_[pos_]), std::get<2>(this->ops_[pos_]));
    fmt::print("a:{},b:{},c:{},d:{};", m["a"], m["b"], m["c"], m["d"]);
  }
  bool valid() const
  {
    return valid(pos_) && outid_ < ValidCount;
  }
  bool valid(int pos) const
  {
    return (0 <= pos) && (pos < ops_.size());
  }
  bool execute()
  {
    while (valid()) {
      if (pos_ == 27) {

      } else {
        //outputreg();
      }
      auto op = calls_[std::get<0>(this->ops_[pos_])];
      (this->*op)(std::get<1>(this->ops_[pos_]), std::get<2>(this->ops_[pos_]));
    }
    return outputvalid_;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Machine m;
    ifs >> m;
    Machine mb(m);
    int i = 0;
    fmt::print("{}\n", i);
    int N = 1000;
    std::vector<int> v(N);
    int max = std::numeric_limits<int>::max();
    fmt::print("{}\n", max);
    ranges::copy(views::ints | views::take(N), v.begin());
    int r = std::transform_reduce(
      std::execution::par_unseq, v.begin(), v.end(), max, [](auto l, auto r) { return std::min(l, r); }, [m](int i) {
      auto mb = m;
      mb.setA(i);
      int rA[] = { std::numeric_limits<int>::max(), i };
      bool res = mb.execute();
      return rA[res]; });
    fmt::print("{}\n", r);
  }
}