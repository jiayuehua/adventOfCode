#include <fstream>
#include <sstream>
#include <fmt/format.h>
#include <string>
#include <cstdint>
#include <vector>
#include <range/v3/algorithm/sort.hpp>
#include <range/v3/algorithm/count.hpp>
#include <range/v3/view.hpp>
template<class Range>
bool istriangle(Range r) noexcept
{
  auto v = r.begin();
  if (v[0] + v[1] <= v[2]) {
    return false;
  }
  if (v[1] + v[2] <= v[0]) {
    return false;
  }
  if (v[0] + v[2] <= v[1]) {
    return false;
  }
  return true;
}

namespace views = ranges::views;
int Count(const std::vector<int> &v)
{
  auto r = v | views::chunk(3) | views::transform([](auto chunk) {
    return istriangle(chunk);
  });
  return ranges::count(r, true);
}


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::string s;
    std::int64_t n = 0;
    std::vector<int> va;
    std::vector<int> vb;
    std::vector<int> vc;
    while (std::getline(ifs, s)) {
      int a, b, c;
      std::istringstream iss(s);
      iss >> a >> b >> c;
      va.push_back(a);
      vb.push_back(b);
      vc.push_back(c);
    }
    n = Count(va) + Count(vb) + Count(vc);
    fmt::print("triangle count:{}\n", n);
  }
}