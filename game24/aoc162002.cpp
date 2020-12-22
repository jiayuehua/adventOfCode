#include <complex>
#include <exception>
#include <fstream>
#include <sstream>
#include <numeric>
#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>
#include <cstdint>
#include <boost/icl/closed_interval.hpp>
#include <boost/icl/interval_set.hpp>
namespace icl = boost::icl;
using gint = std::int64_t;

int main(int argc, char **argv)
{
  if (argc > 1) {
    gint l, h;
    icl::interval_set<gint> ips;
    std::ifstream ifs(argv[1]);
    while (ifs >> l >> h) {
      icl::interval<gint>::type p(l, h);
      ips.add(p);
    }
    icl::interval_set<gint> ipsb = ips;
    auto j = ips.begin();
    ++j;
    for (auto i = ips.begin(); i != ips.end() && (j != ips.end()); ++i, ++j) {
      if (j->lower() - i->upper() == 1) {
        icl::interval<gint>::type p(i->upper(), j->lower());
        ipsb.add(p);
      }
    }
    gint count = 0;
    for (auto i = ipsb.begin(); i != ipsb.end(); ++i) {
      count += (i->upper() - i->lower() + 1);
    }
    std::cout << std::numeric_limits<unsigned int>::max() - count + 1 << std::endl;
  }

  return 0;
}
