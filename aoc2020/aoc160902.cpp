#include <range/v3/all.hpp>
#include <fstream>
#include <sstream>
#include <iterator>
#include <fmt/format.h>
#include <numeric>
#include <string>
#include <execution>
#include <vector>
#include <functional>
#include <iomanip>
#include <regex>
#include <iterator>
#include <iostream>
#include <string>
#include <tuple>
#include <cstdint>
using bint = std::int64_t;
namespace views = ranges::views;
struct Zip
{
  std::string s_;
  std::vector<std::tuple<int, int, int, int, std::string>> vp_;//pos,len, x,y

  bint totalLen() const
  {
    int e = s_.size();
    int b = 0;
    bint l = s_.size();
    for (auto &&[pos, regexlen, len, times, match] : vp_) {
      if (pos >= b && pos < e
          && (pos + regexlen) < e
          && (pos + regexlen + len) <= e) {
        l -= regexlen;
        l -= len;
        //fmt::print("match:{}\n", match);
        //(3x3)ABC

        Zip z(s_.substr(pos + regexlen, len));
        //fmt::print("totallen:{}\n", z.totalLen());
        l += (z.totalLen() * times);
        b = pos + regexlen + len;
      }
    }
    return l;
  }


  Zip(const std::string &s) : s_(s)
  {
    std::regex words_regex(R"(\((\d+)x(\d+)\))");
    auto words_begin =
      std::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();

    //std::cout << "Found "
    //          << std::distance(words_begin, words_end)
    //          << " words:\n";

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
      std::smatch match = *i;
      std::string match_str = match.str();
      //std::cout << match_str << ',';
      //std::cout << match[1] << ',';
      //std::cout << match[2] << ';';
      vp_.push_back(std::make_tuple(match.position(0), match.length(), std::stoi(match[1]), std::stoi(match[2]), match.str(0)));
    }
  }
};

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);

    std::string s;
    ifs >> s;
    Zip z(s);
    fmt::print("len:{}\n", z.totalLen());
  }
}
