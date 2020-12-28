#include <range/v3/all.hpp>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <fmt/format.h>
#include <optional>
#include <cstdio>
#include <numeric>
#include <string>
#include <execution>
#include <cx_md5.h>

namespace views = ranges::views;

int main(int argc, char **argv)
{
  fmt::print("world\n");
  auto v = views::ints | views::transform([](int i) {
    auto sum = cx::md5_new(("yzbqklnj" + std::to_string(i)).c_str());
    const uint8_t *m = reinterpret_cast<const uint8_t *>(sum.h);
    std::string sumstr;
    std::ostringstream ost(sumstr);
    ost << std::hex << std::setfill('0');
    for (size_t i = 0; i < sizeof(sum.h); ++i) {
      ost << std::setw(2) << +m[i];
    }
    return std::pair{ ost.str().substr(0, 6) == "000000", i };
  });
  auto it = ranges::find_if(v, [](auto p) { return p.first == true; });
  fmt::print("{}\n", (*it).second);
}