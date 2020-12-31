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
  int soundhz_ = 0;
  int pos_ = 0;
  std::unordered_map<std::string, gint> m;
  std::vector<std::tuple<std::string, std::string, std::string>> ops_;
  std::optional<int> recover_;

public:
  Machine()
  {
    calls_["snd"] = &Machine::snd;
    calls_["set"] = &Machine::set;
    calls_["add"] = &Machine::add;
    calls_["mul"] = &Machine::mul;
    calls_["mod"] = &Machine::mod;
    calls_["rcv"] = &Machine::rcv;
    calls_["jgz"] = &Machine::jgz;
  }
  friend std::istream &operator>>(std::istream &is, Machine &machine)
  {
    std::string op, opanda, opandb;
    while (is >> op >> opanda >> opandb) {
      machine.ops_.push_back(std::make_tuple(op, std::move(opanda), std::move(opandb)));
    }
    return is;
  }

  void snd(const std::string &operand, const std::string &)
  {
    soundhz_ = getvalue(operand);
    ++pos_;
  }
  void mod(const std::string &operand, const std::string &v)
  {
    m[operand] %= getvalue(v);
    ++pos_;
  }
  void mul(const std::string &operand, const std::string &v)
  {
    m[operand] *= getvalue(v);
    ++pos_;
  }
  void set(const std::string &operand, const std::string &v)
  {
    m[operand] = getvalue(v);
    ++pos_;
  }
  void add(const std::string &operand, const std::string &v)
  {
    m[operand] += getvalue(v);
    ++pos_;
  }
  void rcv(const std::string &operand, const std::string &v)
  {
    if (m[operand]) {
      recover_ = soundhz_;
    }
    ++pos_;
  }
  void jgz(const std::string &operand, const std::string &v)
  {
    int n = getvalue(operand);
    int value = getvalue(v);
    if (n > 0) {
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
    return (0 <= pos_) && (pos_ < ops_.size()) && !recover_;
  }
  void execute()
  {
    while (valid()) {
      fmt::print("a:{},b:{},i:{},p:{},f:{};", m["a"], m["b"], m["i"], m["p"], m["f"]);

      fmt::print("{},{} {} {}\n", pos_, std::get<0>(this->ops_[pos_]), std::get<1>(this->ops_[pos_]), std::get<2>(this->ops_[pos_]));
      auto op = calls_[std::get<0>(this->ops_[pos_])];
      (this->*op)(std::get<1>(this->ops_[pos_]), std::get<2>(this->ops_[pos_]));
    }
  }
  std::optional<int> getrecover() const
  {
    return recover_;
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Machine m;
    ifs >> m;
    m.execute();
    if (auto o = m.getrecover(); o) {
      fmt::print("{}\n", *o);
    }
  }
}