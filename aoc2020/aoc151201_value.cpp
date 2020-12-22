#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fmt/format.h>
#include <string>
#include <iomanip>
#include <boost/variant.hpp>
#include <unordered_map>

struct Not
{
};
struct And
{
};
struct Or
{
};
struct Lshift
{
};
struct Rshift
{
};
struct Assign
{
};


template<typename OpTag>
struct binary_op;
template<typename OpTag>
struct unary_op;
typedef boost::variant<unsigned short,
  boost::recursive_wrapper<binary_op<And>>,
  boost::recursive_wrapper<binary_op<Or>>,
  boost::recursive_wrapper<binary_op<Lshift>>,
  boost::recursive_wrapper<binary_op<Rshift>>,
  boost::recursive_wrapper<binary_op<Assign>>,
  boost::recursive_wrapper<binary_op<Not>>>
  Expr;
typedef std::unordered_map<std::string, Expr> ExprMap;
struct Op
{
  std::string leftname;
  std::string rightname;
  Expr left;
  Expr right;
};
template<typename OpTag>
struct binary_op : Op
{
};
template<class IntType>
class Calculator : public boost::static_visitor<IntType>
{
  IntType getleft(const Op &binary) const
  {

    value_type l = 0;
    if (!binary.leftname.empty()) {

      if (auto i = tokentable.find(binary.leftname); i != tokentable.end()) {
        l = i->second;
      }
      if (auto i = m.find(binary.leftname); i != m.end()) {
        l = boost::apply_visitor(*this, i->second);
        tokentable[binary.leftname] = l;
      }
    } else {
      l = boost::apply_visitor(*this, binary.left);
    }
    return l;
  }
  IntType getright(const Op &binary) const
  {
    value_type l = 0;
    if (!binary.rightname.empty()) {
      if (auto i = tokentable.find(binary.leftname); i != tokentable.end()) {
        l = i->second;
      }
      if (auto i = m.find(binary.rightname); i != m.end()) {
        l = boost::apply_visitor(*this, i->second);
        tokentable[binary.rightname] = l;
      }
    } else {
      l = boost::apply_visitor(*this, binary.right);
    }
    return l;
  }

  mutable std::map<std::string, unsigned short> tokentable;

public:
  mutable ExprMap m;
  using value_type = IntType;
  IntType operator()(IntType value) const
  {
    fmt::print("value:\n ");
    return value;
  }

  IntType operator()(const binary_op<And> &binary) const
  {
    return getleft(binary)
           & getright(binary);
  }

  IntType operator()(const binary_op<Or> &binary) const
  {
    return getleft(binary)
           | getright(binary);
  }
  IntType operator()(const binary_op<Lshift> &binary) const
  {
    return getleft(binary)
           << getright(binary);
  }
  IntType operator()(const binary_op<Rshift> &binary) const
  {
    return getleft(binary)
           >> getright(binary);
  }
  IntType operator()(const binary_op<Not> &binary) const
  {
    return ~(getleft(binary));
  }
  IntType operator()(const binary_op<Assign> &binary) const
  {
    return getleft(binary);
  }
};
using AocCal = Calculator<unsigned short>;
struct IS
{
  AocCal c_;

  AocCal::value_type operator()(const std::string &s) const
  {
    std::cout << std::endl;
    if (auto i = c_.m.find(s); i != c_.m.end()) {
      AocCal::value_type r = boost::apply_visitor(c_, i->second);
      return r;
    } else {
      return 0;
    }
  }
};

int main(int argc, char **argv)
{

  if (argc > 2) {
    std::ifstream ifs(argv[1]);
    std::string line;
    IS asms;
    while (std::getline(ifs, line)) {
      std::istringstream iss(line);
      std::vector<std::string> v;
      std::istream_iterator<std::string> b(iss);
      std::istream_iterator<std::string> e;
      std::copy(b, e, std::back_inserter(v));
      if (v.size() == 3) {
        if (std::isdigit(v[0][0])) {
          auto n = static_cast<unsigned short>(std::stoi(v[0]));
          asms.c_.m[v[2]] = n;
        } else {
          asms.c_.m[v[2]] = binary_op<Assign>{ v[0] };
          asms.c_.m[v[0]];
        }
      } else if (v.size() == 4) {
        asms.c_.m[v[3]] = binary_op<Not>{ v[1] };
        asms.c_.m[v[1]];
      } else if (v.size() == 5) {
        if (v[1] == "OR") {
          asms.c_.m[v[4]] = binary_op<Or>{ v[0], v[2] };
          asms.c_.m[v[0]];
          asms.c_.m[v[2]];
        } else if (v[1] == "AND") {
          asms.c_.m[v[4]] = binary_op<And>{ v[0], v[2] };
          asms.c_.m[v[0]];
          asms.c_.m[v[2]];
        } else if (v[1] == "LSHIFT") {
          binary_op<Lshift> binop{ v[0] };
          asms.c_.m[v[0]];

          binop.right = std::stoi(v[2]);
          asms.c_.m[v[4]] = binop;
        } else if (v[1] == "RSHIFT") {
          binary_op<Rshift> binop{ v[0] };
          asms.c_.m[v[0]];
          binop.right = std::stoi(v[2]);
          asms.c_.m[v[4]] = binop;
        }
      }
    }
    std::cout << asms(argv[2]) << std::endl;
  }
}
