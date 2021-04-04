#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <cctype>
#include <unordered_map>
#include <map>
#include <cstdint>
using gint = std::int64_t;
class Machine
{
  typedef void (Machine::*MemFunc)(const std::string &l, const std::string &r);

  std::map<std::string, MemFunc> calls_;
  int pos_ = 0;
  std::unordered_map<std::string, gint> m;
  std::vector<std::tuple<std::string, std::string, std::string>> ops_;
  int mul_ = 0;

public:
  Machine()
  {
    calls_["set"] = &Machine::set;
    calls_["sub"] = &Machine::sub;
    calls_["mul"] = &Machine::mul;
    calls_["jnz"] = &Machine::jnz;
    m["a"] = 1;
  }
  int mulCnt() const
  {
    return mul_;
  }
  friend std::istream &operator>>(std::istream &is, Machine &machine)
  {
    std::string op, opanda, opandb;
    while (is >> op >> opanda >> opandb) {
      machine.ops_.push_back(std::make_tuple(op, std::move(opanda), std::move(opandb)));
    }
    return is;
  }

  void sub(const std::string &operand, const std::string &v)
  {
    m[operand] -= getvalue(v);
    ++pos_;
  }
  void mul(const std::string &operand, const std::string &v)
  {
    m[operand] *= getvalue(v);
    ++pos_;
    ++mul_;
  }
  void set(const std::string &operand, const std::string &v)
  {
    m[operand] = getvalue(v);
    ++pos_;
  }
  void jnz(const std::string &operand, const std::string &v)
  {
    int n = getvalue(operand);
    int value = getvalue(v);
    if (pos_ == 14) {
      if (m["d"]) {
        m["g"] += (m["b"] - m["d"] * m["e"]) / m["d"] * m["d"];
        m["e"] += (m["b"] / m["d"]);
      }
      n = m["g"];
    } else if (pos_ = 19) {
      m["d"] = 2;
      m["b"] =
    }

    if (n) {
      pos_ += value;
    } else {
      ++pos_;
    }
  }

  gint getvalue(const std::string &operand)
  {
    if (std::isdigit(operand[0]) || operand[0] == '-') {
      return std::stoi(operand);
    } else {
      return m[operand];
    }
  }
  bool isnumber(const std::string &s) const
  {
    return std::isdigit(s[0]) || s[0] == '-';
  }
  bool valid() const
  {
    return (0 <= pos_) && (pos_ < ops_.size());
  }

  void execute()
  {
    while (valid()) {
      fmt::print("a:{},b:{},c:{},d:{},e:{},f:{},g:{},h:{};", m["a"], m["b"], m["c"], m["d"], m["e"], m["f"], m["g"], m["h"]);

      fmt::print(" {}: {} {} {}\n", pos_, std::get<0>(this->ops_[pos_]), std::get<1>(this->ops_[pos_]), std::get<2>(this->ops_[pos_]));
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
    std::cout << m.mulCnt() << std::endl;
  }
}