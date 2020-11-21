module;
#include <range/v3/all.hpp>
module game24;
import std.core;
// import<algorithm>;
// import<string>;
// import<vector>;
namespace
{
std::vector<std::vector<std::string>> getAllPerms(std::vector<std::string> v)
{
  std::vector<std::vector<std::string>> r;
  r.push_back(v);
  while (std::next_permutation(v.begin(), v.end())) {
    r.push_back(v);
  }
  return r;
}
template <class I>
std::vector<std::string> generateExprs(I b, I e)
{
  int                      n = e - b;
  std::vector<std::string> v;
  v.reserve(24);
  if (n == 0) {
    v.push_back(std::string{});
    return v;
  } else if (n == 1) {
    v.push_back(std::string("") + *b + std::string(""));
    return v;
  } else {
    ranges::for_each(ranges::views::ints | ranges::views::drop(1) | ranges::views::take(n - 1), [b, e, &v](int i) {
      auto l = generateExprs(b, b + i);
      auto r = generateExprs(b + i, e);
      ranges::for_each(l, [&v, &r](auto&& li) {
        ranges::for_each(r, [&li, &v](auto&& ri) {
          std::string s = std::string("(") + li + std::string("+") + ri + ")";
          v.push_back(s);
          s = std::string("(") + li + std::string("-") + ri + ")";
          v.push_back(s);
          s = std::string("(") + li + std::string("*") + ri + ")";
          v.push_back(s);
          s = std::string("(") + li + std::string("/") + ri + ")";
          v.push_back(s);
        });
      });
    });
    return v;
  }
}
}  // namespace
std::vector<std::string> getAllexprs(const std::vector<std::string>& v)
{
  std::vector<std::string> r;
  auto                     all = getAllPerms(v);
  ranges::for_each(all, [&r](auto&& i) {
    auto pairs = generateExprs(i.begin(), i.end());
    r.insert(r.end(), pairs.begin(), pairs.end());
  });
  return r;
}
