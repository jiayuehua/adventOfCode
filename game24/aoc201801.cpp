#include <complex>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <range/v3/all.hpp>
#include <cstdint>

#include "exprs.h"
#include "cal.h"
using int64 = std::int64_t;
namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;
namespace parser {
using x3::eps;
using x3::int_;
using x3::lexeme;
x3::rule<class expr, std::int64_t> const expr = "expr";
x3::rule<class term, std::int64_t> const term = "term";
//x3::rule<class factor, int> const factor = "factor";
x3::rule<class group, int64> const group = "group";
auto indentity = [](auto &ctx) { _val(ctx) = _attr(ctx); };
auto multi = [](auto &ctx) { _val(ctx) *= _attr(ctx); };
//auto divide = [](auto &ctx) {
//  if (_attr(ctx) && (!(_val(ctx) % _attr(ctx)))) {
//    _val(ctx) /= _attr(ctx);
//  } else {
//    _pass(ctx) = false;
//  }
//};
auto add = [](auto &ctx) { _val(ctx) += _attr(ctx); };
auto sub = [](auto &ctx) { _val(ctx) -= _attr(ctx); };
auto const expr_def = term[indentity] >> *(('+' >> term[add]) | ('-' >> term[sub]) | ('*' >> (term)[multi]));//左结合
//auto const term_def = factor[indentity];//左结合
auto const term_def = (int_ | group);
auto const group_def = '(' >> expr >> ')';

BOOST_SPIRIT_DEFINE(expr, term, group)
}// namespace parser
int64 getAll24Exprs(std::string const &oneexpr)
{
  using parser::expr;
  using ascii::space;
  int64 result{ 0 };
  std::string::const_iterator iter = oneexpr.cbegin();
  std::string::const_iterator end = oneexpr.cend();
  bool r = x3::phrase_parse(iter, end, expr, space, result);
  std::cout << "origin:" << oneexpr << std::endl;
  std::cout << "origin:" << oneexpr << std::endl;

  if (r) {
    std::cout << "success:" << oneexpr << "," << result << std::endl;
    std::cout << std::endl;
  } else {
    std::cout << "fail:" << oneexpr << " #  " << std::endl;
  }
  return result;
}


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string expr;
    std::int64_t sum = 0;
    while (std::getline(ifs, expr)) {
      sum += getAll24Exprs(expr);
    }
    //fmt::print("{}", val24exprstr)
    std::cout << "sum:" << sum << std::endl;
  }
}
