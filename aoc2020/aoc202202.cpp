#include <fstream>
#include <sstream>
#include <iostream>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <deque>
#include <algorithm>
#include <iterator>
#include <set>
#include <range/v3/view.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/numeric.hpp>
namespace views = ranges::views;
struct Game
{
  std::deque<int> qa_{ 2, 31, 14, 45, 33, 18, 29, 36, 44, 47, 38, 6, 9, 5, 48, 17, 50, 41, 4, 21, 42, 23, 25, 28, 3 };
  std::deque<int> qb_{ 26, 16, 27, 12, 49, 32, 19, 46, 37, 15, 10, 30, 11, 24, 1, 40, 7, 8, 43, 34, 20, 35, 22, 39, 13 };
  bool round(std::deque<int> &qa, std::deque<int> &qb)
  {
    int count = 0;
    auto qab = qa.begin(), qae = qa.end(), qbb = qb.begin(), qbe = qb.end();
    std::set<std::deque<int>> qaprevrounds;
    std::set<std::deque<int>> qbprevrounds;

    while (qab != qae && qbb != qbe) {
      ++count;
      if (qaprevrounds.contains(qa) && qbprevrounds.contains(qb)) {
        return false;
      } else {
        qaprevrounds.insert(qa);
        qbprevrounds.insert(qb);
      }
      auto qarightlen = (qae - qab) - 1;
      auto qbrightlen = (qbe - qbb) - 1;

      auto a = qa.front();
      auto b = qb.front();
      qa.pop_front();
      qb.pop_front();
      bool rwin = false;
      if (a <= (qarightlen) && b <= (qbrightlen)) {
        std::deque nqa(qa.begin(), qa.begin() + a);
        std::deque nqb(qb.begin(), qb.begin() + b);
        rwin = round(nqa, nqb);
      } else {
        rwin = a < b;
      }
      if (rwin) {
        qb.push_back(b);
        qb.push_back(a);
      } else {
        qa.push_back(a);
        qa.push_back(b);
      }


      qab = qa.begin();
      qae = qa.end();
      qbb = qb.begin();
      qbe = qb.end();
    }
    return (qae - qab) < (qbe - qbb);
  }
  bool rounds()
  {
    return round(qa_, qb_);
  }
  int score()
  {
    try {
      auto r = rounds();
      if (!r) {
        int n = qa_.size();
        auto view = views::ints(1, n + 1) | views::reverse | views::common;
        return ranges::inner_product(view, qa_, 0);
      } else {
        int n = qb_.size();
        auto view = views::ints(1, n + 1) | views::reverse | views::common;
        return ranges::inner_product(view, qb_, 0);
      }

    } catch (...) {
      int n = qa_.size();
      auto view = views::ints(1, n + 1) | views::reverse | views::common;
      return ranges::inner_product(view, qa_, 0);
    }
  }
};


int main(int argc, char **argv)
{
  Game g;
  fmt::print("{}\n", g.score());
}