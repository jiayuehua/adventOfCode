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
namespace views = ranges::views;

using Iter = std::vector<int>::iterator;
template<int PlayerNum, int LastPoint>
class Marble
{
  std::array<std::int64_t, PlayerNum> playerScore_;
  std::list<int> marbles_;
  std::int64_t maxscore_ = 0;

public:
  auto maxScore() const
  {
    return maxscore_;
  }
  Marble() : playerScore_{},
             marbles_{ 0 }
  {
    auto it = marbles_.begin();
    for (int i = 1; i <= LastPoint; ++i) {
      if (i % 23) {
        ++it;
        if (it == marbles_.end()) {
          it = marbles_.begin();
        }
        ++it;
        it = marbles_.insert(it, i);
      } else {
        auto playNum = i % PlayerNum;
        playNum = (playNum) + (playNum == PlayerNum) * PlayerNum;
        auto worth = i;
        for (int j = 0; j < 7; ++j) {
          if (it == marbles_.begin()) {
            it = marbles_.end();
          }
          --it;
        }
        worth += *it;
        playerScore_[playNum - 1] += worth;
        it = marbles_.erase(it);
      }
    }
    maxscore_ = *ranges::max_element(playerScore_);
  }
};

int main(int argc, char **argv)
{
  {
    Marble<9, 25> m;
    std::cout << m.maxScore() << std::endl;
  }
  {
    Marble<10, 1618> mb;
    std::cout << mb.maxScore() << std::endl;
  }
  {
    Marble<13, 7999> mb;
    std::cout << mb.maxScore() << std::endl;
  }
  {
    Marble<17, 1104> mb;
    std::cout << mb.maxScore() << std::endl;
  }
  {
    Marble<441, 71032> mb;
    std::cout << mb.maxScore() << std::endl;
  }
  {
    Marble<441, 710320> mb;
    std::cout << mb.maxScore() << std::endl;
  }
  {
    Marble<441, 7103200> mb;
    std::cout << mb.maxScore() << std::endl;
  }
}
