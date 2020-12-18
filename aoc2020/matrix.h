// Program to test slices and a simple N*M matrix class

// pp 670-674 and 683-684

// No guarantees offered. Constructive comments to bs@research.att.com

#include <iostream>
#include <valarray>
#include <algorithm>
#include <numeric>// for inner_product
#include <iterator>
#include <cstddef>
#include <fmt/format.h>
#include <execution>
// using namespace std;

// forward declarations to allow friend declarations:
template<class T>
class Slice_iter;
template<class T>
bool operator==(const Slice_iter<T> &, const Slice_iter<T> &);
template<class T>
bool operator!=(const Slice_iter<T> &, const Slice_iter<T> &);
template<class T>
bool operator<(const Slice_iter<T> &, const Slice_iter<T> &);

template<class T>
class Slice_iter
{

  std::valarray<T> *v = nullptr;
  std::slice s;
  int curr = 0;// index of current element

  T &ref(int i) const { return (*v)[s.start() + static_cast<std::size_t>(i) * s.stride()]; }

public:
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;
  using reference = T &;
  using pointer_type = T *;
  Slice_iter(std::valarray<T> *vv, std::slice ss) : v(vv), s(ss), curr(0) {}
  Slice_iter() {}

  Slice_iter begin() const
  {
    Slice_iter t = *this;
    t.curr = 0;// index of last-plus-one element
    return t;
  }
  constexpr auto size() const noexcept
  {
    return s.size();
  }

  Slice_iter end() const
  {
    Slice_iter t = *this;
    t.curr = static_cast<int>(s.size());// index of last-plus-one element
    return t;
  }

  Slice_iter &operator++()
  {
    curr++;
    return *this;
  }
  Slice_iter operator++(int)
  {
    Slice_iter t = *this;
    curr++;
    return t;
  }
  Slice_iter &operator--()
  {
    curr--;
    return *this;
  }
  Slice_iter operator--(int)
  {
    Slice_iter t = *this;
    curr--;
    return t;
  }
  Slice_iter &operator+=(int n)
  {
    curr += n;
    return *this;
  }
  Slice_iter &operator-=(int n)
  {
    curr -= n;
    return *this;
  }
  Slice_iter operator+(int n) const
  {
    Slice_iter tmp(*this);
    tmp += n;
    return tmp;
  }
  friend Slice_iter operator+(int n, Slice_iter i)
  {
    return i + n;
  }

  Slice_iter operator-(int n) const
  {
    Slice_iter tmp(*this);
    tmp -= n;
    return tmp;
  }
  difference_type operator-(Slice_iter j) const
  {
    return this->curr - j.curr;
  }

  T &operator[](int i) { return ref(i); }// C style subscript
  T &operator()(int i) { return ref(i); }// Fortran-style subscript
  T &operator*() { return ref(curr); }// current element
  const T &operator[](int i) const { return ref(i); }// C style subscript
  const T &operator()(int i) const { return ref(i); }// Fortran-style subscript
  const T &operator*() const { return ref(curr); }// current element

  friend bool operator==(const Slice_iter &p, const Slice_iter &q)
  {
    return p.curr == q.curr && p.s.stride() == q.s.stride() && p.s.start() == q.s.start();
  }

  friend bool operator!=(const Slice_iter &p, const Slice_iter &q)
  {
    return !(p == q);
  }

  friend bool operator<(const Slice_iter &p, const Slice_iter &q)
  {
    return p.curr < q.curr && p.s.stride() == q.s.stride() && p.s.start() == q.s.start();
  }
};

//-------------------------------------------------------------

// forward declarations to allow friend declarations:
//template<class T>
//class Cslice_iter;
//template<class T>
//bool operator==(const Cslice_iter<T> &, const Cslice_iter<T> &);
//template<class T>
//bool operator!=(const Cslice_iter<T> &, const Cslice_iter<T> &);
//template<class T>
//bool operator<(const Cslice_iter<T> &, const Cslice_iter<T> &);

