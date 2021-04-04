#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <optional>
#include <cctype>
#include <map>
#include <algorithm>
#include <vector>
#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <boost/dynamic_bitset.hpp>
#include <complex>
using namespace std::literals::complex_literals;
#include "../aoc2020/matrix.h"
#include "../aoc2020/mypair.h"

namespace views = ranges::views;

template<int N>
concept Module2 = N % 2 == 0;

template<int N>
auto rotateSquare(const FixedMatrix<bool, N, N> &m)
{
  FixedMatrix<bool, N, N> r;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      r(j, N - 1 - i) = m(i, j);
    }
  }
  return r;
}
template<int N>
auto flipSquare(const FixedMatrix<bool, N, N> &m)
{
  FixedMatrix<bool, N, N> r;
  for (int i = 0; i < N; ++i) {
    std::reverse_copy(m.row(i).begin(), m.row(i).end(), r.row(i));
  }
  return r;
}

template<int N>
auto rotateflipSquare(const FixedMatrix<bool, N, N> &m)
{
  std::array<FixedMatrix<bool, N, N>, 8> r;

  r[0] = m;
  for (int i = 0; i < 3; ++i) {
    r[i + 1] = rotateSquare(r[i]);
  }

  r[4] = flipSquare(m);
  for (int i = 4; i < 7; ++i) {
    r[i + 1] = rotateSquare(r[i]);
  }
  return r;
}


class Game
{
  std::map<FixedMatrix<bool, 2>, FixedMatrix<bool, 3>> ruleB_;
  std::map<FixedMatrix<bool, 3>, FixedMatrix<bool, 4>> ruleC_;
  FixedMatrix<bool, 3> mat_;

  template<int N>
  void insert(std::map<FixedMatrix<bool, N>, FixedMatrix<bool, N + 1>> &m, FixedMatrix<bool, N> const &k, const FixedMatrix<bool, N + 1> &v)
  {
    //std::cout << N << "v" << std::endl;
    //std::cout << v << std::endl;
    auto r = rotateflipSquare(k);
    for (auto square : r) {
      //std::cout << square << std::endl;
      m[square] = v;
    }
  }
  //Matrix r;
  template<int M, int N>
  FixedMatrix<bool, M> subMatrix(const FixedMatrix<bool, N> &input, int m, int n)
  {
    FixedMatrix<bool, M> r;
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < M; ++j) {
        r(i, j) = input(m + i, n + j);
      }
    }
    return r;
  }
  template<int N, int M>
  void assignsubMatrix(FixedMatrix<bool, N> &input, int m, int n, const FixedMatrix<bool, M> &r)
  {
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < M; ++j) {
        input(m + i, n + j) = r(i, j);
      }
    }
  }


