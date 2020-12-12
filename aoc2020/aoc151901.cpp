#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <numeric>
#include <iomanip>
#include <execution>
#include <boost/algorithm/string.hpp>
#include <range/v3/all.hpp>
#include <iterator>
#include <utility>
#include <string_view>
#include <cctype>
namespace views = ranges::views;
namespace actions = ranges::actions;
namespace algo = boost::algorithm;

struct AllString
{
private:
  std::string s_ = "CRnSiRnCaPTiMgYCaPTiRnFArSiThFArCaSiThSiThPBCaCaSiRnSiRnTiTiMgArPBCaPMgYPTiRnFArFArCaSiRnBPMgArPRnCaPTiRnFArCaSiThCaCaFArPBCaCaPTiTiRnFArCaSiRnSiAlYSiThRnFArArCaSiRnBFArCaCaSiRnSiThCaCaCaFYCaPTiBCaSiThCaSiThPMgArSiRnCaPBFYCaCaFArCaCaCaCaSiThCaSiRnPRnFArPBSiThPRnFArSiRnMgArCaFYFArCaSiRnSiAlArTiTiTiTiTiTiTiRnPMgArPTiTiTiBSiRnSiAlArTiTiRnPMgArCaFYBPBPTiRnSiRnMgArSiThCaFArCaSiThFArPRnFArCaSiRnTiBSiThSiRnSiAlYCaFArPRnFArSiThCaFArCaCaSiThCaCaCaSiRnPRnCaFArFYPMgArCaPBCaPBSiRnFYPBCaFArCaSiAl";

  std::vector<std::string> vs_;
  std::vector<std::pair<std::string, std::string>> kv_;

public:
  void push(std::pair<std::string, std::string> p)
  {
    kv_.push_back(std::move(p));
  }
  auto count() noexcept
  {
    for (auto &&kv : kv_) {
      typedef std::pair<std::string::iterator, std::string::iterator> Pair;

      std::vector<Pair> vs;
      boost::algorithm::find_all(vs, s_, kv.first);
      for (int i = 0; i < static_cast<int>(vs.size()); ++i) {
        std::string sc = algo::replace_nth_copy(s_, kv.first, i, kv.second);
        vs_.push_back(std::move(sc));
      }
    }
    auto r = std::move(vs_) | actions::sort | actions::unique;
    return r.size();
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::string ignore;
    std::ifstream ifs(argv[1]);
    std::pair<std::string, std::string> p;

    AllString as;
    while (ifs >> p.first >> ignore >> p.second) {
      as.push(std::move(p));
    }
    fmt::print("{}\n", as.count());
  }
}