template<class T>
class Cslice_iter
{
  const std::valarray<T> *v = nullptr;
  std::slice s;
  int curr = 0;// index of current element
  const T &ref(int i) const { return (*v)[s.start() + static_cast<std::size_t>(i) * s.stride()]; }

public:
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;
  using reference = const T &;
  using pointer_type = const T *;
  Cslice_iter(const std::valarray<T> *vv, std::slice ss) : v(vv), s(ss), curr(0) {}
  Cslice_iter() {}
  Cslice_iter end() const
  {
    Cslice_iter t = *this;
    t.curr = static_cast<int>(s.size());// index of one plus last element
    return t;
  }
  Cslice_iter begin() const
  {
    Cslice_iter t = *this;
    t.curr = 0;// index of one plus last element
    return t;
  }
  Cslice_iter &operator++()
  {
    curr++;
    return *this;
  }
  Cslice_iter operator++(int)
  {
    Cslice_iter t = *this;
    curr++;
    return t;
  }
  Cslice_iter &operator--()
  {
    curr--;
    return *this;
  }
  Cslice_iter operator--(int)
  {
    Cslice_iter t = *this;
    curr--;
    return t;
  }
  Cslice_iter &operator+=(int n)
  {
    curr += n;
    return *this;
  }
  Cslice_iter &operator-=(int n)
  {
    curr -= n;
    return *this;
  }
  Cslice_iter operator+(int n) const
  {
    Cslice_iter tmp(*this);
    tmp += n;
    return tmp;
  }
  friend Cslice_iter operator+(int n, Cslice_iter i)
  {
    return i + n;
  }

  Cslice_iter operator-(int n) const
  {
    Cslice_iter tmp(*this);
    tmp -= n;
    return tmp;
  }
  difference_type operator-(Cslice_iter j) const
  {
    return this->curr
           - j.curr;
  }

  const T &operator[](int i) const { return ref(i); }
  const T &operator()(int i) const { return ref(i); }
  const T &operator*() const { return ref(curr); }

  friend bool operator==(const Cslice_iter &p, const Cslice_iter &q)
  {
    return p.curr == q.curr && p.s.stride() == q.s.stride() && p.s.start() == q.s.start();
  }

  friend bool operator!=(const Cslice_iter &p, const Cslice_iter &q)
  {
    return !(p == q);
  }

  friend bool operator<(const Cslice_iter &p, const Cslice_iter &q)
  {
    return p.curr < q.curr && p.s.stride() == q.s.stride() && p.s.start() == q.s.start();
  }
};


//-------------------------------------------------------------

template<class T, int rownum_, int colnum_ = rownum_, class Plus = std::plus<>, class Mul = std::multiplies<>>
class FixedMatrix
{
  static inline constexpr T innerProductValue = T{};
  std::valarray<T> v;// stores elements by column as described in 22.4.5
  //std::size_t colnum_ = 0, rownum_ = 0;// colnum_ == number of cols, rownum_ == number of rows
  Plus plus;
  Mul multiplies;

public:
  std::size_t size() const { return colnum_ * rownum_; }
  int colCount() const { return colnum_; }
  int rowCount() const { return rownum_; }

  Slice_iter<T> operator()(int i) { return row(i); }
  Cslice_iter<T> operator()(int i) const { return row(i); }

  Slice_iter<T> operator[](int i) { return row(i); }// C-style subscript
  Cslice_iter<T> operator[](int i) const { return row(i); }


  std::valarray<T> &array() { return v; }
  const std::valarray<T> &array() const { return v; }
  inline Slice_iter<T> row(int i) { return Slice_iter<T>(&v, std::slice(static_cast<std::size_t>(i), colnum_, rownum_)); }

  inline Cslice_iter<T> row(int i) const { return Cslice_iter<T>(&v, std::slice(static_cast<std::size_t>(i), colnum_, rownum_)); }

  inline Slice_iter<T> column(int i) { return Slice_iter<T>(&v, std::slice(i * rownum_, rownum_, 1)); }

  inline Cslice_iter<T> column(int i) const { return Cslice_iter<T>(&v, std::slice(i * rownum_, rownum_, 1)); }

  FixedMatrix() : v(innerProductValue, rownum_ * colnum_) {}
  bool operator==(FixedMatrix r) const noexcept
  {
    return std::equal(std::execution::par_unseq, std::begin(v), std::end(v), std::begin(r.v));
  }
  bool operator!=(FixedMatrix r) const noexcept
  {
    return !(*this == r);
  }

