#include <fstream>
#include <iostream>
#include <fmt/format.h>
#include <numeric>
#include <algorithm>
#include <set>
using gint = std::int64_t;
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::istream_iterator<int> b(ifs);
    std::istream_iterator<int> e;
    std::set<int> his;
    std::vector<int> v(b, e);
    int s = 0;
    for (auto i = v.begin();; ++i) {
      if (i == v.end()) {
        i = v.begin();
      }
      s += *i;
      auto [it, v] = his.insert(s);
      if (!v) {
        fmt::print("{}\n", *it);
        break;
      }
    }
  }
}