public:
  void outputrules() const
  {
    std::cout << "rulesB:\n";
    for (auto &[k, v] : ruleB_) {
      std::cout << k << std::endl;
      std::cout << v << std::endl;
      std::cout << "---------\n";
    }
    std::cout << "rulesC:\n";
    for (auto &[k, v] : ruleC_) {
      std::cout << k << std::endl;
      std::cout << v << std::endl;
      std::cout << "---------\n";
    }
  }

  template<int N>
  requires(Module2<N>)
    FixedMatrix<bool, N + N / 2> transform(const FixedMatrix<bool, N> &input)
  {

    //std::cout << "transform" << N << std::endl;
    FixedMatrix<bool, N + N / 2> r;
    for (int i = 0; i < N; i += 2) {
      for (int j = 0; j < N; j += 2) {
        FixedMatrix<bool, 2, 2> m = subMatrix<2>(input, i, j);
        //std::cout << "--" << i << "," << j << "-input--------" << std::endl;

        //std::cout << m << std::endl;
        //std::cout << "--" << i * 3 / 2 << "," << j * 3 / 2 << "-output--------" << std::endl;
        //std::cout << ruleB_[m] << std::endl;
        assignsubMatrix(r, i * 3 / 2, j * 3 / 2, ruleB_[m]);
      }
    }
    return r;
  }
  template<int N>
  requires((N % 3) == 0 || Module2<N>)
    FixedMatrix<bool, N + N / 3> transform(const FixedMatrix<bool, N> &input)
  {
    //std::cout << "transform" << N << std::endl;
    FixedMatrix<bool, N + N / 3> r;
    for (int i = 0; i < N; i += 3) {
      for (int j = 0; j < N; j += 3) {
        FixedMatrix<bool, 3, 3> m = subMatrix<3>(input, i, j);
        //std::cout << "--" << i << "," << j << "-input--------" << std::endl;
        //std::cout << m << std::endl;
        //std::cout << "--" << i * 4 / 3 << "," << j * 4 / 3 << "-output--------" << std::endl;
        //std::cout << ruleC_[m] << std::endl;
        assignsubMatrix(r, i * 4 / 3, j * 4 / 3, ruleC_[m]);
      }
    }
    return r;
  }
  Game()
  {
  }
  friend std::istream &operator>>(std::istream &is, Game &g)
  {
    std::string k, v;
    while (is >> k >> v) {
      if (k.size() == 5) {
        FixedMatrix<bool, 2> matk;
        auto mk = k | views::split('/') | views::transform([](auto row) {
          return row | views::transform([](char c) { return c == '#'; });
        });
        {
          auto id = 0;
          for (auto i = mk.begin(); i != mk.end(); ++i, ++id) {
            auto jd = 0;
            for (auto j = (*i).begin(); j != (*i).end(); ++j, ++jd) {
              matk(id, jd) = *j;
            }
          }
        }
        FixedMatrix<bool, 3> matv;
        auto mv = v | views::split('/') | views::transform([](auto row) {
          return row | views::transform([](char c) { return c == '#'; });
        });
        auto id = 0;
        for (auto i = mv.begin(); i != mv.end(); ++i, ++id) {
          auto jd = 0;
          for (auto j = (*i).begin(); j != (*i).end(); ++j, ++jd) {
            int n = *j;
            matv(id, jd) = n;
          }
        }
        g.insert(g.ruleB_, matk, matv);
      } else {
        FixedMatrix<bool, 3> matk;
        auto mk = k | views::split('/') | views::transform([](auto row) {
          return row | views::transform([](char c) { return c == '#'; });
        });
        {
          auto id = 0;
          for (auto i = mk.begin(); i != mk.end(); ++i, ++id) {
            auto jd = 0;
            for (auto j = (*i).begin(); j != (*i).end(); ++j, ++jd) {
              matk(id, jd) = *j;
            }
          }
        }
        FixedMatrix<bool, 4> matv;
        auto mv = v | views::split('/') | views::transform([](auto row) {
          return row | views::transform([](char c) { return c == '#'; });
        });
        auto id = 0;
        for (auto i = mv.begin(); i != mv.end(); ++i, ++id) {
          auto jd = 0;
          for (auto j = (*i).begin(); j != (*i).end(); ++j, ++jd) {
            int n = *j;
            matv(id, jd) = n;
          }
        }
        g.insert(g.ruleC_, matk, matv);
      }
    }

    return is;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    Game g;
    std::ifstream iss(argv[1]);
    iss >> g;
    //g.outputrules();
    //return 0;
    FixedMatrix<bool, 3> mat_;
    mat_(0, 1) = true;
    mat_(1, 2) = true;
    mat_(2, 0) = true;
    mat_(2, 1) = true;
    mat_(2, 2) = true;
    auto A1 = g.transform(mat_);
    auto A2 = g.transform(A1);
    auto A3 = g.transform(A2);
    auto A4 = g.transform(A3);
    auto A5 = g.transform(A4);
    std::cout << std::count(std::begin(A5.array()), std::end(A5.array()), 1) << std::endl;
    auto A6 = g.transform(A5);
    auto A7 = g.transform(A6);
    auto A8 = g.transform(A7);
    auto A9 = g.transform(A8);
    auto A10 = g.transform(A9);
    auto A11 = g.transform(A10);
    auto A12 = g.transform(A11);
    auto A13 = g.transform(A12);
    auto A14 = g.transform(A13);
    auto A15 = g.transform(A14);
    auto A16 = g.transform(A15);
    auto A17 = g.transform(A16);
    auto A18 = g.transform(A17);
    std::cout << std::count(std::begin(A18.array()), std::end(A18.array()), 1) << std::endl;
  }
}