  T &operator()(int x, int y) { return row(x)[y]; }
  const T &operator()(int x, int y) const { return row(x)[y]; }

  //-------------------------------------------------------------


  std::valarray<T> operator*(const std::valarray<T> &vec) const
  {
    if (colCount() != vec.size()) std::cerr << "wrong number of elements in m*vec\n";

    std::valarray<T> res(rowCount());
    for (std::size_t i = 0; i < rowCount(); i++) {
      res[i] = std::transform_reduce(std::execution::par_unseq, row(i).begin(), row(i).end(), &vec[0], innerProductValue, plus, multiplies);
    }
    return res;
  }

  // alternative definition of m*v


  friend std::valarray<T> operator*(std::valarray<T> &vec, const FixedMatrix &m)
  {
    if (vec.size() != m.rowCount()) std::cerr << "wrong number of elements in vec*m\n";

    std::valarray<T> res(m.colCount());

    for (std::size_t i = 0; i < m.colCount(); i++) {
      const Cslice_iter<T> &ci = m.column(i);
      res[i] = std::transform_reduce(std::execution::par_unseq, ci, ci.end(), &vec[0], innerProductValue, m.plus, m.multiplies);
    }
    return res;
  }
  FixedMatrix operator*(const FixedMatrix &m) const
  {
    FixedMatrix r(rowCount(), m.colCount());
    for (int i = 0; i < rowCount(); i++) {
      for (int j = 0; j < colCount(); j++) {
        r(i, j) = std::transform_reduce(std::execution::par_unseq, row(i).begin(), row(i).end(), m.column(j).begin(), innerProductValue, plus, multiplies);
        fmt::format("{},", r(i, j));
      }
      fmt::format("\n");
    }
    return r;
  }
  FixedMatrix &operator*=(const FixedMatrix &m)
  {
    return *this = (*this) * m;
  }
  void clearslope()
  {

    for (int i = 0; i < rowCount(); i++) {
      (*this)(i, i) = innerProductValue;
    }
  }
  FixedMatrix reverse() const
  {
    FixedMatrix tmp(rownum_, colnum_);
    for (int i = 0; i < rowCount(); ++i) {
      for (int j = 0; j < colCount(); ++j) {
        tmp(j, i) = (*this)(i, j);
      }
    }
    return tmp;
  }

  FixedMatrix &operator*=(T d)
  {
    std::for_each(std::execution::par_unseq, std::begin(v), std::end(v), [this, d](auto &n) { n = this->multiplies(n, d); });
    return *this;
  }
  FixedMatrix operator*(T d) const
  {
    T tmp(*this);
    tmp *= d;
    return tmp;
  }
  friend FixedMatrix operator*(T d, const FixedMatrix &m)
  {
    return m * d;
  }
  friend std::ostream &operator<<(std::ostream &os, const FixedMatrix &m)
  {
    for (std::size_t y = 0; y < m.rowCount(); y++) {
      for (std::size_t x = 0; x < m.colCount(); x++) {
        os << m(y, x) << ",";
      }
      os << "\n";
    }
    return os;
  }
};
template<class T, class Plus = std::plus<>, class Mul = std::multiplies<>>
class Matrix
{
  static inline constexpr T innerProductValue = T{};
  std::valarray<T> v;// stores elements by column as described in 22.4.5
  int colnum_ = 0, rownum_ = 0;// colnum_ == number of cols, rownum_ == number of rows
  Plus plus;
  Mul multiplies;

public:
  std::size_t size() const { return static_cast<std::size_t>(colnum_ * rownum_); }
  int colCount() const { return colnum_; }
  int rowCount() const { return rownum_; }

  Slice_iter<T> operator()(int i) { return row(i); }
  Cslice_iter<T> operator()(int i) const { return row(i); }

  Slice_iter<T> operator[](int i) { return row(i); }// C-style subscript
  Cslice_iter<T> operator[](int i) const { return row(i); }


  std::valarray<T> &array() { return v; }
  const std::valarray<T> &array() const { return v; }
  inline Slice_iter<T> row(int i) { return Slice_iter<T>(&v, std::slice(static_cast<std::size_t>(i), static_cast<std::size_t>(colnum_), static_cast<std::size_t>(rownum_))); }


