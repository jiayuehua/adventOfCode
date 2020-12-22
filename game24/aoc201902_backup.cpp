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
x3::rule<class r43, std::string> const r43 = "r43";
x3::rule<class r44, std::string> const r44 = "r44";
x3::rule<class r45, std::string> const r45 = "r45";
x3::rule<class r46, std::string> const r46 = "r46";
x3::rule<class r47, std::string> const r47 = "r47";
x3::rule<class r48, std::string> const r48 = "r48";
x3::rule<class r49, std::string> const r49 = "r49";
x3::rule<class r50, std::string> const r50 = "r50";
x3::rule<class r51, std::string> const r51 = "r51";
x3::rule<class r52, std::string> const r52 = "r52";
x3::rule<class r53, std::string> const r53 = "r53";
x3::rule<class r54, std::string> const r54 = "r54";
x3::rule<class r55, std::string> const r55 = "r55";
x3::rule<class r56, std::string> const r56 = "r56";
x3::rule<class r57, std::string> const r57 = "r57";
x3::rule<class r58, std::string> const r58 = "r58";
x3::rule<class r59, std::string> const r59 = "r59";
x3::rule<class r60, std::string> const r60 = "r60";
x3::rule<class r61, std::string> const r61 = "r61";
x3::rule<class r62, std::string> const r62 = "r62";
x3::rule<class r63, std::string> const r63 = "r63";
x3::rule<class r64, std::string> const r64 = "r64";
x3::rule<class r65, std::string> const r65 = "r65";
x3::rule<class r66, std::string> const r66 = "r66";
x3::rule<class r67, std::string> const r67 = "r67";
x3::rule<class r68, std::string> const r68 = "r68";
x3::rule<class r69, std::string> const r69 = "r69";
x3::rule<class r70, std::string> const r70 = "r70";
x3::rule<class r71, std::string> const r71 = "r71";
x3::rule<class r72, std::string> const r72 = "r72";
x3::rule<class r73, std::string> const r73 = "r73";
x3::rule<class r74, std::string> const r74 = "r74";
x3::rule<class r75, std::string> const r75 = "r75";
x3::rule<class r76, std::string> const r76 = "r76";
x3::rule<class r77, std::string> const r77 = "r77";
x3::rule<class r78, std::string> const r78 = "r78";
x3::rule<class r79, std::string> const r79 = "r79";
x3::rule<class r80, std::string> const r80 = "r80";
x3::rule<class r81, std::string> const r81 = "r81";
x3::rule<class r82, std::string> const r82 = "r82";
x3::rule<class r83, std::string> const r83 = "r83";
x3::rule<class r84, std::string> const r84 = "r84";
x3::rule<class r85, std::string> const r85 = "r85";
x3::rule<class r86, std::string> const r86 = "r86";
x3::rule<class r87, std::string> const r87 = "r87";
x3::rule<class r88, std::string> const r88 = "r88";
x3::rule<class r89, std::string> const r89 = "r89";
x3::rule<class r90, std::string> const r90 = "r90";
x3::rule<class r91, std::string> const r91 = "r91";
x3::rule<class r92, std::string> const r92 = "r92";
x3::rule<class r93, std::string> const r93 = "r93";
x3::rule<class r94, std::string> const r94 = "r94";
x3::rule<class r95, std::string> const r95 = "r95";
x3::rule<class r96, std::string> const r96 = "r96";
x3::rule<class r97, std::string> const r97 = "r97";
x3::rule<class r98, std::string> const r98 = "r98";
x3::rule<class r99, std::string> const r99 = "r99";
x3::rule<class r100, std::string> const r100 = "r100";
x3::rule<class r101, std::string> const r101 = "r101";
x3::rule<class r102, std::string> const r102 = "r102";
x3::rule<class r103, std::string> const r103 = "r103";
x3::rule<class r104, std::string> const r104 = "r104";
x3::rule<class r105, std::string> const r105 = "r105";
x3::rule<class r106, std::string> const r106 = "r106";
x3::rule<class r107, std::string> const r107 = "r107";
x3::rule<class r108, std::string> const r108 = "r108";
x3::rule<class r109, std::string> const r109 = "r109";
x3::rule<class r110, std::string> const r110 = "r110";
x3::rule<class r111, std::string> const r111 = "r111";
x3::rule<class r112, std::string> const r112 = "r112";
x3::rule<class r113, std::string> const r113 = "r113";
x3::rule<class r114, std::string> const r114 = "r114";
x3::rule<class r115, std::string> const r115 = "r115";
x3::rule<class r116, std::string> const r116 = "r116";
x3::rule<class r117, std::string> const r117 = "r117";
x3::rule<class r118, std::string> const r118 = "r118";
x3::rule<class r119, std::string> const r119 = "r119";
x3::rule<class r120, std::string> const r120 = "r120";
x3::rule<class r121, std::string> const r121 = "r121";
x3::rule<class r122, std::string> const r122 = "r122";
x3::rule<class r123, std::string> const r123 = "r123";
x3::rule<class r124, std::string> const r124 = "r124";
x3::rule<class r125, std::string> const r125 = "r125";
x3::rule<class r126, std::string> const r126 = "r126";
x3::rule<class r127, std::string> const r127 = "r127";
x3::rule<class r128, std::string> const r128 = "r128";
x3::rule<class r129, std::string> const r129 = "r129";
x3::rule<class r130, std::string> const r130 = "r130";
x3::rule<class r131, std::string> const r131 = "r131";
x3::rule<class r132, std::string> const r132 = "r132";
x3::rule<class r133, std::string> const r133 = "r133";
const auto r0_def = r8 >> r11;
const auto r1_def = r23 >> r35 | r105 >> r30;
const auto r2_def = r23 >> r30;
const auto r3_def = r71 >> r23 | r19 >> r105;
const auto r4_def = r23 >> r41 | r105 >> r15;
const auto r5_def = r15 >> r105 | r9 >> r23;
const auto r6_def = r58 >> r105 | r59 >> r23;
const auto r7_def = r105 >> r48 | r23 >> r12;
const auto r8_def = r42 | (r42 >> r8);
const auto r9_def = r105 >> r131 | r23 >> r55;
const auto r10_def = r102 >> r105 | r126 >> r23;
const auto r11_def = (r42 >> r31) | (r42 >> r11 >> r31);
const auto r12_def = r23 >> r23 | r23 >> r105;
const auto r13_def = r23 >> r18 | r105 >> r87;
const auto r14_def = r99 >> r105 | r81 >> r23;
const auto r15_def = r105 >> r71;
const auto r16_def = r105 >> r125 | r23 >> r28;
const auto r17_def = r23 >> r104 | r105 >> r131;
const auto r18_def = r23 >> r118 | r105 >> r29;
const auto r19_def = r23 >> r105 | r105 >> r94;
const auto r20_def = r115 >> r105 | r86 >> r23;
const auto r21_def = r23 >> r71 | r105 >> r104;
const auto r22_def = r30 >> r105;
const auto r23_def = lit("a");
const auto r24_def = r4 >> r105 | r26 >> r23;
const auto r25_def = r105 >> r62 | r23 >> r89;
const auto r26_def = r21 >> r23 | r56 >> r105;
const auto r27_def = r5 >> r23 | r10 >> r105;
const auto r28_def = r105 >> r129 | r23 >> r112;
const auto r29_def = r105 >> r119 | r23 >> r117;
const auto r30_def = r105 >> r105;
const auto r31_def = r105 >> r65 | r23 >> r13;
const auto r32_def = r105 >> r114 | r23 >> r6;
const auto r33_def = r23 >> r89 | r105 >> r101;
const auto r34_def = r23 >> r39 | r105 >> r80;
const auto r35_def = r23 >> r23 | r105 >> r23;
const auto r36_def = r64 >> r105 | r68 >> r23;
const auto r37_def = r48 >> r105 | r55 >> r23;
const auto r38_def = r19 >> r23 | r48 >> r105;
const auto r39_def = r105 >> r105 | r23 >> r23;
const auto r40_def = r23 >> r39 | r105 >> r35;
const auto r41_def = r23 >> r121 | r105 >> r55;
const auto r42_def = r105 >> r128 | r23 >> r132;
const auto r43_def = r23 >> r23 | r94 >> r105;
const auto r44_def = r23 >> r105;
const auto r45_def = r105 >> r33 | r23 >> r84;
const auto r46_def = r30 >> r23 | r39 >> r105;
const auto r47_def = r105 >> r30 | r23 >> r30;
const auto r48_def = r105 >> r23 | r23 >> r94;
const auto r49_def = r104 >> r105 | r55 >> r23;
const auto r50_def = r105 >> r95 | r23 >> r96;
const auto r51_def = r19 >> r105 | r131 >> r23;
const auto r52_def = r105 >> r19 | r23 >> r104;
const auto r53_def = r67 >> r105 | r14 >> r23;
const auto r54_def = r23 >> r48 | r105 >> r55;
const auto r55_def = r105 >> r94 | r23 >> r23;
const auto r56_def = r105 >> r39;
const auto r57_def = r23 >> r30 | r105 >> r121;
const auto r58_def = r55 >> r23 | r131 >> r105;
const auto r59_def = r105 >> r121 | r23 >> r71;
const auto r60_def = r104 >> r105 | r80 >> r23;
const auto r61_def = r85 >> r23 | r70 >> r105;
const auto r62_def = r19 >> r105 | r104 >> r23;
const auto r63_def = r72 >> r105 | r133 >> r23;
const auto r64_def = r23 >> r121 | r105 >> r12;
const auto r65_def = r83 >> r23 | r53 >> r105;
const auto r66_def = r105 >> r113 | r23 >> r49;
const auto r67_def = r23 >> r103 | r105 >> r63;
const auto r68_def = r23 >> r131 | r105 >> r48;
const auto r69_def = r80 >> r105 | r104 >> r23;
const auto r70_def = r19 >> r23 | r12 >> r105;
const auto r71_def = r23 >> r23;
const auto r72_def = r39 >> r105 | r19 >> r23;
const auto r73_def = r105 >> r121 | r23 >> r19;
const auto r74_def = r105 >> r123 | r23 >> r7;
const auto r75_def = r34 >> r105 | r59 >> r23;
const auto r76_def = r37 >> r105 | r78 >> r23;
const auto r77_def = r23 >> r88 | r105 >> r74;
const auto r78_def = r23 >> r131 | r105 >> r35;
const auto r79_def = r17 >> r23 | r78 >> r105;
const auto r80_def = r105 >> r105 | r105 >> r23;
const auto r81_def = r51 >> r105 | r116 >> r23;
const auto r82_def = r105 >> r19 | r23 >> r12;
const auto r83_def = r105 >> r45 | r23 >> r27;
const auto r84_def = r21 >> r23 | r130 >> r105;
const auto r85_def = r12 >> r23 | r39 >> r105;
const auto r86_def = r23 >> r98 | r105 >> r93;
const auto r87_def = r23 >> r77 | r105 >> r91;
const auto r88_def = r120 >> r105 | r78 >> r23;
const auto r89_def = r121 >> r105 | r39 >> r23;
const auto r90_def = r105 >> r32 | r23 >> r107;
const auto r91_def = r25 >> r23 | r66 >> r105;
const auto r92_def = r44 >> r23 | r12 >> r105;
const auto r93_def = r52 >> r23 | r22 >> r105;
const auto r94_def = r105 | r23;
const auto r95_def = r105 >> r69 | r23 >> r109;
const auto r96_def = r85 >> r23 | r73 >> r105;
const auto r97_def = r105 >> r12 | r23 >> r104;
const auto r98_def = r23 >> r38 | r105 >> r82;
const auto r99_def = r47 >> r105 | r1 >> r23;
const auto r100_def = r72 >> r105 | r110 >> r23;
const auto r101_def = r105 >> r44 | r23 >> r43;
const auto r102_def = r43 >> r105 | r48 >> r23;
const auto r103_def = r105 >> r89 | r23 >> r57;
const auto r104_def = r23 >> r105 | r105 >> r23;
const auto r105_def = lit("b");
const auto r106_def = r71 >> r105 | r44 >> r23;
const auto r107_def = r105 >> r79 | r23 >> r76;
const auto r108_def = r105 >> r2 | r23 >> r54;
const auto r109_def = r44 >> r23 | r39 >> r105;
const auto r110_def = r12 >> r23 | r35 >> r105;
const auto r111_def = r105 >> r35 | r23 >> r104;
const auto r112_def = r92 >> r23 | r97 >> r105;
const auto r113_def = r39 >> r23 | r12 >> r105;
const auto r114_def = r70 >> r23 | r106 >> r105;
const auto r115_def = r108 >> r105 | r36 >> r23;
const auto r116_def = r12 >> r105 | r131 >> r23;
const auto r117_def = r124 >> r105 | r60 >> r23;
const auto r118_def = r105 >> r127 | r23 >> r75;
const auto r119_def = r105 >> r40 | r23 >> r46;
const auto r120_def = r105 >> r131 | r23 >> r44;
const auto r121_def = r94 >> r94;
const auto r122_def = r50 >> r105 | r24 >> r23;
const auto r123_def = r71 >> r105 | r35 >> r23;
const auto r124_def = r80 >> r105 | r71 >> r23;
const auto r125_def = r23 >> r61 | r105 >> r100;
const auto r126_def = r35 >> r23 | r43 >> r105;
const auto r127_def = r23 >> r3 | r105 >> r49;
const auto r128_def = r23 >> r90 | r105 >> r20;
const auto r129_def = r105 >> r109 | r23 >> r111;
const auto r130_def = r23 >> r30 | r105 >> r44;
const auto r131_def = r105 >> r23;
const auto r132_def = r23 >> r16 | r105 >> r122;
const auto r133_def = r80 >> r94;
BOOST_SPIRIT_DEFINE(r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19)
BOOST_SPIRIT_DEFINE(r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31, r32, r33, r34, r35, r36, r37, r38, r39)
BOOST_SPIRIT_DEFINE(r40, r41, r42, r43, r44, r45, r46, r47, r48, r49, r50, r51, r52, r53, r54, r55, r56, r57, r58, r59)
BOOST_SPIRIT_DEFINE(r60, r61, r62, r63, r64, r65, r66, r67, r68, r69, r70, r71, r72, r73, r74, r75, r76, r77, r78, r79)
BOOST_SPIRIT_DEFINE(r80, r81, r82, r83, r84, r85, r86, r87, r88, r89, r90, r91, r92, r93, r94, r95, r96, r97, r98, r99)
BOOST_SPIRIT_DEFINE(r100, r101, r102, r103, r104, r105, r106, r107, r108, r109, r110, r111, r112, r113, r114, r115, r116, r117, r118, r119)
BOOST_SPIRIT_DEFINE(r120, r121, r122, r123, r124, r125, r126, r127, r128, r129, r130, r131, r132, r133)
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
