#include <complex>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/circular_buffer.hpp>
#include <range/v3/all.hpp>
#include <numeric>
#include <algorithm>
namespace views = ranges::views;

void spin(std::string &s, const std::string &, const std::string &num)
{
  auto n = std::stoi(num);
  std::rotate(s.begin(), s.end() - n, s.end());
}
void xchg(std::string &s, const std::string &l, const std::string &r)
{
  auto ln = std::stoi(l);
  auto rn = std::stoi(r);
  std::iter_swap(s.begin() + ln, s.begin() + rn);
}
void part(std::string &s, const std::string &l, const std::string &r)
{
  auto lpos = s.find(l);
  auto rpos = s.find(r);
  std::iter_swap(s.begin() + lpos, s.begin() + rpos);
}
typedef void (*Op)(std::string &s, const std::string &l, const std::string &r);
int main(int argc, char **argv)
{
  if (argc > 1) {
    std::map<std::string, Op> ops;
    ops.insert(std::pair{ "x", &xchg });
    ops.insert(std::pair{ "p", &part });
    ops.insert(std::pair{ "s", &spin });

    std::ifstream ifs(argv[1]);

    std::vector<std::string> vs;
    std::istream_iterator<std::string> isb(ifs);
    std::istream_iterator<std::string> ise;
    std::copy(isb, ise, std::back_inserter(vs));
    std::string s("abcdefghijklmnop");

    constexpr std::string_view origin = "abcdefghijklmnop";

    auto r = vs | views::chunk(3);
    int n = 1'000'000'000;
    int loopsz = 0;

    for (auto i = 0; i < n; ++i) {
      ranges::for_each(r, [&s, ops](auto range) {
        auto i = ops.find(range[0]);
        (i->second)(s, range[1], range[2]);
      });
      if (s == origin) {
        loopsz = i + 1;
        break;
      }
    }
    int loopcnt = n % loopsz;
    for (auto i = 0; i < loopcnt; ++i) {
      ranges::for_each(r, [&s, ops](auto range) {
        auto i = ops.find(range[0]);
        (i->second)(s, range[1], range[2]);
      });
    }
    std::cout << s << std::endl;
  }
}