  inline Cslice_iter<T> row(int i) const { return Cslice_iter<T>(&v, std::slice(static_cast<std::size_t>(i), static_cast<std::size_t>(colnum_), static_cast<std::size_t>(rownum_))); }

  inline Slice_iter<T> column(int i) { return Slice_iter<T>(&v, std::slice(static_cast<std::size_t>(i) * static_cast<std::size_t>(rownum_), static_cast<std::size_t>(rownum_), 1)); }

  inline Cslice_iter<T> column(int i) const { return Cslice_iter<T>(&v, std::slice(static_cast<std::size_t>(i) * static_cast<std::size_t>(rownum_), static_cast<std::size_t>(rownum_), 1)); }

  Matrix() {}
  Matrix(int x, int y) : v(innerProductValue, static_cast<std::size_t>(x * y))
  {
    // check that x and y are sensible
    rownum_ = x;
    colnum_ = y;
  }


  T &operator()(int x, int y) { return row(x)[y]; }
  const T &operator()(int x, int y) const { return row(x)[y]; }

  //-------------------------------------------------------------


  std::valarray<T> operator*(const std::valarray<T> &vec) const
  {
    if (colCount() != vec.size()) std::cerr << "wrong number of elements in m*vec\n";

    std::valarray<T> res(rowCount());
    for (std::size_t i = 0; i < rowCount(); i++) {
      res[i] = std::transform_reduce(std::execution::par_unseq, row(i).begin(), row(i).end(), &vec[0], innerProductValue, plus, multiplies);
    }
    return res;
  }

  // alternative definition of m*v


  friend std::valarray<T> operator*(std::valarray<T> &vec, const Matrix &m)
  {
    if (vec.size() != m.rowCount()) std::cerr << "wrong number of elements in vec*m\n";

    std::valarray<T> res(m.colCount());

    for (std::size_t i = 0; i < m.colCount(); i++) {
      const Cslice_iter<T> &ci = m.column(i);
      res[i] = std::transform_reduce(std::execution::par_unseq, ci, ci.end(), &vec[0], innerProductValue, m.plus, m.multiplies);
    }
    return res;
  }
  Matrix operator*(const Matrix &m) const
  {
    Matrix r(rowCount(), m.colCount());
    for (int i = 0; i < rowCount(); i++) {
      for (int j = 0; j < colCount(); j++) {
        r(i, j) = std::transform_reduce(std::execution::par_unseq, row(i).begin(), row(i).end(), m.column(j).begin(), innerProductValue, plus, multiplies);
        fmt::format("{},", r(i, j));
      }
      fmt::format("\n");
    }
    return r;
  }
  Matrix &operator*=(const Matrix &m)
  {
    return *this = (*this) * m;
  }
  void clearslope()
  {

    for (int i = 0; i < rowCount(); i++) {
      (*this)(i, i) = innerProductValue;
    }
  }
  Matrix reverse() const
  {
    Matrix tmp(rownum_, colnum_);
    for (int i = 0; i < rowCount(); ++i) {
      for (int j = 0; j < colCount(); ++j) {
        tmp(j, i) = (*this)(i, j);
      }
    }
    return tmp;
  }

  Matrix &operator*=(T d)
  {
    std::for_each(std::execution::par_unseq, std::begin(v), std::end(v), [this, d](auto &n) { n = this->multiplies(n, d); });
    return *this;
  }
  Matrix operator*(T d) const
  {
    T tmp(*this);
    tmp *= d;
    return tmp;
  }
  friend Matrix operator*(T d, const Matrix &m)
  {
    return m * d;
  }
  friend std::ostream &operator<<(std::ostream &os, const Matrix &m)
  {
    for (auto y = 0; y < m.rowCount(); y++) {
      for (auto x = 0; x < m.colCount(); x++) os << m(y, x) << "\t";
      os << "\n";
    }
    return os;
  }
};
template<class T>
std::ostream &operator<<(std::ostream &os, const std::valarray<T> &v)
{
  for (std::size_t i = 0; i < v.size(); ++i) os << v[i] << '\t';
  return os;
}
