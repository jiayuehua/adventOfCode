#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    std::string sb;
    int n = 0;
    while (ifs >> s) {
      std::istringstream iss(s);
      iss >> std::quoted(sb);
      n += (iss.str().size() - sb.size());
    }
    fmt::print("{}\n", n);
  }
}