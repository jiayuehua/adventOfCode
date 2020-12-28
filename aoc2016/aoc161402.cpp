#include <range/v3/all.hpp>
#include <fstream>
#include <sstream>
#include <iterator>
#include <fmt/format.h>
#include <numeric>
#include <string>
#include <execution>
#include <cx_md5.h>
#include <vector>
#include <functional>
#include <iomanip>

namespace views = ranges::views;


int main(int argc, char **argv)
{
  //constexpr int N = 1024 * 1024;
  constexpr int N = 32 * 8 * 1024;
  constexpr int Total = N + 1000;
  std::vector<int> v(Total);
  std::vector<std::pair<std::string, int>> vs(Total);
  //auto values = views::iota(N + 1000) | views::common;
  //int N = 1;
  //std::vector<int> v(N);
  //std::vector<std::pair<std::string, int>> vs(N);
  auto values = views::ints | views::take(Total) | views::common;
  v.assign(values.begin(), values.end());
  std::transform(std::execution::par_unseq, v.begin(), v.end(), vs.begin(), [](int k) {
    std::string str = ("cuanljph" + std::to_string(k));
    //std::string str = ("abc" + std::to_string(k));
    for (int j = 0; j < 2017; ++j) {

      auto sum = cx::md5_new(str.c_str());

      const uint8_t *m = reinterpret_cast<const uint8_t *>(sum.h);
      std::string sumstr;
      std::ostringstream ost(sumstr);
      ost << std::hex << std::setfill('0');
      for (size_t i = 0; i < sizeof(sum.h); ++i) {
        ost << std::setw(2) << +m[i];
      }
      str = ost.str();
      sumstr.clear();
    }

    return std::pair{ str, k };
  });
  //for (int i = 0; i < 10; ++i) {
  //  fmt::print("{},{};", vs[i].second, vs[i].first);
  //}
  //fmt::print("$\n");
  //return 0;


  auto valid = [&vs](auto p) {
    auto s = p.first | views::sliding(3) | views::transform([p](auto v) { 
      auto uniq=ranges::adjacent_find(v, std::not_equal_to{}) == v.end();
  //    if (uniq) {
  //fmt::print("s3:{}\n", p.first);
  //    }

      return std::make_pair(uniq, v[0]); }) | views::filter([](auto pair) { return pair.first; }) | views::values;
    std::string str(s.begin(), s.end());
    auto r = std::move(str) | ranges::actions::sort | ranges::actions::unique;
    for (auto c : r) {
      auto correct = std::transform_reduce(std::execution::par_unseq, vs.begin() + p.second + 1, vs.begin() + p.second + 1000 + 1, 0, std::plus{}, [c, p](const auto &s5p) {
        auto s5 = s5p.first | views::sliding(5) | views::transform([c](auto v) { return ranges::count(v, c) == 5; }) | views::filter([](auto pair) { return pair; });

        //if (!s5.empty()) {
        //  fmt::print("s5:{}\n", s5p.first);
        //  fmt::print("s3:{},{}\n", p.first, p.second);
        //}
        return !s5.empty();
      });

      if (correct) {
        return true;
      }
    }
    return false;
  };
  auto validindexs = vs | views::take(N) | views::filter(valid) | views::take(65) | views::drop(64);
  for (auto b : validindexs) {
    fmt::print("{},{}\n", b.first, b.second);
  }
}