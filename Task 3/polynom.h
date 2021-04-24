// polynom.h
#ifndef POLYNOM_H
#define POLYNOM_H

#include <vector>
#include <string>

class Polynom
{
public:
  Polynom(std::vector<int> coeffs = {}) : _coeffs(coeffs){};

  std::string to_string() const;
  int eval(int) const;
  int coeff(size_t i) const;
  int deg() const;

private:
  std::vector<int> _coeffs;
};

#endif /* POLYNOM_H */