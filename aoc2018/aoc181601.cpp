#include <complex>
#include <exception>
#include <fstream>
#include <set>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <iterator>
#include <list>
#include <array>
#include <cstdint>
#include <optional>
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
int f(const std::vector<int> &vec)
{
  typedef std::optional<Regs> (*Operation)(const Regs &code, const Regs &reg);

  auto v = vec | views::chunk(4) | views::chunk(3) | views::transform([](auto input) {
    Operation ops[] = { addr, addi, mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr };
    //Regs reg;
    Regs code;
    Regs expected;
    Regs reg;
    ranges::copy(input[0], reg.begin());
    ranges::copy(input[1], code.begin());
    ranges::copy(input[2], expected.begin());
    //Regs reg = input[0] | ranges::to<std::array<int, 4>>;
    int n = 0;
    for (auto op : ops) {
      auto ir = op(code, reg);
      n += (ir && (*ir == expected));
    }
    return n >= 3;
  });
  return ranges::count(v, true);
}
int main(int argc, char **argv)
{
  std::ifstream ifs(argv[1]);
  ranges::istream_view<int> iv(ifs);
  auto v = iv | ranges::to<std::vector>;
  std::cout << f(v) << std::endl;
}
