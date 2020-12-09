#include <fstream>
#include <sstream>
#include <string_view>
#include <cctype>
#include <fmt/format.h>
#include <range/v3/all.hpp>
#include <range/v3/algorithm.hpp>
#include <string>
#include <unordered_map>

bool byr(const std::string &s) noexcept
{
  int n = std::stoi(s);
  return (n <= 2002 && n >= 1920);
}
bool iyr(const std::string &s) noexcept
{
  int n = std::stoi(s);
  return (n <= 2020 && n >= 2010);
}
bool eyr(const std::string &s) noexcept
{
  int n = std::stoi(s);
  return (n <= 2030 && n >= 2020);
}
bool hgt(const std::string &str) noexcept
{
  std::istringstream ist(str);
  int n;
  std::string s;
  ist >> n >> s;
  if (s == "cm") {
    return (150 <= n && n <= 193);
  } else if (s == "in") {
    return (59 <= n && n <= 76);
  }
  return false;
}
bool hcl(const std::string &s) noexcept
{
  return s[0] == '#' && s.size() == 7 && ranges::count_if(s, [](char c) { return std::isdigit(c) || ('a' <= c && c <= 'f'); }) == 6;
}
bool ecl(const std::string &s) noexcept
{
  std::array<const char *, 7> eclArray = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
  return ranges::find(eclArray, s) != std::end(eclArray);
}
bool pid(const std::string &s) noexcept
{
  return s.size() == 9 && (ranges::count_if(s, [](char c) { return std::isdigit(c); }) == 9);
}

bool cid(const std::string &) noexcept
{
  return false;
}

int main(int argc, char **argv)
{
  namespace views = ranges::views;
  typedef bool (*Callback)(const std::string &s) noexcept;
  std::unordered_map<std::string, Callback> m;
  m["byr"] = byr;
  m["iyr"] = iyr;
  m["eyr"] = eyr;
  m["hgt"] = hgt;
  m["hcl"] = hcl;
  m["ecl"] = ecl;
  m["pid"] = pid;
  m["cid"] = cid;
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    auto s = ranges::istream<std::string>(ifs);
    int n = 0;
    int count = 0;
    for (auto &&v : s) {
      if (v.starts_with("###")) {
        if (count == 7) {
          ++n;
        }
        count = 0;
      } else {
        count += m[v.substr(0, 3)](v.substr(4));
      }
    }
    fmt::print("{}\n", n);

    return 0;
  }
}
