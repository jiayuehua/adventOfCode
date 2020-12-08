#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <range/v3/algorithm.hpp>

struct Distance
{
public:
  int speed_;
  int forwardtime_;
  int resttime_;
  int score_ = 0;
  int distance_ = 0;
  constexpr int operator()(int time) noexcept
  {
    int divide = time / (forwardtime_ + resttime_);
    distance_ = divide * speed_ * forwardtime_;
    int quote = time % (forwardtime_ + resttime_);
    distance_ += std::min(quote, forwardtime_) * speed_;
    return distance_;
  }
};
int main(int argc, char **argv)
{
  if (argc > 1) {

    std::ifstream ifs(argv[1]);
    std::string s;
    std::vector<Distance> v;
    Distance d;
    while (ifs >> s >> d.speed_ >> d.forwardtime_ >> d.resttime_) {
      fmt::print("{}-{}-{}\n", d.speed_, d.forwardtime_, d.resttime_);
      v.push_back(d);
    }
    for (int i = 1; i < 2504; ++i) {

      int md = 0;
      for (auto &&dis : v) {
        md = std::max(md, dis(i));
      }

      for (auto &&dis : v) {
        if (md == dis.distance_) {
          ++dis.score_;
        }
      }
    }
    int score = 0;
    for (auto &&dis : v) {
      score = std::max(score, dis.score_);
    }
    fmt::print("{}\n", score);
  }
}
