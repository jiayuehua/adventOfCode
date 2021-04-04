#include <fstream>
#include <sstream>
#include <iostream>
#include <fmt/format.h>
#include <numeric>
#include <algorithm>
#include <set>
#include <chrono>
#include <map>
#include <range/v3/all.hpp>

#include <fmt/format.h>
#include <fmt/chrono.h>
#include <boost/icl/closed_interval.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval_map.hpp>
#include <date/tz.h>
namespace icl = boost::icl;
namespace views = ranges::views;
class Guards
{
  std::map<int, icl::interval_map<int, int>> guard_timevalset_;
  std::map<int, int> sleepTime_;

public:
  int count() const
  {
    int max = 0;
    int tvf = 0;
    int key;
    std::pair<int, int> sumcnt(0, 0);
    for (auto [k, v] : sleepTime_) {
      if (v > max) {
        max = v;
        key = k;
      }
    }
    max = 0;
    if (auto it = guard_timevalset_.find(key); it != guard_timevalset_.end()) {
      for (auto &&[k, v] : it->second) {
        if (v > max) {
          max = v;
          tvf = k.lower();
        }
      }
    }
    return key * tvf;
  }
  int mostfreSleep() const
  {
    int maxfs = 0;
    int key = 0;
    int time = 0;

    for (auto &&[k, v] : guard_timevalset_) {
      for (auto &&[kb, vb] : v) {
        if (vb > maxfs) {
          maxfs = vb;
          key = k;
          time = kb.lower();
        }
      }
    }

    return key * time;
  }
  friend std::istream &operator>>(std::istream &ifs, Guards &g)
  {
    std::string s;
    int curguardid = 0;
    int falls = 0;
    int wakesup = 0;
    while (std::getline(ifs, s)) {

      using namespace std;
      std::istringstream iss(s);
      {
        std::chrono::sys_time<std::chrono::minutes> t;
        iss >> date::parse("%F %H:%M", t);
        int n = t.time_since_epoch().count();
        std::string guard;
        iss >> guard;
        if (guard == "Guard") {
          iss >> curguardid;
        } else if (guard == "falls") {
          falls = t.time_since_epoch().count();
        } else {
          wakesup = t.time_since_epoch().count();
          icl::interval<int>::type p(falls, wakesup);
          g.sleepTime_[curguardid] += (wakesup - falls);
          if (auto i = g.guard_timevalset_.find(curguardid); i == g.guard_timevalset_.end()) {
            g.guard_timevalset_.insert(std::pair{ curguardid, std::pair{ p, 1 } });
          } else {
            i->second += std::pair{ p, 1 };
          }
        }
      };
    }
    return ifs;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    Guards g;
    ifs >> g;
    std::cout << g.mostfreSleep() << std::endl;
  }
}