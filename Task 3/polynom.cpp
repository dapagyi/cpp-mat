#include <string>

#include "polynom.h"

std::string Polynom::to_string() const
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
int Polynom::eval(int t) const
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

int Polynom::deg() const
{
  int n = _coeffs.size();
  while (n && !_coeffs[--n])
    continue;
  return n;
}

int Polynom::coeff(size_t i) const
{
  return i >= _coeffs.size() ? 0 : _coeffs[i];
}