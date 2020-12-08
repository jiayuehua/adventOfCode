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
// Flattens a range of ranges by iterating the inner
// ranges in round-robin fashion.
using namespace ranges;
namespace views = ranges::views;
template<class Rngs>
class interleave_view : public view_facade<interleave_view<Rngs>>
{
  friend range_access;
  std::vector<range_value_t<Rngs>> rngs_;
  struct cursor;
  cursor begin_cursor()
  {
    return { 0, &rngs_, views::transform(rngs_, ranges::begin) | to<std::vector> };
  }

public:
  interleave_view() = default;
  explicit interleave_view(Rngs rngs)
    : rngs_(std::move(rngs) | to<std::vector>)
  {}
};

template<class Rngs>
struct interleave_view<Rngs>::cursor
{
  std::size_t n_;
  std::vector<range_value_t<Rngs>> *rngs_;
  std::vector<iterator_t<range_value_t<Rngs>>> its_;
  decltype(auto) read() const
  {
    return *its_[n_];
  }
  void next()
  {
    if (0 == ((++n_) %= its_.size()))
      for_each(its_, [](auto &it) { ++it; });
  }
  bool equal(default_sentinel_t) const
  {
    if (n_ != 0)
      return false;
    auto ends = *rngs_ | views::transform(ranges::end);
    return its_.end() != std::mismatch(its_.begin(), its_.end(), ends.begin(), std::not_equal_to<>{}).first;
  }
  CPP_member auto equal(cursor const &that) const -> CPP_ret(bool)(
    requires forward_range<range_value_t<Rngs>>)
  {
    return n_ == that.n_ && its_ == that.its_;
  }
};

// In:  range<range<T>>
// Out: range<T>, flattened by walking the ranges
//                round-robin fashion.
auto interleave()
{
  return make_view_closure([](auto &&rngs) {
    using Rngs = decltype(rngs);
    return interleave_view<views::all_t<Rngs>>(
      views::all(std::forward<Rngs>(rngs)));
  });
}
auto transpose()
{
  return make_view_closure([](auto &&rngs) {
    using Rngs = decltype(rngs);
    CPP_assert(forward_range<Rngs>);
    return std::forward<Rngs>(rngs)
           | interleave()
           | views::chunk(static_cast<std::size_t>(distance(rngs)));
  });
}


int main(int argc, char **argv)
{
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    std::vector<std::string> v;
    v.reserve(1000);
    std::istream_iterator<std::string> ib(ifs);
    std::istream_iterator<std::string> ie;
    std::move(ib, ie, std::back_inserter(v));
    auto gszs = v | views::split(std::string("###"))
                | views::transform([](auto &&g) {
                    auto min = [](int l, int r) { return std::min(l, r); };
                    auto size = [](std::string_view sv) { return sv.size(); };
                    std::vector<int> vsz;
                    ranges::transform(g, std::back_inserter(vsz), [](std::string_view sv) { return sv.size(); });
                    int sz = *ranges::min_element(vsz);
                    fmt::print("{}-", sz);
                    auto answers = g | transpose() | views::take(sz) | views::transform([](auto sv) {
                      return ranges::adjacent_find(sv, [](char l, char r) { return l != r; }) == sv.end();
                    });
                    int cnt = ranges::count(answers, true);
                    fmt::print("{}\n", cnt);
                    return cnt;
                  });
    auto n = std::reduce(gszs.begin(), gszs.end(), 0);
    fmt::print("{}\n", n);
  }
}