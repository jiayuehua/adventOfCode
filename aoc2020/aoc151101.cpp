#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <range/v3/algorithm.hpp>

struct Number
{
private:
  std::string s;
  static inline const std::string allchars_ = "abcdefghijklmnopqrstuvwxyz";

public:
  Number() {}
  Number(std::string sa) : s(sa) {}
  friend std::ostream &operator<<(std::ostream &os, Number n)
  {
    os << n.s;
    return os;
  }
  Number &operator++()
  {
    char carry = 1;
    auto len = s.size();
    for (std::size_t i = 0; i < (len); ++i) {
      auto index = (len - 1 - i);

      char sum = s[index] + carry;
      char c = static_cast<char>((sum - 'a') % 26 + 'a');
      carry = static_cast<char>((sum - 'a') / 26);
      s[index] = c;
    }
    if (carry == 1) {
      s = 'b' + s;
    }
    return *this;
  }
  operator bool() const noexcept
  {
    return ca() && cb() && cc();
  }

private:
  bool ca() const noexcept
  {
    for (int i = 0; i < 24; ++i) {
      if (s.find(std::string_view(allchars_.c_str() + i, 3)) != s.npos) {
        return true;
      }
    }
    return false;
  }
  bool cb() const noexcept
  {
    return s.find_first_of("iol") == s.npos;
  }
  bool cc() const noexcept
  {
    auto first = std::adjacent_find(s.cbegin(), s.cend());
    if (first == s.cend()) {
      return false;
    }
    auto second = std::adjacent_find(first + 2, s.cend());
    return (second != s.cend() && (*first != *second));
  }
};


int main()
{
  Number n("hxbxwxba");
  for (; !n; ++n) {
  }
  ++n;
  for (; !n; ++n) {
  }
  std::cout << n << "\n";
}