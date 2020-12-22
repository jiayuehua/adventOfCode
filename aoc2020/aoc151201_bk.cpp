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


template<typename OpTag>
struct binary_op;
typedef boost::variant<unsigned short,
  boost::recursive_wrapper<binary_op<And>>,
  boost::recursive_wrapper<binary_op<Or>>,
  boost::recursive_wrapper<binary_op<Lshift>>,
  boost::recursive_wrapper<binary_op<Rshift>>,
  boost::recursive_wrapper<binary_op<Not>>>
  Expr;
typedef std::unordered_map<std::string, Expr> ExprMap;
template<typename OpTag>
struct binary_op
{
  Expr left;
  Expr right;

  binary_op(const Expr &lhs, const Expr &rhs)
    : left(lhs), right(rhs)
  {
  }
  binary_op() {}
};
template<class IntType>
class Calculator : public boost::static_visitor<IntType>
{
public:
  using value_type = IntType;
  IntType operator()(IntType value) const
  {
    return value;
  }

  IntType operator()(const binary_op<And> &binary) const
  {
    return boost::apply_visitor(Calculator(), binary.left)
           & boost::apply_visitor(Calculator(), binary.right);
  }

  IntType operator()(const binary_op<Or> &binary) const
  {
    return boost::apply_visitor(Calculator(), binary.left)
           | boost::apply_visitor(Calculator(), binary.right);
  }
  IntType operator()(const binary_op<Lshift> &binary) const
  {
    return boost::apply_visitor(Calculator(), binary.left)
           << boost::apply_visitor(Calculator(), binary.right);
  }
  IntType operator()(const binary_op<Rshift> &binary) const
  {
    return boost::apply_visitor(Calculator(), binary.left)
           >> boost::apply_visitor(Calculator(), binary.right);
  }
  IntType operator()(const binary_op<Not> &binary) const
  {
    return ~(boost::apply_visitor(Calculator(), binary.left));
  }
};
using AocCal = Calculator<unsigned short>;
struct IS
{
  AocCal c_;
  ExprMap exprmap_;
  AocCal::value_type operator()(const std::string &s) const
  {
    if (auto i = exprmap_.find(s); i != exprmap_.end()) {
      AocCal::value_type r = boost::apply_visitor(c_, i->second);
      return r;
    } else {
      return 0;
    }
  }
};

int main(int argc, char **argv)
{
  Expr e;
  e = 32;

  if (argc > 1) {
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
          asms.exprmap_[v[2]] = n;
        } else {
          asms.exprmap_[v[2]] = asms.exprmap_[v[0]];
        }
      } else if (v.size() == 4) {
        asms.exprmap_[v[3]] = binary_op<Not>(asms.exprmap_[v[1]], asms.exprmap_[v[1]]);
      } else if (v.size() == 5) {
        if (v[1] == "OR") {
          asms.exprmap_[v[4]] = binary_op<Or>(asms.exprmap_[v[0]], asms.exprmap_[v[2]]);
        } else if (v[1] == "AND") {
          asms.exprmap_[v[4]] = binary_op<And>(asms.exprmap_[v[0]], asms.exprmap_[v[2]]);
        } else if (v[1] == "LSHIFT") {
          asms.exprmap_[v[4]] = binary_op<Lshift>(asms.exprmap_[v[0]], std::stoi(v[2]));
        } else if (v[1] == "RSHIFT") {
          asms.exprmap_[v[4]] = binary_op<Rshift>(asms.exprmap_[v[0]], std::stoi(v[2]));
        }
      }
    }
    std::cout << asms("d") << std::endl;
    std::cout << asms("e") << std::endl;
    std::cout << asms("f") << std::endl;
    std::cout << asms("g") << std::endl;
    std::cout << asms("h") << std::endl;
    std::cout << asms("i") << std::endl;
    std::cout << asms("x") << std::endl;
    std::cout << asms("y") << std::endl;
  }
}
