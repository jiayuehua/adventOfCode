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
#include <unordered_map>
#include <string_view>
#include <iostream>
#include <cctype>
#include <functional>
#include <limits>
namespace views = ranges::views;
namespace actions = ranges::actions;
namespace algo = boost::algorithm;

struct AllString
{
private:
  std::vector<std::string> vs_;
  std::map<std::string, std::string, std::greater<>> kv_;
  int mincount_ = std::numeric_limits<int>::max();
  int steps_ = 0;

public:
  void push(std::pair<std::string, std::string> p)
  {
    kv_.insert(std::move(p));
  }
  void count(const std::string &source) noexcept
  {
    for (auto &&kv : kv_) {

      typedef std::pair<std::string::const_iterator, std::string::const_iterator> Pair;

      std::vector<Pair> vs;
      boost::algorithm::find_all(vs, source, kv.first);
      if (vs.size()) {
        ++steps_;
      }
      if (steps_ < mincount_) {
        for (int i = 0; i < static_cast<int>(vs.size()); ++i) {
          std::string sc = algo::replace_nth_copy(source, kv.first, i, kv.second);

          if (sc == "e") {
            mincount_ = std::min(steps_, mincount_);
            //fmt::print("mincount_:{}\n", mincount_);
            break;
          } else {
            count(sc);
          }
        }
      }

      if (vs.size()) {
        --steps_;
      }
    }
  }
  constexpr int minsteps() const noexcept
  {
    return mincount_;
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::string ignore;
    std::ifstream ifs(argv[1]);
    std::pair<std::string, std::string> p;

    AllString as;
    while (ifs >> p.second >> ignore >> p.first) {
      as.push(std::move(p));
    }
    std::string s_ = "CRnSiRnCaPTiMgYCaPTiRnFArSiThFArCaSiThSiThPBCaCaSiRnSiRnTiTiMgArPBCaPMgYPTiRnFArFArCaSiRnBPMgArPRnCaPTiRnFArCaSiThCaCaFArPBCaCaPTiTiRnFArCaSiRnSiAlYSiThRnFArArCaSiRnBFArCaCaSiRnSiThCaCaCaFYCaPTiBCaSiThCaSiThPMgArSiRnCaPBFYCaCaFArCaCaCaCaSiThCaSiRnPRnFArPBSiThPRnFArSiRnMgArCaFYFArCaSiRnSiAlArTiTiTiTiTiTiTiRnPMgArPTiTiTiBSiRnSiAlArTiTiRnPMgArCaFYBPBPTiRnSiRnMgArSiThCaFArCaSiThFArPRnFArCaSiRnTiBSiThSiRnSiAlYCaFArPRnFArSiThCaFArCaCaSiThCaCaCaSiRnPRnCaFArFYPMgArCaPBCaPBSiRnFYPBCaFArCaSiAl";
    as.count(s_);
    fmt::print("{}\n", as.minsteps());
  }
}