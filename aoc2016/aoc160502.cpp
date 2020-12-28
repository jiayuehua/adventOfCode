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

struct HashResult
{
  bool valid_ = false;
  operator bool() const
  {
    return valid_;
  }
  int pos_ = std::numeric_limits<int>::max();
  int dstpos_ = 8;
  char msg_ = '#';
  HashResult(int pos, const std::string &s) : pos_(pos)
  {
    valid_ = s.substr(0, 5) == "00000" && '0' <= s[5] && s[5] <= '7';
    dstpos_ = s[5] - '0';
    msg_ = s[6];
  }
  HashResult() = default;
  friend auto operator<=>(const HashResult &l, const HashResult &r)
  {
    return l.pos_ <=> r.pos_;
  }
};
struct HashResultArray
{
  static constexpr int Size = 8;
  int validcount_ = 0;
  std::string str() const
  {
    std::string result = ".#.#.#.#";
    ranges::transform(hashresults_, result.begin(), [](const HashResult &h) { return h.msg_; });
    return result;
  }


  operator bool() const
  {
    return validcount_ == Size;
  }
  std::array<HashResult, Size> hashresults_;
  const HashResult &operator[](int i) const
  {
    return hashresults_[i];
  }
  HashResult &operator[](int i)
  {
    return hashresults_[i];
  }
  HashResultArray() = default;
  //HashResultArray(const HashResult &h)
  //HashResultArray(const HashResult &h)
  HashResultArray(int pos, const std::string &s)
  {
    HashResult h(pos, s);
    if (h.valid_) {
      hashresults_[h.dstpos_] = h;
      ++validcount_;
    }
  }
  friend HashResultArray operator+(const HashResultArray &l, const HashResultArray &r)
  {
    HashResultArray t(l);
    for (int i = 0; i < 8; ++i) {
      if (!l[i]) {
        t[i] = r[i];
        t.validcount_ += r[i].valid_;
      } else if (r[i]) {
        t[i] = std::min(l[i], r[i]);
      }
    }
    return t;
  }
};

int main(int argc, char **argv)
{
  fmt::print("world\n");
  std::string s("########");
  int N = 1024 * 1024 * 128;

  HashResultArray init;
  //{

  //  HashResultArray a(0, "000000ABCDEFGHI");
  //  HashResultArray b(1, "000001BC");
  //  init = a + b;
  //  fmt::print("init:{}\n", init.str());
  //  fmt::print("initvalid:{}\n", static_cast<bool>(init));

  //  HashResultArray c(2, "000002CC");
  //  HashResultArray d(3, "000003DC");
  //  HashResultArray e(4, "000004EBCDEFGHI");
  //  HashResultArray f(5, "000005FC");
  //  HashResultArray g(6, "000006GC");
  //  HashResultArray h(7, "000007HC");

  //  init = a + b + c + d + e + f + g + h;
  //  fmt::print("lastvalue:{}\n", init.str());
  //  fmt::print("initvalid:{}\n", static_cast<bool>(init));
  //  return 0;
  //}

  std::vector<int> v(N);
  for (int i = 0; !init; ++i) {
    auto values = views::iota(N * i) | views::take(N) | views::common;
    v.assign(values.begin(), values.end());
    init =
      std::transform_reduce(std::execution::par_unseq, v.begin(), v.end(), init, std::plus{}, [](int i) {
        auto sum = cx::md5_new(("ugkcyxxp" + std::to_string(i)).c_str());
        const uint8_t *m = reinterpret_cast<const uint8_t *>(sum.h);
        std::string sumstr;
        std::ostringstream ost(sumstr);
        ost << std::hex << std::setfill('0');
        for (size_t i = 0; i < sizeof(sum.h); ++i) {
          ost << std::setw(2) << +m[i];
        }
        HashResultArray hasharray(i, ost.str());
        return hasharray;
      });
    fmt::print("init:{}\n", init.str());
  }
  fmt::print("lastvalue:{}\n", init.str());

  //views::transform([&s](int i) {
  //  auto sum = cx::md5_new(("ugkcyxxp" + std::to_string(i)).c_str());
  //  const uint8_t *m = reinterpret_cast<const uint8_t *>(sum.h);
  //  std::string sumstr;
  //  std::ostringstream ost(sumstr);
  //  ost << std::hex << std::setfill('0');
  //  for (size_t i = 0; i < sizeof(sum.h); ++i) {
  //    ost << std::setw(2) << +m[i];
  //  }
  //  char ost5th = ost.str()[5];
  //  char ost6th = ost.str()[6];

  //  bool ca = ost.str().substr(0, 5) == "00000" && '0' <= ost5th && ost5th <= '7' && '#' != s[ost5th - '0'];
  //  if (ca) {
  //    s[ost5th - '0'] = ost6th;
  //  }
  //  return ca;
  //}) | views::filter([](auto one) { return one; })
  //  | views::take(8);
  ////auto it = ranges::find_if(v, [](auto p) { return p.first == true; });
  //for (auto i : v) {
  //  fmt::print("{}", i);
  //}
  //fmt::print("$$\n");
  //fmt::print("{}\n", s);
}