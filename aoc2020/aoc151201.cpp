
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <boost/variant.hpp>
#include <unordered_map>
#include <range/v3/all.hpp>
struct Valid
{
  std::pair<int, int> ca;
  std::pair<int, int> cb;
  bool operator()(int n) const
  {
    return (n >= ca.first && n <= ca.second) || (

             (n >= cb.first && n <= cb.second));
  }
};
struct Scan
{
  std::vector<Valid> v_;
  bool operator()(int n) const
  {
    return ranges::any_of(v_, [n](auto v) { return v(n); });
  }
};
int main(int argc, char **argv)
{
  if (argc > 2) {
    std::ifstream ifs(argv[1]);
    std::string s;
    int drop2lines = 10;
    Scan scan;
    while (std::getline(ifs, s) && drop2lines) {
      --drop2lines;
      std::istringstream iss(s);
      std::string ignore;
      int caf, cas, cbf, cbs;
      iss >> ignore >> ignore >> caf >> cas >> ignore >> cbf >> cbs;
      cas = -cas;
      cbs = -cbs;
      scan.v_.push_back({ { caf, cas }, { cbf, cbs } });

      std::cout << caf << " ";
      std::cout << cas << " ";
      std::cout << cbf << " ";
      std::cout << cbs << "\n";
    }
    while (std::getline(ifs, s)) {
      std::istringstream iss(s);
      std::string ignore;
      int caf, cas, cbf, cbs;
      iss >> ignore >> caf >> cas >> ignore >> cbf >> cbs;
      cas = -cas;
      cbs = -cbs;

      std::cout << caf << " ";
      std::cout << cas << " ";
      std::cout << cbf << " ";
      std::cout << cbs << "\n";
    }
    {

      std::ifstream ifs(argv[2]);
      int n;
      int64_t sum = 0;
      while (ifs >> n) {

        if (!scan(n)) {
          sum += n;
          std::cout << "$$$" << n << std::endl;

        } else {
          std::cout << n << std::endl;
        }
      }
      std::cout << sum << std::endl;
    }
  }
}