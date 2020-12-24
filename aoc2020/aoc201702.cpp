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
  matrix<int, 4>              ma;
  matrix<int, 4>              mb;
  matrix<int, 4>              mzero;
  static inline constexpr int Origin = N / 2;

  friend std::istream& operator>>(std::istream& is, Conwaycube& conway)
  {
    std::string s;
    for (int j = 0; std::getline(is, s); ++j) {
      std::vector<int> v(s.size());
      conway.NY = v.size() + (v.size() % 2);
      conway.NX = v.size() + (v.size() % 2);

      std::transform(s.begin(), s.end(), v.begin(), [](char c) { return c == '#'; });
      for (int k = conway.Origin - conway.NY / 2; k < conway.Origin + conway.NY / 2 + 1; ++k) {
        conway.ma(conway.Origin, conway.Origin, j + conway.Origin - conway.NY / 2, k) =
            v[k - (conway.Origin - conway.NY / 2)];
      }
    }
    return is;
  }
  Conwaycube() : ma(N, N, N, N), mb(N, N, N, N), mzero(N, N, N, N) {}
  int NY = 7;
  int NX = 2;
  int nc(int x, int y, int z, int w)
  {
    int n = 0;
    for (int i = -1; i < 2; ++i) {
      for (int j = -1; j < 2; ++j) {
        for (int k = -1; k < 2; ++k) {
          for (int l = -1; l < 2; ++l) {
            n += ma(x + i, y + j, z + k, w + l);
          }
        }
      }
    }
    n -= ma(x, y, z, w);
    return n;
  }
  void turn(int x, int y, int z, int w)
  {
    int n = nc(x, y, z, w);
    if (ma(x, y, z, w)) {
      if ((2 <= n) && (n < 4)) {
        mb(x, y, z, w) = true;
      } else {
        mb(x, y, z, w) = false;
      }
    } else if (n == 3) {
      mb(x, y, z, w) = true;
    }
  }
  int validCount() { return std::count(ma.begin(), ma.end(), 1); }

  void transform()
  {
    NX += 2;
    NY += 2;
    for (int i = Origin - NX / 2; i < Origin + NX / 2 + 1; ++i) {
      for (int j = Origin - NX / 2; j < Origin + NX / 2 + 1; ++j) {
        for (int k = Origin - NY / 2; k < Origin + NY / 2 + 1; ++k) {
          for (int l = Origin - NY / 2; l < Origin + NY / 2 + 1; ++l) {
            turn(i, j, k, l);
          }
        }
      }
    }
    ma = mzero;
    ma = std::exchange(mb, mzero);
  }
};

int main(int argc, char** argv)
{
  if (argc > 1) {
    std::ifstream  ifs(argv[1]);
    Conwaycube<23> c;
    ifs >> c;
    cout << c.validCount() << endl;
    for (int i = 0; i < 6; ++i) {
      c.transform();
    }
    cout << c.validCount() << endl;
  }
}
