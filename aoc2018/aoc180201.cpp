#include <fstream>
#include <iostream>
#include <fmt/format.h>
#include <cstdint>
#include <numeric>
#include <algorithm>


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::istream_iterator<std::string> b(ifs);
    std::istream_iterator<std::string> e;
    int twocnt = 0;
    int threecnt = 0;
    std::for_each(b, e, [&twocnt, &threecnt](const std::string &s) {
      std::vector<int> charcnt(256);
      std::cout << s << std::endl;
      for (auto c : s) {
        ++charcnt[c];
      }
      twocnt += (std::find(charcnt.begin(), charcnt.end(), 2) != charcnt.end());
      threecnt += (std::find(charcnt.begin(), charcnt.end(), 3) != charcnt.end());
    });
    std::cout << twocnt * threecnt << std::endl;
  }
}