#include <iostream>
#include <vector>
#include <string>

std::string to_string(std::vector<int> v);
int evaluate(std::vector<int> v, int t);

template <typename T>
void assert(const T &out, const T &expOut, std::string title);
struct to_string_test_t
{
  std::vector<int> coeffs;
  std::string expOut;
};
struct evaluate_test_t
{
  std::vector<int> coeffs;
  int t;
  int expOut;
};

int main()
{
  std::cerr << "<---------- Test: to_string ---------->\n";
  std::vector<to_string_test_t> to_string_tests = {
    {{0, -1, 3, 0}, "3X^2-X"},
    {{0, 0, 0}, "0"},
    {{}, "0"},
    {{-4, 2, -1}, "-X^2+2X-4"},
    {{6, 0, 0}, "6"},
    {{-1, 0, 0}, "-1"},
    {{1, 0, 0}, "1"},
    {{0, 1, 0}, "X"},
    {{0, -6, 0}, "-6X"},
    {{-1, 42, -2, -5}, "-5X^3-2X^2+42X-1"},
    {{-1, 1, 0}, "X-1"},
    {{1, -2, 3, -4, 5}, "5X^4-4X^3+3X^2-2X+1"},
    {{1, -1, 1, -1, 1, -1, 1}, "X^6-X^5+X^4-X^3+X^2-X+1"},
    {{-2, 0, 5, -3, 8}, "8X^4-3X^3+5X^2-2"}
  };
  for ( auto t : to_string_tests )
  {
    assert<std::string>(to_string(t.coeffs), t.expOut, t.expOut);
  }

  std::cerr << "\n<---------- Test: evaluate ---------->\n";
  std::vector<evaluate_test_t> evaluate_tests = {
    {{0, -1, 3, 0}, 10, 290},
    {{0}, 1, 0},
    {{}, 42, 0},
    {{-1, 1, -1, 1}, 5, 104},
    {{-2, 0, 5, -3, 8}, -2, 170},
    {{-2, 0, 5, -3, 8}, 0, -2},
    {{-2, 0, 5, -3, 8}, 42, 24680122}
  };
  for ( auto t : evaluate_tests )
  {
    assert<int>(
      evaluate(t.coeffs, t.t),
      t.expOut,
      "P(X) = " + to_string(t.coeffs) + ",\tP(" + std::to_string(t.t) + ") = " + std::to_string(t.expOut)
    );
  }

  return 0;
}

std::string to_string(std::vector<int> v)
{
  // Indeterminate of the polynomial
  const std::string ind = "X";
  std::string result;
  for ( int i = v.size() - 1; i >= 0; --i )
  {
    // Skip zeros.
    if ( v[i] == 0 )
    {
      continue;
    }

    // Append '+' sign, except before the first coefficient. ('-' signs are added by the negative coefficients.)
    if ( v[i] > 0 && "" != result )
    {
      result += '+';
    }

    // Append coefficient if not +-1. If yes, reduce +1 and -1 to + and -, except the constant. 
    if ( !(1 == v[i] || -1 == v[i]) || 0 == i)
    {
      result += std::to_string(v[i]);
    }
    else if ( -1 == v[i] )
    {
      result += '-';
    }

    // Append indeterminate symbol and simplify exponent part. (E.g. 5X^1 -> 5X, 4X^0 -> 4) 
    if ( i > 1 )
    {
      result += ind + '^' + std::to_string(i);
    }
    else if ( i == 1 )
    {
      result += ind;
    }
  }
  return ( "" != result ) ? result : "0";
}

// Evaluate polynomial at t using Horner's method
int evaluate(std::vector<int> v, int t)
{
  if ( v.empty() )
  {
    return 0;
  }
  int result = v.back();
  for ( auto it = ++v.rbegin(); it != v.rend(); ++it )
  {
    result *= t;
    result += *it;
  }
  return result;
}

// Based on lecture "16. Templates"
template <typename T>
void assert(const T &out, const T &expOut, std::string title)
{
  if ( expOut == out )
  {
    std::cerr << "Passed test: " << title << '\n';
  }
  else
  {
    std::cerr << "[!] Failed test: " << title
              << "\tExpected: "      << expOut 
              << "\tReturned: "      << out <<'\n';
  }
}
