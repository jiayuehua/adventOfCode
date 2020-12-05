#include <range/v3/all.hpp>
#include <unordered_set>
#include <fstream>
#include <iterator>
#include <fmt/format.h>
#include <optional>


//struct Advance
//{
//  static inline constexpr int a[2] = { -1, 1 };
//  int &n;
//  constexpr int operator()(char c) noexcept
//  {
//    return n += a[c == ')'];
//  }
//};

int main(int argc, char **argv)
{
  if (argc > 1) {
    fmt::print("{}\n", argv[1]);
    std::ifstream ifs(argv[1]);
    //std::istream_iterator<std::string> ib(ifs);
    //std::istream_iterator<std::string> ie;
    std::string s;
    ifs >> s;
    int n = 0;
    fmt::print("{}\n", s);
    auto it = ranges::find_if(s, [&n](char c) {
      static constexpr int a[2] = { -1, 1 };

      n += a[c == '('];
      return n == -1;
    });
    fmt::print("{}\n", it - s.begin() + 1);
  }
}