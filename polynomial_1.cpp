#include <iostream>
#include <vector>
#include <string>

std::string to_string(std::vector<int> v);
void assert(std::vector<int> v, std::string expOut);

int main()
{
  assert( {0, -1, 3, 0}, "3X^2-X" );
  assert( {0, 0, 0}, "0" );
  assert( {}, "0" );
  assert( {-4, 2, -1}, "-X^2+2X-4" );
  assert( {6, 0, 0}, "6" );
  assert( {-1, 0, 0}, "-1" );
  assert( {1, 0, 0}, "1" );
  assert( {0, 1, 0}, "X" );
  assert( {0, -6, 0}, "-6X" );
  assert( {-1, 42, -2, -5}, "-5X^3-2X^2+42X-1" );
  assert( {-1, 1, 0}, "X-1" );
  assert( {-2, 0, 5, -3, 8}, "8X^4-3X^3+5X^2-2" ); 
  assert( {1, -2, 3, -4, 5}, "5X^4-4X^3+3X^2-2X+1" ); 
  assert( {1, -1, 1, -1, 1, -1, 1}, "X^6-X^5+X^4-X^3+X^2-X+1" );
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

void assert(std::vector<int> v, std::string expOut)
{
  std::string r = to_string(v);
  if ( expOut == r )
  {
    std::cout << "Passed:\t" << r << '\n';
  }
  else
  {
    std::cerr << "Failed:\t" << expOut << "\treturned string:\t" << r << '\n';
  }
}
