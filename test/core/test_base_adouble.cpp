#include <iostream>

#include "src/core/base_active.hpp"

using namespace ReverseAD;

typedef BaseActive<double> adouble;

int main() {
  adouble a, b, c, d;
  a = 1;
  b = 2;
  c = 3;
  d = 4;
  adouble z(a+b+c+d);
  std::cout << "z = " << z.getVal() << std::endl;  
} 
