#include <unordered_set>
#include <fstream>
#include <sstream>
#include <fmt/format.h>
#include <string>
#include <unordered_map>
#include <execution>
#include <tuple>
#include <functional>
#include <limits>
#include <numeric>
#include <range/v3/all.hpp>

#include "matrix.h"
namespace views = ranges::views;
struct Min
{
  template<class T>
  constexpr T operator()(T l, T r) const noexcept
  {
    return std::min(l, r);
  }
};
struct Plus
{
  template<class T>
  constexpr T operator()(T l, T r) const noexcept
  {
    if (l == std::numeric_limits<int>::max() || r == std::numeric_limits<int>::max()) {
      return std::numeric_limits<int>::max();
    }
    return std::plus{}(l, r);
  };
};
void foo()
{
  Matrix<int> ma(2, 2);
  Matrix<int> mb(2, 2);

  for (auto i : views::ints | views::take(2)) {
    for (auto j : views::ints | views::take(2)) {
      ma(i, j) = 1;
      mb(i, j) = 1;
    }
  }
  Matrix<int> mc = ma * mb;
  for (auto i : views::ints | views::take(2)) {
    for (auto j : views::ints | views::take(2)) {
      fmt::print("{},", mc(i, j));
    }
    fmt::print("\n");
  }
  fmt::print("\n");
}

void path()
{
  typedef Matrix<int, Min, Plus, std::numeric_limits<int>::max()> Mat;
  Mat ma(4, 4);
  Mat mb(4, 4);
  ma(0, 1) = 1;
  ma(1, 2) = 1;
  ma(2, 3) = 1;
  ma(1, 0) = 1;
  ma(2, 1) = 1;
  ma(3, 2) = 1;

  mb = ma;
  //min: (a00+b00),(a01+b10),(a02+b20)
  //min: (a00+b01),(a01+b11),(a02+b21)
  {//01
    //10
  }
  Mat mc = ma * mb;
  mc.clearslope();
  mc = mc * mb;
  mc.clearslope();
  for (auto i : views::ints | views::take(mc.colCount())) {
    for (auto j : views::ints | views::take(mc.colCount())) {
      fmt::print("{},", mc(i, j));
    }
    fmt::print("\n");
  }
  fmt::print("\n");
}

int main(int argc, char **argv)
{
  foo();
  path();
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    std::size_t index = 0;
    std::unordered_map<std::string, std::size_t> m;
    std::vector<std::tuple<std::string, std::string, int>> v;

    while (std::getline(ifs, s)) {
      std::istringstream iss(s);
      std::string citya, cityb, ig;
      int distance;
      iss >> citya >> ig >> cityb >> ig >> distance;
      v.push_back(std::make_tuple(citya, cityb, distance));
      if (!m.contains(citya)) {
        m[citya] = index;
        ++index;
      }
      if (!m.contains(cityb)) {
        m[cityb] = index;
        ++index;
      }
    }
    using Mat = Matrix<int, Plus, Min>;
    Mat graph(index, index);
    //for (auto i : views::ints | views::take(index)) {
    //graph(i, i) = std::numeric_limits<int>::max();
    //}
    for (auto i : views::ints | views::take(index)) {
      for (auto j : views::ints | views::take(index)) {
        graph(i, j) = std::numeric_limits<int>::max();
      }
    }
    Mat base = graph;
    ranges::for_each(v, [&m, &graph](auto &&tuple) {
      int i = m[std::get<0>(tuple)];
      int j = m[std::get<1>(tuple)];
      graph(i, j) = std::get<2>(tuple);
      graph(j, i) = std::get<2>(tuple);
    });
    for (auto i : views::ints | views::take(index - 2)) {
      base *= graph;
    }
  }
}