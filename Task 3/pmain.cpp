#include <iostream>
#include <vector>

#include "polynom.h"

int main()
{
  std::vector<Polynom> polynoms{
      {{-2, 0, 5, -3, 8}},
      {{42, 0, 5, 0, 8, 9}},
      {{-42, 0, 5, 0, 8, -9}},
      {{0, 0, 5, 0, 8, -9}},
      {{0, 0, -5, 0, 8, -9}},
      {{8}},
      {{-8}},
      {{0}},
      {{}}};
  polynoms.push_back(Polynom{}); // default constructor

  int t1 = -2;
  int t2 = 0;
  int t3 = 42;
  for (auto poly : polynoms)
  {
    std::string s = poly.to_string();
    std::cout << s << "\t\t";
    std::cout << "deg = " << poly.deg() << "\t\t"; // degree
    for (int i = 9; i >= 0; --i)                   // print coeffs 9..0
    {
      // if i > deg() then this should be 0
      std::cout << poly.coeff(i) << " ";
    }
    // evaluate the polynom at t1, t2, t3
    std::cout << "\neval(" << t1 << ") == " << poly.eval(t1);
    std::cout << "\teval(" << t2 << ") == " << poly.eval(t2);
    std::cout << "\teval(" << t3 << ") == " << poly.eval(t3);
    std::cout << '\n';
  }
  return 0;
}