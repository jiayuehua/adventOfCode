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
#include <string_view>
#include <array>
#include <complex>
#include <boost/range.hpp>
#include <boost/algorithm/string.hpp>
#include "../aoc2020/matrix.h"
#include "../aoc2020/mypair.h"
namespace views = ranges::views;
namespace algo = boost::algorithm;
using Regs = std::array<int, 4>;
using namespace std::complex_literals;
auto turn_right(Mypair p)
{
  std::complex<int> c(p.y, -p.x);
  std::complex<int> m(0, -1);
  auto a = c * m;
  return Mypair(-a.imag(), a.real());
}
auto turn_left(Mypair p)
{
  std::complex<int> c(p.y, -p.x);
  std::complex<int> m(0, 1);
  auto a = c * m;
  return Mypair(-a.imag(), a.real());
}
class MineCart;
class Cart
{
  Mypair s_;
  Mypair d_;
  std::map<Mypair, char> *pturnright_;
  std::map<Mypair, char> *pturnleft_;

  int cnt_ = 0;
  FixedMatrix<char, 150> *pm_;
  FixedMatrix<char, 150> *pcartpos_;
  std::optional<Mypair> *pcollision_;
  char &cur()
  {
    return (*pm_)(s_.x, s_.y);
  }
  bool iscart() const
  {
    return (*pcartpos_)(s_.x, s_.y) == '#';
  }
  void setcart() const
  {
    (*pcartpos_)(s_.x, s_.y) = '#';
  }
  void clearcart() const
  {
    (*pcartpos_)(s_.x, s_.y) = '.';
  }
  void turn()
  {
    auto &turnright_ = *pturnright_;
    auto &turnleft_ = *pturnleft_;
    if (iscart()) {
      *pcollision_ = s_;
      return;
    }
    //std::cout << s_ << "," << d_ << std::endl;
    auto rightc = turnright_[d_];
    auto leftc = turnleft_[d_];
    if (cur() == rightc) {
      d_ = turn_right(d_);
    } else if (cur() == leftc) {
      d_ = turn_left(d_);
    } else if (cur() == '+') {
      if (cnt_ % 3 == 0) {
        d_ = turn_left(d_);
      }
      if (cnt_ % 3 == 2) {
        d_ = turn_right(d_);
      }
      ++cnt_;
    }
  }

public:
  auto getStartPoint() const
  {
    return s_;
  }
  friend std::ostream &operator<<(std::ostream &os, Cart const &c)
  {
    return os << c.s_;
  }
  Cart() = default;
  Cart(Mypair s, char c, FixedMatrix<char, 150> *pm, FixedMatrix<char, 150> *pcp, std::optional<Mypair> *po, std::map<Mypair, char> *pturnright, std::map<Mypair, char> *pturnleft) : s_(s), pm_(pm), pcartpos_(pcp), pcollision_(po), pturnright_(pturnright), pturnleft_(pturnleft)
  {
    std::map<char, Mypair> dms_;
    dms_['>'] = Mypair(0, 1);
    dms_['v'] = Mypair(1, 0);
    dms_['^'] = Mypair(-1, 0);
    dms_['<'] = Mypair(0, -1);
    d_ = dms_[c];
    //cur() = '#';
  }
  auto operator<=>(const Cart &c) const
  {
    return s_ <=> c.s_;
  }
  bool operator==(const Cart &c) const
  {
    return s_ == c.s_;
  }
  Cart &operator++()
  {
    //cur() = '.';
    clearcart();
    s_ += d_;
    turn();
    setcart();

    return *this;
  }
};
class MineCart
{
  FixedMatrix<char, 150> m_;
  FixedMatrix<char, 150> cartpos_;
  std::vector<Cart> vc_;
  std::optional<Mypair> collision_;

  std::map<Mypair, char> turnright_;
  std::map<Mypair, char> turnleft_;

public:
  MineCart()
  {
    turnright_[Mypair{ 0, 1 }] = '\\';
    turnleft_[Mypair{ 0, 1 }] = '/';

    turnright_[Mypair{ 1, 0 }] = '/';
    turnleft_[Mypair{ 1, 0 }] = '\\';

    turnright_[Mypair{ 0, -1 }] = '\\';
    turnleft_[Mypair{ 0, -1 }] = '/';
    turnright_[Mypair{ -1, 0 }] = '/';
    turnleft_[Mypair{ -1, 0 }] = '\\';
  }
  friend std::istream &operator>>(std::istream &is, MineCart &m)
  {
    ranges::getlines_view iv(is);
    int i = 0;
    ranges::for_each(iv, [&m, &i](std::string_view s) {
      ranges::copy(s, m.m_.row(i).begin());
      typedef std::vector<boost::iterator_range<std::string_view::iterator>> find_vector_type;
      for (auto c : { "<", ">", "^", "v" }) {
        find_vector_type FindVec;
        algo::find_all(FindVec, s, c);
        for (auto r : FindVec) {
          m.vc_.emplace_back(Mypair(i, r.begin() - s.begin()), c[0], &m.m_, &m.cartpos_, &m.collision_, &m.turnright_, &m.turnleft_);
        }
      }
      ++i;
    });
    ranges::sort(m.vc_);
    std::ostream_iterator<Cart> oi(std::cout, ",");
    ranges::copy(m.vc_, oi);
    std::cout << "size:" << m.vc_.size() << std::endl;
    ranges::fill(m.cartpos_.array(), '.');
    for (auto cart : m.vc_) {
      auto pos = cart.getStartPoint();
      m.cartpos_(pos.x, pos.y) = '#';
    }
    int sz = m.vc_.size();
    for (int i = 0; !m.collision_; ++i) {
      std::cout << "i:" << i << std::endl;
      auto &c = m.vc_[i % sz];
      ++c;
    }
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const MineCart &m)
  {
    for (int i = 120; i != 150; ++i) {
      for (int j = 120; j != 150; ++j) {
        os << m.m_(i, j);
      }
      os << std::endl;
    }
    return os;
  }
  Mypair collisionPoint()
  {
    return *collision_;
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    MineCart m;
    ifs >> m;
    std::cout << m.collisionPoint() << std::endl;
  }
}
