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
using x3::lit;
x3::rule<class r0, std::string> const r0 = "r0";
x3::rule<class r1, std::string> const r1 = "r1";
x3::rule<class r2, std::string> const r2 = "r2";
x3::rule<class r3, std::string> const r3 = "r3";
x3::rule<class r4, std::string> const r4 = "r4";
x3::rule<class r5, std::string> const r5 = "r5";
x3::rule<class r6, std::string> const r6 = "r6";
x3::rule<class r7, std::string> const r7 = "r7";
x3::rule<class r8, std::string> const r8 = "r8";
x3::rule<class r9, std::string> const r9 = "r9";
x3::rule<class r10, std::string> const r10 = "r10";
x3::rule<class r11, std::string> const r11 = "r11";
x3::rule<class r12, std::string> const r12 = "r12";
x3::rule<class r13, std::string> const r13 = "r13";
x3::rule<class r14, std::string> const r14 = "r14";
x3::rule<class r15, std::string> const r15 = "r15";
x3::rule<class r16, std::string> const r16 = "r16";
x3::rule<class r17, std::string> const r17 = "r17";
x3::rule<class r18, std::string> const r18 = "r18";
x3::rule<class r19, std::string> const r19 = "r19";
x3::rule<class r20, std::string> const r20 = "r20";
x3::rule<class r21, std::string> const r21 = "r21";
x3::rule<class r22, std::string> const r22 = "r22";
x3::rule<class r23, std::string> const r23 = "r23";
x3::rule<class r24, std::string> const r24 = "r24";
x3::rule<class r25, std::string> const r25 = "r25";
x3::rule<class r26, std::string> const r26 = "r26";
x3::rule<class r27, std::string> const r27 = "r27";
x3::rule<class r28, std::string> const r28 = "r28";
x3::rule<class r29, std::string> const r29 = "r29";
x3::rule<class r30, std::string> const r30 = "r30";
x3::rule<class r31, std::string> const r31 = "r31";
x3::rule<class r32, std::string> const r32 = "r32";
x3::rule<class r33, std::string> const r33 = "r33";
x3::rule<class r34, std::string> const r34 = "r34";
x3::rule<class r35, std::string> const r35 = "r35";
x3::rule<class r36, std::string> const r36 = "r36";
x3::rule<class r37, std::string> const r37 = "r37";
x3::rule<class r38, std::string> const r38 = "r38";
x3::rule<class r39, std::string> const r39 = "r39";
x3::rule<class r40, std::string> const r40 = "r40";
x3::rule<class r41, std::string> const r41 = "r41";
x3::rule<class r42, std::string> const r42 = "r42";

//x3::rule<class r8, std::string> const r43 = "r43";
//x3::rule<class r8, std::string> const r44 = "r44";

const auto r0_def = r42 >> r0 | r42 >> r11;
const auto r1_def = lit("a");
const auto r2_def = r1 >> r24 | r14 >> r4;
const auto r3_def = r5 >> r14 | r16 >> r1;
const auto r4_def = r1 >> r1;
const auto r5_def = r1 >> r14 | r15 >> r1;
const auto r6_def = r14 >> r14 | r1 >> r14;
const auto r7_def = r14 >> r5 | r1 >> r21;

//const auto r43_def =  r42 >> r8;
const auto r8_def = r11 | r31;
const auto r9_def = r14 >> r27 | r1 >> r26;
const auto r10_def = r23 >> r14 | r28 >> r1;
const auto r11_def = r42 >> r8 | r42 >> r31;
const auto r12_def = r24 >> r14 | r19 >> r1;
const auto r13_def = r14 >> r3 | r1 >> r12;
const auto r14_def = lit("b");
const auto r15_def = r1 | r14;
const auto r16_def = r15 >> r1 | r14 >> r14;
const auto r17_def = r14 >> r2 | r1 >> r7;
const auto r18_def = r15 >> r15;
const auto r19_def = r14 >> r1 | r14 >> r14;
const auto r20_def = r14 >> r14 | r1 >> r15;
const auto r21_def = r14 >> r1 | r1 >> r14;
const auto r22_def = r14 >> r14;
const auto r23_def = r25 >> r1 | r22 >> r14;
const auto r24_def = r14 >> r1;
const auto r25_def = r1 >> r1 | r1 >> r14;
const auto r26_def = r14 >> r22 | r1 >> r20;
const auto r27_def = r1 >> r6 | r14 >> r18;
const auto r28_def = r16 >> r1;
const auto r31_def = r14 >> r17 | r1 >> r13;
const auto r42_def = r9 >> r14 | r10 >> r1;
//const auto r43_def = r8;
//const auto r44_def = r11 >> r31;
BOOST_SPIRIT_DEFINE(r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19)
BOOST_SPIRIT_DEFINE(r20, r21, r22, r23, r24, r25, r26, r27, r28, r31)
BOOST_SPIRIT_DEFINE(r42)
//BOOST_SPIRIT_DEFINE(r43)
//BOOST_SPIRIT_DEFINE(r44)
}// namespace parser
int64 getAll24Exprs(std::string const &oneexpr)
{
  using parser::r0;
  using ascii::space;
  std::string::const_iterator iter = oneexpr.cbegin();
  std::string::const_iterator b = oneexpr.cbegin();
  std::string::const_iterator end = oneexpr.cend();
  bool r = x3::phrase_parse(iter, end, r0, space);
  return (iter == end) && r;
}

int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string expr;
    int sum = 0;
    while (std::getline(ifs, expr)) {

      if (getAll24Exprs(expr)) {
        sum += 1;
        //std::cout << "expr:" << expr << std::endl;
        ;
      }
      expr.clear();
    }
    std::cout << "sum:" << sum << std::endl;
  }
}
