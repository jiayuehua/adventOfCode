#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <range/v3/all.hpp>
#include "matrix.h"
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

  bool operator()(int col, int n) const
  {
    auto departfield = v_[col];
    return departfield(n);
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
      std::string s;
      std::vector<std::vector<int>> fakeMatrix;
      while (std::getline(ifs, s)) {
        std::istringstream iss(s);
        int n;
        int64_t sum = 0;
        std::vector<int> row;
        bool valid = true;
        while (iss >> n) {

          if (!scan(n)) {
            valid = false;
            break;
          } else {
            row.push_back(n);
          }
        }
        if (valid) {
          fakeMatrix.push_back(row);
        }
        //std::cout << sum << std::endl;
      }
      Matrix<int> m(fakeMatrix.size(), fakeMatrix[0].size());
      for (auto i = 0; i < fakeMatrix.size(); ++i) {
        ranges::copy(fakeMatrix[i], m.row(i).begin());
      }
      //std::cout << m << std::endl;
      int64_t sum = 1;
      int total = 0;
      //return 0;
      std::vector<int> a(m.colCount());
      std::vector<std::vector<int>> departcols(m.colCount());


      for (int j = 0; j < departcols.size(); ++j) {

        for (auto i = 0; i < m.colCount(); ++i) {
          auto c = m.column(i);
          if (std::all_of(c.begin(), c.end(), [&scan, j](auto value) {
                return scan(j, value);
              })) {
            //sum *= m(0, i);
            departcols[j].push_back(i);
            ++a[j];
            ++total;
            //break;
          }
        }
      }
      std::vector<int> ra(departcols[0]);
      std::vector<int> rb;

      for (auto r : departcols) {
        //std::set_intersection(r.begin(), r.end(), ra.begin(), ra.end(), std::back_inserter(rb));
        //ra = rb;
        //rb.clear();
        for (auto i : r) {
          std::cout << i << ',';
        }

        std::cout << std::endl;
      }
      for (auto i : { 2, 3, 6, 7, 9, 11 }) {
        std::cout << i << ' ';
        sum *= m(0, i);
      }
      std::cout << '\n';
      std::cout << "total"
                << "," << sum << std::endl;
      std::cout << std::endl;
      ;
    }
  }
}