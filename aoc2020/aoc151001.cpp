#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>


int main(int argc, char **argv)
{
  std::string sa("1113222113");
  std::string sr;
  std::string sb;
  for (int i = 0; i < 50; ++i) {
    for (auto it = sa.begin(), end = sa.begin(); it != sa.end(); it = end) {
      char c = *it;
      end = std::find_if(it, sa.end(), [c](char e) { return e != c; });
      sb += std::to_string(end - it);
      sb += c;
    }
    sa = std::exchange(sb, "");
  }
  fmt::print("{}", sa.size());
}