#include <complex>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fmt/format.h>
//#include <boost/config/warning_disable.hpp>
//#include <boost/spirit/home/x3.hpp>
//#include <range/v3/all.hpp>
#include <cstdint>
struct Sue
{
  int id_;
  std::map<std::string, int> gifts_;
  bool contains(const Sue &others) const
  {
    for (auto gift : others.gifts_) {
      if (auto i = gifts_.find(gift.first); i != gifts_.end() && (*i == gift)) {
      } else {
        return false;
      }
    }
    return true;
  }
  friend std::istream &operator>>(std::istream &is, Sue &sue)
  {
    std::string ignore;
    std::string k;
    int v;
    is >> ignore >> sue.id_;
    while (is >> ignore >> k >> v) {
      sue.gifts_[k] = v;
    }

    return is;
  }
};

int main(int argc, char **argv)
{
  if (argc > 2) {
    Sue suea;
    std::string k;
    int v;
    {
      std::ifstream ifs(argv[1]);
      while (ifs >> k >> v) {
        suea.gifts_[k] = v;
      }
    }

    std::ifstream ifs(argv[2]);
    std::string expr;
    while (std::getline(ifs, expr)) {
      Sue sueb;
      std::istringstream iss(expr);
      iss >> sueb;
      if (suea.contains(sueb)) {
        fmt::print("sueid:{}\n", sueb.id_);
        break;
      }
    }
  }
}
