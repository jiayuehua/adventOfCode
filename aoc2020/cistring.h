#pragma once
#include <string>
#include <string_view>
#include <iostream>
struct ci_char_traits : public std::char_traits<char> {
  static char to_upper(char ch) { return std::toupper((unsigned char)ch); }
  static bool eq(char c1, char c2) { return to_upper(c1) == to_upper(c2); }
  static bool lt(char c1, char c2) { return to_upper(c1) < to_upper(c2); }
  static int  compare(const char *s1, const char *s2, std::size_t n)
  {
    while (n-- != 0) {
      if (to_upper(*s1) < to_upper(*s2)) return -1;
      if (to_upper(*s1) > to_upper(*s2)) return 1;
      ++s1;
      ++s2;
    }
    return 0;
  }
  static const char *find(const char *s, std::size_t n, char a)
  {
    auto const ua(to_upper(a));
    while (n-- != 0) {
      if (to_upper(*s) == ua) return s;
      s++;
    }
    return nullptr;
  }
  friend std::istream &operator>>(std::istream &is, cistring &s)
  {
    std::string str;
    is >> str;
    s.resize(str.size());
    ranges::copy(str, s.begin());
    return is;
  }
  friend std::ostream &operator<<(std::istream &os, const cistring &s)
  {
    std::string str(s.c_str(), s.size());
    return os << str;
  }
};

using cistring      = std::basic_string<char, ci_char_traits>;
using cistring_view = std::basic_string_view<char, ci_char_traits>;
