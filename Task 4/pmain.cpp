#include <iostream>
#include "polynom.h"

int main()
{
  Polynom<double> p1{{42, 0, 5, 0, 8, 9}};
  Polynom<double> p2{{-2, 6, -3, 9, 1}};
  Polynom<int> p3{{-2, 6, -3, 9, 1}};

  int t1 = 0;
  int t2 = 1;
  int t3 = -2;

  auto poly1 = p1 + p2;
  auto poly2 = 2.0 * p1;
  auto poly3 = p1 - p2;
  auto poly4 = p1 * p2;
  auto poly5 = operator+<int>(p1, p3);
  std::cout << "p1    = " << p1.to_string() << '\n';
  std::cout << "p2    = " << p2.to_string() << '\n';
  std::cout << "p3    = " << p3.to_string() << '\n';
  std::cout << "p1+p2 = " << poly1.to_string() << '\n';
  std::cout << "2*p1  = " << poly2.to_string() << '\n';
  std::cout << "p1-p2 = " << poly3.to_string() << '\n';
  std::cout << "p1*p2 = " << poly4.to_string() << '\n';
  std::cout << "p1+p3 = " << poly5.to_string() << '\n';
  std::cout << "p1+p2 = " << p1 + p2 << '\n';

  std::cout << "\np1(" << t1 << ")    == " << p1(t1);
  std::cout << "  p1(" << t2 << ")    == " << p1(t2);
  std::cout << "  p1(" << t3 << ")    == " << p1(t3);
  std::cout << "\np2(" << t1 << ")    == " << p2(t1);
  std::cout << "  p2(" << t2 << ")    == " << p2(t2);
  std::cout << "  p2(" << t3 << ")    == " << p2(t3);
  std::cout << "\n(p1+p2)(" << t1 << ") == " << poly1(t1);
  std::cout << "  (p1+p2)(" << t2 << ") == " << poly1(t2);
  std::cout << "  (p1+p2)(" << t3 << ") == " << poly1(t3)
            << '\n';
  return 0;
}