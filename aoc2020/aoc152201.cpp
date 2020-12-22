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
stuct Boss
{
  int points_ = 51;
  int damage_ = 9;
  int armor_ = 0;
  bool lose_ = false;

protected:
  int beat(const Boss &other) const
  {
    int diff = 1;
    if (other.damage_ > armor_) {
      diff = other.damage_ - armor_;
    }
    return diff;
  }
  bool bebeated(int n)
  {
    if (points_ < n) {
      lose_ = true;
      return false;
    }
    points -= n;
    return true;
  }
  bool lose() const noexcept
  {
    return lose_;
  }
};

struct Player : Boss
{
  static constexpr inline int Initmana_ = 500;
  int mana_ = 500;
  int shieldturn_ = 0;
  int poisonturn_ = 0;
  int rechargeturn_ = 0;
  int spentmana() const
  {
    return 0;
  }
  bool MagicMissile(Boss &boss)
  {
    if (mana_ <= 53) {
      return false;
    } else {
      boss.beated(4);
      mana_ -= 53;
      return true;
    }
  }
  bool Drain(Boss &boss)
  {
    if (mana_ <= 73) {
      return false;
    } else {
      boss.beated(2);
      points_ += 2;
      mana_ -= 73;
      return true;
    }
  }
  bool Shield(Boss &boss)
  {
    if (mana_ <= 113 || shieldturn_) {
      return false;
    } else {
      shieldturn_ = 6;
      return true;
    }
  }
  bool Poison(Boss &boss)
  {
    if (mana_ <= 173 || poisonturn_) {
      return false;
    } else {
      poisonturn_ = 6;
      return true;
    }
  }
  bool Recharge(Boss &boss)
  {
    if (mana_ <= 229 || rechargeturn_) {
      return false;
    } else {
      rechargeturn_ = 5;
      return true;
    }
  }
  void shieldeffect()
  {
    if (shieldturn_) {
      --shieldturn_;
      armor_ += 7;
    }
  }
  void poisoneffect(Boss &boss)
  {
    if (poisonturn_) {
      --poisonturn_;
      boss.bebeated(3);
    }
  }
  void rechargeeffect()
  {
    if (rechargeturn_) {
      --rechargeturn_;
      mana_ += 101;
    }
  }
  typedef void (Player::*BeatBoss)(Boss &);
  BeatBoss[] = {
    &Player::MagicMissile,
    &Player::Drain,
    &Player::Shield,
    &Player::Poison,
    &Player::Recharge
  };

public:
  void effect(Boss &boss)
  {
    shieldeffect();
    poisoneffect(boss);
    rechargeeffect();
  }
  bool beat(Boss &other, int i, int &MinMana)
  {
    bool conbeat = true;
    bool r = this->*(BeatBoss[i])(other);
    if (r && other.lose()) {
      MinMana = std::min(MinMana, spentmana());
      conbeat = false;
    }
    if (!r) {
      conbeat = false;
    }
    return conteat;
  }
  Player() : Boss{ 50, 0, 0 } {}
};

struct Game
{
  Boss boss_;
  Player player_;
  int MinManaSpend_ = 1000000000;
  int timestamp_ = 0;
  void heartBeat()
  {
    if (timestamp_ % 2 == 0) {
      Game tmp = *this;
      int failedtimes = 0;
      for (int i = 0; i < 5; ++i) {
        *this = tmp;
        bool canbeat = player_.beat(boss_, i, MiniManaSpend_);
        player_.effect(boss_);
        ++timestamp_;
        failedtimes += !canbeat;
        if (canbeat) {
          heartBeat();
        }
      }
    } else {
      player_.effect(boss_);
      boss.beat(player_);
      ++timestamp;
      heartBeat();
    }
  }
};

int main(int argc, char **argv)
{
  Game g;
  fmt::print("maxLostCost:{}\n", g.maxCost());
}