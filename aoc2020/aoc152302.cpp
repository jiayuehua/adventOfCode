#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <boost/variant.hpp>
#include <unordered_map>
#include <range/v3/all.hpp>
struct Jio
{
};
struct Jie
{
};
struct Inc
{
};
struct Tpl
{
};
struct Hlf
{
};
struct Jmp
{
};
struct Machine
{
  Machine()
  {
    m["packages_"] = 1;
    m["b"] = 0;
  }
  int pos_;
  int minpos_ = 0;
  int maxpos_ = 48;
  std::unordered_map<std::string, int> m;
  std::vector<std::string> ops_;
  void Jio(const std::string &operand, int value)
  {
    int n = m[operand];
    if (n == 1) {
      pos_ += value;
    } else {
      ++pos_;
    }
  }
  void Jie(const std::string &operand, int value)
  {
    int n = m[operand] % 2;
    if (n == 0) {
      pos_ += value;
    } else {
      ++pos_;
    }
  }

  void Tpl(const std::string &operand)
  {
    m[operand] *= 3;
    ++pos_;
  }

  void Hlf(const std::string &operand)
  {
    m[operand] /= 2;
    ++pos_;
  }
  void Inc(const std::string &operand)
  {
    m[operand] += 1;
    ++pos_;
  }
  void Jmp(int value)
  {
    pos_ += value;
  }
  bool valid() const
  {
    return (minpos_ <= pos_) && (pos_ < maxpos_);
  }
  void execute()
  {
    while (valid()) {
      std::istringstream iss(ops_[pos_]);
      std::string s;
      std::string op, opand;
      iss >> op;
      int opint;
      if (op == "hlf") {
        iss >> opand;
        Hlf(opand);
      } else if (op == "tpl") {
        iss >> opand;
        Tpl(opand);
      } else if (op == "inc") {
        iss >> opand;
        Inc(opand);
      } else if (op == "jmp") {
        iss >> opint;
        Jmp(opint);
      } else if (op == "jie") {
        iss >> opand >> opint;
        Jie(opand, opint);
      } else if (op == "jio") {
        iss >> opand >> opint;
        Jio(opand, opint);
      }
    }
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Machine m;
    //Jio jio;
    //Jie jie;
    //Jmp jmp;
    //Inc inc;
    //Hlf hlf;
    //Tpl tpl;
    std::string s;

    for (; std::getline(ifs, s);) {
      m.ops_.push_back(s);
    }
    m.execute();
    fmt::print("{}\n", m.m["b"]);
  }
}