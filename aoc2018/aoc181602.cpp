#include <fstream>
#include <set>
#include <map>
#include <iostream>
#include <vector>
#include <range/v3/all.hpp>
#include <array>
#include <optional>
#include <fmt/format.h>
#include <fmt/ranges.h>
namespace views = ranges::views;
using Regs = std::array<int, 4>;
std::optional<Regs> addr(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (int i = 1; i < 4; ++i) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = reg[code[1]] + reg[code[2]];
  return rb;
}
std::optional<Regs> addi(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 1, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = reg[code[1]] + code[2];
  return rb;
}
std::optional<Regs> mulr(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (int i = 1; i < 4; ++i) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = reg[code[1]] * reg[code[2]];
  return rb;
}
std::optional<Regs> muli(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 1, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = reg[code[1]] * code[2];
  return rb;
}

std::optional<Regs> banr(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (int i = 1; i < 4; ++i) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = reg[code[1]] & reg[code[2]];
  return rb;
}
std::optional<Regs> bani(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 1, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = reg[code[1]] & code[2];
  return rb;
}
std::optional<Regs> borr(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (int i = 1; i < 4; ++i) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = reg[code[1]] | reg[code[2]];
  return rb;
}
std::optional<Regs> bori(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 1, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = reg[code[1]] | code[2];
  return rb;
}
std::optional<Regs> setr(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 1, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = reg[code[1]];
  return rb;
}

std::optional<Regs> seti(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = code[1];
  return rb;
}
std::optional<Regs> gtir(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 2, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = code[1] > rb[code[2]];
  return rb;
}
std::optional<Regs> gtrr(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 1, 2, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = rb[code[1]] > rb[code[2]];
  return rb;
}
std::optional<Regs> gtri(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 1, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = rb[code[1]] > code[2];
  return rb;
}
std::optional<Regs> eqir(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 2, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = code[1] == rb[code[2]];
  return rb;
}
std::optional<Regs> eqrr(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 1, 2, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = rb[code[1]] == rb[code[2]];
  return rb;
}
std::optional<Regs> eqri(const Regs &code, const Regs &reg)
{
  auto rb = reg;
  for (auto i : { 1, 3 }) {
    if (code[i] > 3 || code[i] < 0) {
      return std::nullopt;
    }
  }
  rb[code[3]] = rb[code[1]] == code[2];
  return rb;
}
typedef std::optional<Regs> (*Operation)(const Regs &code, const Regs &reg);
Operation ops[] = { addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr };
auto f(const std::vector<int> &vec)
{
  std::map<int, std::set<int>> m;
  auto v = vec | views::chunk(4) | views::chunk(3);
  ranges::for_each(v, [&m](auto input) {
    Regs code;
    Regs expected;
    Regs reg;
    ranges::copy(input[0], reg.begin());
    ranges::copy(input[1], code.begin());
    ranges::copy(input[2], expected.begin());
    int n = 0;
    Operation opa{ nullptr };
    int opcode = 0;
    for (int i = 0; auto op : ops) {
      auto ir = op(code, reg);
      if (ir && (*ir == expected)) {
        opa = op;
        opcode = code[0];
        m[opcode].insert(i);
      }
      ++i;
    }
  });
  std::map<int, int> opCodeFuncId;
  for (int i = 0; i < 16; ++i) {
    for (auto &[k, v] : m) {
      if (v.size() == 1) {
        auto one = *v.begin();
        opCodeFuncId[k] = one;
        for (auto &[k, vb] : m) {
          vb.erase(one);
        }
      }
    }
  }
  return opCodeFuncId;
}
int run(const std::vector<int> &vec, const std::map<int, int> &m)
{
  auto v = vec | views::chunk(4);
  //int n
  Regs reg{};
  ranges::for_each(v, [&m, &reg](auto input) {
    Regs code;
    ranges::copy(input, code.begin());
    int opcode = code[0];
    Operation op{ ops[m.find(opcode)->second] };
    if (auto opt = op(code, reg); opt) {
      reg = *opt;
    }
  });
  return reg[0];
}
int main(int argc, char **argv)
{
  if (argc > 2) {
    std::ifstream ifs(argv[1]);
    ranges::istream_view<int> iv(ifs);
    auto v = iv | ranges::to<std::vector>;
    auto opFunc = f(v);
    std::ifstream ifsb(argv[2]);
    ranges::istream_view<int> ivb(ifsb);
    auto vb = ivb | ranges::to<std::vector>;
    auto r = run(vb, opFunc);
    fmt::print("r0:{}\n", r);
  }
}
