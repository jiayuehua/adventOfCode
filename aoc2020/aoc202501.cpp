#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <fmt/format.h>
#include <numeric>
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <iomanip>
#include <set>
#include <utility>
#include <range/v3/all.hpp>

int main()
{
  std::int64_t n = 1;
  //12578151;
  for (int i = 0; i < 10000000; ++i) {
    n = n * 7;
    n = n % 20201227;
    if (n == 12578151) {
      fmt::print("B{},{}\n", i, n);
      break;
    }
  }
  n = 1;
  for (int i = 0; i < 10000000; ++i) {
    n = n * 7;
    n = n % 20201227;
    if (n == 5051300) {
      fmt::print("B{},{}\n", i, n);
      break;
    }
  }
  std::int64_t k = 1;
  for (int i = 0; i < 5497777; ++i) {
    k = k * 12578151;

    k = k % 20201227;
  }
  fmt::print("{}\n", k);
  k = 1;
  for (int i = 0; i < 538014; ++i) {
    k = k * 5051300;
    k = k % 20201227;
  }
  fmt::print("{}\n", k);
}
