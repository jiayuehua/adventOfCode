#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <fmt/format.h>
#include <string>
#include <unordered_map>
#include <limits>
#include <numeric>
#include <vector>
#include <functional>
#include <range/v3/all.hpp>
#include "matrix.h"
namespace views = ranges::views;
struct Bag
{
  std::string color_;
  std::vector<std::string> containcolors_;
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    int index = 0;
    std::vector<Bag> v;
    std::unordered_map<std::string, int> colorid;
    while (std::getline(ifs, s)) {
      std::istringstream iss(s);
      Bag bag;
      std::string ignore;
      std::string colorfirst;
      std::string colorsecond;
      iss >> colorfirst >> colorsecond >> ignore >> ignore;
      bag.color_ = colorfirst + colorsecond;
      if (!colorid.contains(bag.color_)) {
        colorid[bag.color_] = index;
        ++index;
      }
      while (iss >> ignore >> colorfirst >> colorsecond >> ignore) {
        bag.containcolors_.push_back(colorfirst + colorsecond);
        if (!colorid.contains(bag.containcolors_.back())) {
          colorid[bag.containcolors_.back()] = index;
          ++index;
        }
      }
      v.push_back(bag);
    }
    typedef Matrix<bool, std::logical_or<>, std::logical_and<>, false> Mat;
    Mat m(colorid.size(), colorid.size());
    for (auto &&bag : v) {
      for (auto &&subbag : bag.containcolors_) {
        if (subbag == "shinygold") {
          fmt::print("{}:{}={}\n", colorid[subbag], bag.color_, subbag);
        }
        m(colorid[subbag], colorid[bag.color_]) = true;
      }
    }
    Mat b(m.rowCount(), m.colCount());
    for (auto i : views::ints | views::take(m.rowCount())) {
      m(i, i) = true;
      b(i, i) = true;
    }
    Mat tmp = m.reverse();
    auto shinybagid = colorid["shinygold"];
    fmt::print("shinybagid:{}\n", shinybagid);
    auto mn = std::count(m.row(shinybagid).begin(), m.row(shinybagid).end(), true);
    fmt::print("{}\n", mn - 1);
    //Mat r = m * tmp;
    std::vector<Mat> vm(m.rowCount() - 1, tmp);
    auto r = std::reduce(std::execution::par_unseq, vm.begin(), vm.end(), m, std::multiplies{});
    auto n = std::count(r.row(shinybagid).begin(), r.row(shinybagid).end(), true);
    fmt::print("{}\n", n - 1);
  }
}