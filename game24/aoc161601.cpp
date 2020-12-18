#include <complex>
#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <range/v3/all.hpp>
#include <cstdint>
#include <boost/dynamic_bitset.hpp>
using mybitset = boost::dynamic_bitset<unsigned>;
mybitset convertimpl(const mybitset &bitset)
{

  boost::dynamic_bitset<unsigned> zero(1, 0);
  boost::dynamic_bitset<unsigned> bb;
  std::string sbb;
  std::ostringstream obb(sbb);
  obb << ~bitset;
  std::string sbbcpy;
  ranges::reverse_copy(obb.str(), std::back_inserter(sbbcpy));

  std::istringstream ibb(sbbcpy);
  ibb >> bb;


  bb.resize(bitset.size());
  std::string s;
  std::ostringstream ost(s);
  ost << bitset << zero << bb;
  boost::dynamic_bitset<unsigned> result;
  std::string b(ost.str());
  std::istringstream iss(b.substr(0, 35651584));
  iss >> result;
  return result;
}
mybitset convert(const mybitset &bitset)
{
  auto r = convertimpl(bitset);
  if (r.size() < 35651584) {
    return convert(r);
  } else {
    r.resize(35651584);
    return r;
  }
}
mybitset shrink(mybitset bitset)
{

  while (bitset.size() % 2 == 0) {
    mybitset r(bitset.size() / 2);
    int n = r.size();
    for (int i = 0; i < n; ++i) {
      bool lhs = bitset[2 * i];
      bool rhs = bitset[2 * i + 1];
      auto t = !(lhs ^ rhs);
      r.set(i, t);
    }
    bitset = r;
  }
  return bitset;
}


int main()
{
  boost::dynamic_bitset<unsigned> bitset(17, 0b00111101111101000);
  auto r = convert(bitset);

  auto s = shrink(r);
  std::cout << "result:" << s << std::endl;
  return 0;
}
