#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <cctype>
#include <unordered_map>
#include <map>
#include <range/v3/all.hpp>
struct Machine
{
  typedef void (Machine::*MemFunc)(const std::string &l, const std::string &r);

  std::map<std::string, MemFunc> calls_;
  std::map<std::string, std::string> togglefuns_;
  Machine()
  {
    m["a"] = 12;
    m["b"] = 0;
    m["c"] = 0;
    m["d"] = 0;
    calls_["cpy"] = &Machine::cpy;
    calls_["dec"] = &Machine::dec;
    calls_["inc"] = &Machine::inc;
    calls_["jnz"] = &Machine::jnz;
    calls_["tgl"] = &Machine::tgl;
    togglefuns_["inc"] = "dec";
    togglefuns_["dec"] = "inc";
    togglefuns_["tgl"] = "inc";
    togglefuns_["jnz"] = "cpy";
    togglefuns_["cpy"] = "jnz";
  }
  friend std::istream &operator>>(std::istream &is, Machine &m)
  {
    std::string op, opanda, opandb;
    while (is >> op >> opanda >> opandb) {
      m.ops_.push_back(std::make_tuple(op, std::move(opanda), std::move(opandb)));
    }
    return is;
  }

  int pos_ = 0;
  std::unordered_map<std::string, int> m;
  std::vector<std::tuple<std::string, std::string, std::string>> ops_;
  void jnz(const std::string &operand, const std::string &v)
  {
    int n = getvalue(operand);
    int value = getvalue(v);
    if (n) {
      pos_ += value;
    } else {
      ++pos_;
    }
  }

  void tgl(const std::string &lhs, const std::string &rhs)
  {
    int offset = getvalue(lhs);
    if (valid(pos_ + offset)) {
      auto &op = std::get<0>(ops_[pos_ + offset]);
      op = togglefuns_[op];
    }
    ++pos_;
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
  bool valid() const
  {
    return (0 <= pos_) && (pos_ < ops_.size());
  }
  bool valid(int pos) const
  {
    return (0 <= pos) && (pos < ops_.size());
  }
  void execute()
  {
    while (valid()) {
      //fmt::print("a:{},b:{},c:{},d:{};", m["a"], m["b"], m["c"], m["d"]);
      if (pos_ == 9) {
        m["a"] = m["a"] + m["b"] * m["d"];
        ++pos_;
        continue;
      }

      fmt::print("pos:{},{} {} {}\n", pos_, std::get<0>(this->ops_[pos_]), std::get<1>(this->ops_[pos_]), std::get<2>(this->ops_[pos_]));
      auto op = calls_[std::get<0>(this->ops_[pos_])];
      (this->*op)(std::get<1>(this->ops_[pos_]), std::get<2>(this->ops_[pos_]));
    }
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Machine m;
    ifs >> m;
    m.execute();
    fmt::print("{}\n", m.m["a"]);
  }
}