#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <cctype>
#include <boost/variant.hpp>
#include <unordered_map>
#include <range/v3/all.hpp>
#include <queue>
#include <optional>
#include <vector>
struct Output
{
};
struct Bot
{
  std::optional<int> low_;
  std::optional<int> high_;
  std::priority_queue<int> q_;
};
struct Factory
{
  std::vector<Bot> bots;
  int startid_;
  Factory() : bots(500) {}
  bool abletran_{ true };
  std::optional<int> validid_;
  int n = 0;
  int total = 1;

  void transfer(int i)
  {
    auto &bot = bots[i];
    auto big = bot.q_.top();
    bot.q_.pop();
    auto small = bot.q_.top();
    if (i == 49 || i == 159 || i == 115) {
      if (n != 3) {
        total *= small;
        if (n == 2) {
          fmt::print("total:{}\n", total);
        }
        ++n;
      } else {
        return;
      }
    }
    bot.q_.pop();
    std::tuple result{ small, big, i };
    //fmt::print("id:{},pair:{},{}\n", i, small, big);

    //if (small == 17 && big == 61) {
    //  if (!validid_) {
    //    *validid_ = std::get<2>(result);
    //    fmt::print("validid:{}", i);
    //  }
    //  return;
    //}
    if (bot.low_) {
      bots[*bot.low_].q_.push(small);
      if (bots[*bot.low_].q_.size() == 2) {
        //fmt::print("transfer low\n");
        transfer(*bot.low_);
      }
    }
    if (bot.high_) {
      bots[*bot.high_].q_.push(big);
      if (bots[*bot.high_].q_.size() == 2) {
        //fmt::print("transfer high\n");
        transfer(*bot.high_);
      }
    }
    //result;
  }
};

int main(int argc, char **argv)
{
  if (argc > 2) {
    std::ifstream init(argv[1]);
    int value, botid;
    int startbotid;
    Factory f;
    while (init >> value >> botid) {
      f.bots[botid].q_.push(value);
      if (f.bots[botid].q_.size() == 2) {
        f.startid_ = botid;
      }
    }
    std::ifstream tran(argv[2]);
    int low, high;

    std::string loutput;
    std::string houtput;
    std::string ignore;
    while (tran >> ignore >> botid
           >> ignore >> ignore >> ignore >> loutput >> low
           >> ignore >> ignore >> ignore >> houtput >> high) {
      if (loutput != "output") {
        f.bots[botid].low_ = low;
      }
      if (houtput != "output") {
        f.bots[botid].high_ = high;
      }
    }
    //for (; f.abletran_;) {
    f.transfer(f.startid_);
    //fmt::print("tranid:{}\n", id);
    //if (l == 17 && h == 61) {
    //  fmt::print("id:{}\n", id);
    //  break;
    //}
    //}
  }
}
