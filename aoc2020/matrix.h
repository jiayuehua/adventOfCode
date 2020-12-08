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
  std::size_t curr = 0;// index of current element

  T &ref(std::size_t i) const { return (*v)[s.start() + i * s.stride()]; }

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

  Slice_iter end() const
  {
    Slice_iter t = *this;
    t.curr = s.size();// index of last-plus-one element
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
  Slice_iter &operator+=(std::size_t n)
  {
    curr += n;
    return *this;
  }
  Slice_iter &operator-=(std::size_t n)
  {
    curr -= n;
    return *this;
  }
  Slice_iter operator+(std::size_t n) const
  {
    Slice_iter tmp(*this);
    tmp += n;
    return tmp;
  }
  friend Slice_iter operator+(std::size_t n, Slice_iter i)
  {
    return i + n;
  }

  Slice_iter operator-(std::size_t n) const
  {
    Slice_iter tmp(*this);
    tmp -= n;
    return tmp;
  }
  difference_type operator-(Slice_iter j) const
  {
    return this->curr - j.curr;
  }

  T &operator[](std::size_t i) { return ref(i); }// C style subscript
  T &operator()(std::size_t i) { return ref(i); }// Fortran-style subscript
  T &operator*() { return ref(curr); }// current element
  const T &operator[](std::size_t i) const { return ref(i); }// C style subscript
  const T &operator()(std::size_t i) const { return ref(i); }// Fortran-style subscript
  const T &operator*() const { return ref(curr); }// current element

  friend bool operator==<>(const Slice_iter &p, const Slice_iter &q);
  friend bool operator!=<>(const Slice_iter &p, const Slice_iter &q);
  friend bool operator<(const Slice_iter &p, const Slice_iter &q);
};

template<class T>
bool operator==(const Slice_iter<T> &p, const Slice_iter<T> &q)
{
  return p.curr == q.curr && p.s.stride() == q.s.stride() && p.s.start() == q.s.start();
}

template<class T>
bool operator!=(const Slice_iter<T> &p, const Slice_iter<T> &q)
{
  return !(p == q);
}

template<class T>
bool operator<(const Slice_iter<T> &p, const Slice_iter<T> &q)
{
  return p.curr < q.curr && p.s.stride() == q.s.stride() && p.s.start() == q.s.start();
}

//-------------------------------------------------------------

// forward declarations to allow friend declarations:
template<class T>
class Cslice_iter;
template<class T>
bool operator==(const Cslice_iter<T> &, const Cslice_iter<T> &);
template<class T>
bool operator!=(const Cslice_iter<T> &, const Cslice_iter<T> &);
template<class T>
bool operator<(const Cslice_iter<T> &, const Cslice_iter<T> &);

template<class T>
class Cslice_iter
{
  const std::valarray<T> *v = nullptr;
  std::slice s;
  std::size_t curr = 0;// index of current element
  const T &ref(std::size_t i) const { return (*v)[s.start() + i * s.stride()]; }

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
    t.curr = s.size();// index of one plus last element
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
  Cslice_iter &operator+=(std::size_t n)
  {
    curr += n;
    return *this;
  }
  Cslice_iter &operator-=(std::size_t n)
  {
    curr -= n;
    return *this;
  }
  Cslice_iter operator+(std::size_t n) const
  {
    Cslice_iter tmp(*this);
    tmp += n;
    return tmp;
  }
  friend Cslice_iter operator+(std::size_t n, Cslice_iter i)
  {
    return i + n;
  }

  Cslice_iter operator-(std::size_t n) const
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

  const T &operator[](std::size_t i) const { return ref(i); }
  const T &operator()(std::size_t i) const { return ref(i); }
  const T &operator*() const { return ref(curr); }

  friend bool operator==<>(const Cslice_iter &p, const Cslice_iter &q);
  friend bool operator!=<>(const Cslice_iter &p, const Cslice_iter &q);
  friend bool operator<(const Cslice_iter &p, const Cslice_iter &q);
};

template<class T>
bool operator==(const Cslice_iter<T> &p, const Cslice_iter<T> &q)
{
  return p.curr == q.curr && p.s.stride() == q.s.stride() && p.s.start() == q.s.start();
}

template<class T>
bool operator!=(const Cslice_iter<T> &p, const Cslice_iter<T> &q)
{
  return !(p == q);
}

