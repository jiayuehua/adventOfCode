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
#include "combinations_algo.h"

struct Item
{
  int cost_ = 0;
  int damage_ = 0;
  int armor_ = 0;
  Item &operator+=(const Item &other)
  {
    cost_ += other.cost_;
    damage_ += other.damage_;
    armor_ += other.armor_;
    return *this;
  }
  friend Item operator+(const Item &l, const Item &r)
  {
    Item tmp(l);

    return tmp += r;
  }
};
struct Role
{
private:
  int beheated(const Role &other) const
  {
    int diff = 1;
    if (other.damage_ > armor_) {
      diff = other.damage_ - armor_;
    }
    return diff;
  }

public:
  int points_ = 100;
  int damage_ = 0;
  int armor_ = 0;
  int rounds(const Role &other) const
  {
    return points_ / beheated(other);
  }
  auto operator<=>(const Role &other) const
  {
    return rounds(other) <=> other.rounds(*this);
  }
  void assign(const Item &other)
  {
    damage_ = other.damage_;
    armor_ = other.armor_;
  }
};

struct Game
{
  Role boss_{ 100, 8, 2 };
  Role player_{ 100 };
  std::array<Item, 5> weapons_{
    Item{ 8, 4 },
    Item{ 10, 5 },
    Item{ 25, 6 },
    Item{ 40, 7 },
    Item{ 74, 8 }
  };
  std::array<Item, 6> armor_{
    Item{},
    Item{ 13, 0, 1 },
    Item{ 31, 0, 2 },
    Item{ 53, 0, 3 },
    Item{ 75, 0, 4 },
    Item{ 102, 0, 5 }
  };

  int maxCost() const
  {
    std::array<Item, 16> rings_{
      Item{ 25, 1 },
      Item{ 50, 2 },
      Item{ 100, 3 },
      Item{ 20, 0, 1 },
      Item{ 40, 0, 2 },
      Item{ 80, 0, 3 }
    };

    int maxcost = std::numeric_limits<int>::min();


    for (auto w : weapons_) {
      for (auto a : armor_) {
        Role newplayer = this->player_;
        Item sum = w + a;
        newplayer.assign(sum);
        if (boss_ > newplayer) {
          maxcost = std::max(sum.cost_, maxcost);
        }

        auto f = [this, w, a, &maxcost](auto b, auto e) {
          Role newplayer = this->player_;
          Item sum = w + std::accumulate(b, e, a);
          newplayer.assign(sum);
          if (boss_ > newplayer) {
            maxcost = std::max(sum.cost_, maxcost);
          }
          return false;
        };
        for (auto mid = rings_.begin(); mid != rings_.end(); ++mid) {
          for_each_combination(rings_.begin(), mid, rings_.end(), f);
        }
        for_each_combination(rings_.begin(), rings_.end(), rings_.end(), f);
      }
    }
    return maxcost;
  }
};


int main(int argc, char **argv)
{
  Game g;
  fmt::print("maxLostCost:{}\n", g.maxCost());
}