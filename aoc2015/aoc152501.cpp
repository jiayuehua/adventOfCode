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
// 0 ,1
//1,2
//(i,j)( i+j +1
//i,j+1   (i+j+1,0
int main(int argc, char **argv)
{
  int i = 2978 - 1, j = 3083 - 1;
  int n = (i - 1) + j;
  int total = 0;
  for (int i = 0; i <= n; ++i) {
    total += 1 + i;
  }
  total += j + 1;
  //a[total]-1;
  std::int64_t a = 20151125;
  for (int i = 1; i < total; ++i) {
    a *= 252533;
    a %= 33554393;
    //fmt::print(";i:{},a:{}", i, a);
    //
  }
  fmt::print("{}", a);
}
