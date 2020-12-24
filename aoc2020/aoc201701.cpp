#include <iostream>
#include <tuple>
#include <origin/math/matrix/matrix.hpp>
#include <utility>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace origin;
template <int N>
struct Conwaycube {
  matrix<int, 3>       ma;
  matrix<int, 3>       mb;
  matrix<int, 3>       mzero;
  int                  Origin = N / 2;
  friend std::ostream& operator<<(std::ostream& os, Conwaycube const& conway)
  {
    for (int i = conway.Origin - conway.NX / 2; i < conway.Origin + conway.NX / 2 + 1; ++i) {
      os << "=========   " << i << "," << conway.Origin - conway.NY / 2 << "   ===============\n" << std::endl;
      for (int j = conway.Origin - conway.NY / 2; j < conway.Origin + conway.NY / 2; ++j) {
        for (int k = conway.Origin - conway.NY / 2; k < conway.Origin + conway.NY / 2; ++k) {
          os << conway.ma(i, j, k);
          if (k != conway.Origin + conway.NY / 2 + 1) {
            os << ",";
          }
        }
        os << std::endl;
      }
      os << "==========$$$$$$$$$$$$$$$$$$$$===========\n" << std::endl;
    }
    return os;
  }
  friend std::istream& operator>>(std::istream& is, Conwaycube& conway)
  {
    std::string s;
    for (int j = 0; std::getline(is, s); ++j) {
      std::vector<int> v(s.size());
      conway.NY = v.size();

      std::transform(s.begin(), s.end(), v.begin(), [](char c) { return c == '#'; });
      for (int k = conway.Origin - conway.NY / 2; k < conway.Origin + conway.NY / 2; ++k) {
        conway.ma(conway.Origin, j + conway.Origin - conway.NY / 2, k) = v[k - (conway.Origin - conway.NY / 2)];
      }
    }
    return is;
  }
  Conwaycube() : ma(N, N, N), mb(N, N, N), mzero(N, N, N) {}
  int NY = 7;
  int NX = 1;
  int nc(int x, int y, int z)
  {
    int n = 0;
    for (int i = -1; i < 2; ++i) {
      for (int j = -1; j < 2; ++j) {
        for (int k = -1; k < 2; ++k) {
          n += ma(x + i, y + j, z + k);
        }
      }
    }
    n -= ma(x, y, z);
    return n;
  }
  void turn(int x, int y, int z)
  {
    int n = nc(x, y, z);
    if (ma(x, y, z)) {
      if (2 <= n && n < 4) {
        mb(x, y, z) = true;
      } else {
        mb(x, y, z) = false;
      }
    } else if (n == 3) {
      mb(x, y, z) = true;
    }
  }
  int validCount() { return std::count(ma.begin(), ma.end(), 1); }

  void transform()
  {
    NY += 2;
    for (int i = Origin - NX; i < Origin + NX + 1; ++i) {
      for (int j = Origin - NY / 2; j < Origin + NY / 2; ++j) {
        for (int k = Origin - NY / 2; k < Origin + NY / 2; ++k) {
          turn(i, j, k);
        }
      }
    }
    NX += 1;
    ma = std::exchange(mb, mzero);
  }
};

int main(int argc, char** argv)
{
  if (argc > 1) {
    std::ifstream  ifs(argv[1]);
    Conwaycube<22> c;
    ifs >> c;
    cout << c.validCount() << endl;
    for (int i = 0; i < 6; ++i) {
      c.transform();
      if (i == 0) {
        cout << c << endl;
      }
      cout << c.validCount() << endl;
    }
  }
}
