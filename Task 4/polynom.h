// polynom.h
#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>
#include <string>
#include <algorithm>
#include <ostream>

template <class T>
class Polynom
{
public:
  Polynom(std::vector<T> coeffs = {}) : _coeffs(coeffs){};

  std::string to_string() const;
  T eval(T) const;
  T coeff(size_t i) const;
  int deg() const;

  T operator()(const T &t) const;

  std::vector<T> coeffs() const;

private:
  std::vector<T> _coeffs;
};

template <class T>
std::vector<T> Polynom<T>::coeffs() const
{
  return _coeffs;
}

template <class T>
T Polynom<T>::operator()(const T &t) const
{
  return eval(t);
}

template <class R, class S, class T>
Polynom<R> operator+(const Polynom<S> &p1, const Polynom<T> &p2)
{
  // ? TODO: optimize ?
  int maxndeg = std::max(p1.deg(), p2.deg());
  std::vector<R> ncoeffs(maxndeg + 1);
  for (int i = 0; i <= maxndeg; ++i)
    ncoeffs[i] = p1.coeff(i) + p2.coeff(i);
  while (!ncoeffs.empty() && !ncoeffs.back())
    ncoeffs.pop_back();
  return Polynom<R>{ncoeffs};
}
template <class T>
inline Polynom<T> operator+(const Polynom<T> &p1, const Polynom<T> &p2)
{
  return operator+<T, T, T>(p1, p2);
}

template <class T>
Polynom<T> operator*(const Polynom<T> &p, const T &l)
{
  std::vector<T> ncoeffs = p.coeffs();
  std::for_each(ncoeffs.begin(), ncoeffs.end(), [&l](auto &t) { t *= l; });
  return Polynom<T>{ncoeffs};
}
template <class T>
inline Polynom<T> operator*(const T &l, const Polynom<T> &p)
{
  return p * l;
}

template <class T>
inline Polynom<T> operator-(const Polynom<T> &p)
{
  return p * (T)(-1);
}
template <class T>
inline Polynom<T> operator-(const Polynom<T> &p1, const Polynom<T> &p2)
{
  return p1 + (-p2);
}

template <class T>
Polynom<T> operator*(const Polynom<T> &p1, const Polynom<T> &p2)
{
  int ndeg = p1.deg() + p2.deg();
  std::vector<T> ncoeffs(ndeg + 1);
  // ? TODO: optimize ?
  // n^2...
  for (int i = 0; i <= ndeg; ++i)
    for (int j = 0; j <= i; ++j)
      ncoeffs[i] += p1.coeff(j) * p2.coeff(i - j);
  return {ncoeffs};
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Polynom<T> &d)
{
  os << d.to_string();
  return os;
}

template <class T>
std::string Polynom<T>::to_string() const
{
  // Indeterminate of the polynomial.
  const std::string ind = "X";
  std::string result;
  for (int i = _coeffs.size() - 1; i >= 0; --i)
  {
    // Skip zeros.
    if (_coeffs[i] == 0)
    {
      continue;
    }

    // Append '+' sign, except before the first coefficient. ('-' signs are added by the negative coefficients.)
    if (_coeffs[i] > 0 && "" != result)
    {
      result += '+';
    }

    // Append coefficient if not +-1. If yes, reduce +1 and -1 to + and -, except the constant.
    if (!(1 == _coeffs[i] || -1 == _coeffs[i]) || 0 == i)
    {
      result += std::to_string(_coeffs[i]);
    }
    else if (-1 == _coeffs[i])
    {
      result += '-';
    }

    // Append indeterminate symbol and simplify exponent part. (E.g. 5X^1 -> 5X, 4X^0 -> 4)
    if (i > 1)
    {
      result += ind + '^' + std::to_string(i);
    }
    else if (1 == i)
    {
      result += ind;
    }
  }
  return ("" != result) ? result : "0";
}

// Evaluate polynomial at t using Horner's method.
template <class T>
T Polynom<T>::eval(T t) const
{
  if (_coeffs.empty())
  {
    return 0;
  }
  int result = _coeffs.back();
  for (auto it = ++_coeffs.rbegin(); it != _coeffs.rend(); ++it)
  {
    result *= t;
    result += *it;
  }
  return result;
}

template <class T>
int Polynom<T>::deg() const
{
  int n = _coeffs.size();
  while (n && !_coeffs[--n])
    continue;
  return n;
}

template <class T>
T Polynom<T>::coeff(size_t i) const
{
  return i >= _coeffs.size() ? 0 : _coeffs[i];
}

#endif /* POLYNOM_H */