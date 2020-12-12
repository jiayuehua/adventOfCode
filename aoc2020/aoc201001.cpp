#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <numeric>
#include <iomanip>
#include <range/v3/all.hpp>


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    int i;
    std::vector<int> v;
    v.reserve(500);
    v.push_back(0);
    while (ifs >> i) {
      v.push_back(i);
    }
    fmt::print("{}\n", v.size());
    std::vector<int> vd(v);
    ranges::sort(v);
    ranges::adjacent_difference(v, vd.begin());
    vd.push_back(3);

    int onescount = ranges::count(vd, 1);
    fmt::print("{}\n", onescount);
    int max = ranges::max(vd);
    fmt::print("{}\n", max);

    int threescount = ranges::count(vd, 3);
    fmt::print("{}\n", threescount);
    fmt::print("{}\n", onescount * threescount);
  }
}