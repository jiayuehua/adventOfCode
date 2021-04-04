#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#include <memory>
#include <cctype>
#include <range/v3/algorithm.hpp>
using cstring = std::string;

unsigned short fand(unsigned short l, unsigned short r)
{
  return l & r;
}
unsigned short ffor(unsigned short l, unsigned short r)
{
  return l | r;
}
unsigned short flshift(unsigned short l, unsigned short r)
{
  return l << r;
}
unsigned short frshift(unsigned short l, unsigned short r)
{
  return l >> r;
}
unsigned short fnot(unsigned short l, unsigned short r)
{
  return ~l;
}
unsigned short fassign(unsigned short l, unsigned short r)
{
  return l;
}
typedef unsigned short (*Func)(unsigned short, unsigned short);

std::optional<unsigned short> getvalue(const std::string &operand)
{
  if (std::isdigit(operand[0]) || operand[0] == '-') {
    return std::stoi(operand);
  } else {
    return std::nullopt;
  }
}
struct Binop
{
  Func fun;
  std::vector<std::string> childs;
};
struct Node
{
  std::string name;
  std::map<std::string, unsigned short> *ptables_ = 0;
  Func fun = nullptr;
  unsigned short value;
  std::vector<Node> childs;
  auto operator<=>(const std::string &other) const
  {
    return name <=> other;
  }
  auto operator<=>(const Node &other) const
  {
    return name <=> other.name;
  }
  unsigned short calTotal()
  {
    unsigned short lhs = 0;
    unsigned short rhs = 0;
    if (auto it = ptables_->find(name); it != ptables_->end()) {
      return it->second;
    }
    std::vector<int> opands(2);
    for (int i = 0; i < childs.size(); ++i) {
      opands[i] = childs[i].calTotal();
    }
    auto r = fun(opands[0], opands[1]);
    (*ptables_)[name] = r;
    return r;
  }
};

struct compare
{
  using is_transparent = void;
  bool operator()(const Node &l, const Node &r) const
  {
    return l < r;
  }
  bool operator()(const Node &l, const std::string &r) const
  {
    return l.name < r;
  }
  bool operator()(const std::string &l, const Node &r) const
  {
    return l < r.name;
  }
};
struct Table
{
  std::map<std::string, Binop> binops;
  Node root_;
  std::string rootname_;
  std::map<std::string, unsigned short> values;
  int total_;
  unsigned short insert(std::string const &name)
  {
    if (auto i = values.find(name); i != values.end()) {
      return i->second;
    }
    if (auto it = binops.find(name); it != binops.end()) {
      std::vector<unsigned short> v(2);
      ranges::transform(it->second.childs, v.begin(), [this](std::string const &v) { return insert(v); });
      unsigned short val = it->second.fun(v[0], v[1]);
      values[name] = val;
      return val;
    }
  }
  unsigned short total()
  {
    return total_;
  }
  Table(std::string const &s) : rootname_(s)
  {
  }
  friend std::istream &operator>>(std::istream &ifs, Table &table)
  {
    std::map<std::string, Func> ops;
    ops["AND"] = fand;
    ops["OR"] = ffor;
    ops["LSHIFT"] = flshift;
    ops["RSHIFT"] = frshift;
    ops["NOT"] = fnot;
    ops["Assign"] = fassign;
    std::string line;
    while (std::getline(ifs, line)) {
      std::istringstream iss(line);
      std::vector<std::string> vs;
      std::string s;
      while (iss >> s) {
        vs.push_back(s);
      }
      if (vs.size() == 5) {
        Binop binop{ ops[vs[1]] };
        binop.childs.push_back(vs[0]);
        binop.childs.push_back(vs[2]);
        table.binops[vs[4]] = binop;
        if (auto o = getvalue(vs[2]); o) {
          table.values[vs[2]] = *o;
        }
      } else if (vs.size() == 4) {
        Binop binop{ ops["NOT"], { vs[1] } };
        table.binops[vs[3]] = binop;
      } else if (vs.size() == 3) {
        if (auto o = getvalue(vs[0]); o) {
          table.values[vs[2]] = *o;
        } else {
          Binop Binop{ ops["Assign"], { vs[0] } };
          table.binops[vs[2]] = Binop;
        }
      }
    }
    table.total_ = table.insert(table.rootname_);

    return ifs;
  }
};

int main(int argc, char **argv)
{
  if (argc > 2) {
    std::ifstream ifs(argv[1]);

    Table table(argv[2]);
    ifs >> table;
    std::cout << table.total() << std::endl;
  }
}