#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <optional>
#include <cctype>
#include <map>
#include <vector>
#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include "matrix.h"
#include "mypair.h"
#include "combinations_algo.h"
namespace views = ranges::views;
struct Game
{
private:
  static inline constexpr int NX = 39;
  static inline constexpr int NY = 179;
  static inline constexpr int TreeSZ = 9;
  FixedMatrix<int, NX, NY> networks_;
  std::array<std::pair<Mypair, int>, TreeSZ> trees_;


public:
  using Network = FixedMatrix<int, NX, NY>;
  int shortestpath()
  {
    FixedMatrix<int, TreeSZ - 1, TreeSZ - 1> adjmatrix;
    std::vector<Mypair> adjp;
    for (int i = 0; i < TreeSZ - 2; ++i) {
      for (int j = i + 1; j < TreeSZ - 1; ++j) {
        adjp.push_back({ i, j });
      }
    }
    std::for_each(std::execution::par_unseq, adjp.begin(), adjp.end(), [this, &adjmatrix](Mypair p) {
      adjmatrix(p.x, p.y) = this->shortestpath(this->trees_[p.x].first, this->trees_[p.y].first);
      adjmatrix(p.y, p.x) = adjmatrix(p.x, p.y);
    });

    int totallen = std::numeric_limits<int>::max();
    auto f = [&totallen, this, &adjmatrix](auto b, auto e) {
      auto len = 0;
      --b;
      for (; b != e; ++b) {
        if (auto sl = adjmatrix(b->second, (b + 1)->second); sl) {
          len += sl;
        } else {
          int nl = shortestpath(b->first, (b + 1)->first);
          adjmatrix(b->second, (b + 1)->second) = nl;
          adjmatrix((b + 1)->second, b->second) = nl;
          len += nl;
        }
      }
      totallen = std::min(len, totallen);
      return false;
    };
    for_each_reversible_permutation(trees_.begin() + 1, trees_.end() - 1, trees_.end() - 1, f);
    return totallen;
  }
  friend std::istream &operator>>(std::istream &is, Game &g)
  {
    std::string str;

    for (int i = 0; std::getline(is, str); ++i) {
      auto v = str | views::transform([](char c) { return c != '#'; });
      for (auto k = 0; k < str.size(); ++k) {
        std::copy(v.begin(), v.end(), g.networks_.row(i).begin());
      }

      auto ids = views::all(str) | views::enumerate | views::filter([](auto pair) {
        auto id = std::isdigit(std::get<1>(pair));
        return static_cast<bool>(id);
      }) | views::transform([i](auto pair) {
        Mypair p(i, std::get<0>(pair));
        return std::make_pair(p, std::get<1>(pair) - '0');
      }) | views::common;
      for (auto pair : ids) {
        g.trees_[pair.second] = pair;
      }
    }

    g.trees_.back() = g.trees_.front();
    return is;
  }
  std::array<Mypair, 4> step_ = {
    Mypair{ 0, -1 },
    Mypair{ 0, 1 },
    Mypair{ -1, 0 },
    Mypair{ 1, 0 }
  };
  void setbrick(Network &network, std::vector<Mypair> &v)
  {
    for (auto pos : v) {
      network(pos.x, pos.y) = 0;
    }
  }
  void setbrick(Network &n, Mypair pos)
  {
    n(pos.x, pos.y) = 0;
  }
  bool isroad(Network const &n, Mypair p) const
  {
    return n(p.x, p.y);
  }

  int shortestpath(Mypair pos, Mypair dst)
  {
    int len = 1;
    auto networksB = networks_;
    std::vector<Mypair> curr;
    curr.push_back(pos);
    setbrick(networksB, pos);
    for (int j = 0;; ++j) {
      std::vector<Mypair> adjs;
      for (auto cur : curr) {
        for (int i = 0; i < 4; ++i) {
          if (isroad(networksB, cur + step_[i])) {
            if (cur + step_[i] == dst) {
              return j + 1;
            }
            adjs.push_back(cur + step_[i]);
          }
        }
      }
      curr = adjs;
      setbrick(networksB, curr);
    }
    return std::numeric_limits<int>::max();
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {
    Game g;
    std::ifstream ifs(argv[1]);
    ifs >> g;
    auto r = g.shortestpath();
    std::cout << r << std::endl;
  }
}