template<class T>
bool operator<(const Cslice_iter<T> &p, const Cslice_iter<T> &q)
{
  return p.curr < q.curr && p.s.stride() == q.s.stride() && p.s.start() == q.s.start();
}

//-------------------------------------------------------------

template<class T, class Plus = std::plus<>, class Mul = std::multiplies<>, T innerProductValue = 0>
class Matrix
{
  std::valarray<T> v;// stores elements by column as described in 22.4.5
  std::size_t d1 = 0, d2 = 0;// d1 == number of rows, d2 == number of columns
  Plus plus;
  Mul multiplies;

public:
  std::size_t size() const { return d1 * d2; }
  std::size_t dim1() const { return d1; }
  std::size_t dim2() const { return d2; }

  Slice_iter<T> operator()(std::size_t i) { return row(i); }
  Cslice_iter<T> operator()(std::size_t i) const { return row(i); }

  Slice_iter<T> operator[](std::size_t i) { return row(i); }// C-style subscript
  Cslice_iter<T> operator[](std::size_t i) const { return row(i); }


  std::valarray<T> &array() { return v; }
  inline Slice_iter<T> row(std::size_t i) { return Slice_iter<T>(&v, std::slice(i, d1, d2)); }

  inline Cslice_iter<T> row(std::size_t i) const { return Cslice_iter<T>(&v, std::slice(i, d1, d2)); }

  inline Slice_iter<T> column(std::size_t i) { return Slice_iter<T>(&v, std::slice(i * d2, d2, 1)); }

  inline Cslice_iter<T> column(std::size_t i) const { return Cslice_iter<T>(&v, std::slice(i * d2, d2, 1)); }

  Matrix() {}
  Matrix(std::size_t x, std::size_t y) : v(innerProductValue, x * y)
  {
    // check that x and y are sensible
    d1 = x;
    d2 = y;
  }


  T &operator()(std::size_t x, std::size_t y) { return row(x)[y]; }
  const T &operator()(std::size_t x, std::size_t y) const { return row(x)[y]; }

  //-------------------------------------------------------------


  std::valarray<T> operator*(const std::valarray<T> &vec) const
  {
    if (dim1() != vec.size()) std::cerr << "wrong number of elements in m*vec\n";

    std::valarray<T> res(dim2());
    for (std::size_t i = 0; i < dim2(); i++) {
      res[i] = std::transform_reduce(std::execution::par_unseq, row(i).begin(), row(i).end(), &vec[0], innerProductValue, plus, multiplies);
    }
    return res;
  }

  // alternative definition of m*v


  //friend std::valarray<T> operator*(std::valarray<T> &vec, const Matrix &m)
  //{
  //  if (vec.size() != m.dim2()) std::cerr << "wrong number of elements in vec*m\n";

  //  std::valarray<T> res(m.dim1());

  //  for (std::size_t i = 0; i < m.dim1(); i++) {
  //    const Cslice_iter<T> &ci = m.column(i);
  //    res[i] = std::transform_reduce(std::execution::par_unseq, ci, ci.end(), &vec[0], innerProductValue, m.plus, m.multiplies);
  //  }
  //  return res;
  //}
  Matrix operator*(const Matrix &m) const
  {
    Matrix r(dim2(), m.dim1());
    for (std::size_t i = 0; i < dim2(); i++) {
      for (std::size_t j = 0; j < dim1(); j++) {
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

    for (std::size_t i = 0; i < dim2(); i++) {
      (*this)(i, i) = innerProductValue;
    }
  }
  Matrix reverse() const
  {
    Matrix tmp(d2, d1);
    for (std::size_t i = 0; i < dim2(); ++i) {
      for (std::size_t j = 0; j < dim1(); ++j) {
        tmp(j, i) = (*this)(i, j);
      }
    }
    return tmp;
  }

  //Matrix &operator*=(T d)
  //{
  //  (v) *= d;
  //  return *this;
  //}
  friend std::ostream &operator<<(std::ostream &os, Matrix &m)
  {
    for (std::size_t y = 0; y < m.dim2(); y++) {
      for (std::size_t x = 0; x < m.dim1(); x++) os << m[x][y] << "\t";
      os << "\n";
    }
    return os;
  }
};
template<class T>
std::ostream &operator<<(std::ostream &os, const std::valarray<T> &v)
{
  for (std::size_t i = 0; i < v.size(); ++i) os << '\t' << v[i];
  return os;
}
