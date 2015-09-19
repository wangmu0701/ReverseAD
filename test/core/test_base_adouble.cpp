#include <iostream>

#include "src/core/base_active.hpp"
#include "src/core/reversead.hpp"
#include "src/trace/trivial_trace.hpp"

//using namespace ReverseAD;
//typedef BaseActive<double> adouble;

int main() {
  ReverseAD::trace_on();
  adouble a, b, c, d;
  a = 1;
  b = 2;
  c = 3;
  d = 4;
  d = d + 4;
  d = 4 + d;  // 12
  adouble x(a+b+c+d); // 18
  adouble y = (b * c) + d; // 18
  y = y * 2.0; // 36
  x = 2.0 * x;  // 36
  adouble z = x + y; // 72
  ReverseAD::TrivialTrace* trace = ReverseAD::trace_off();
  std::cout << "z = " << z.getVal() << std::endl;  
  trace->dump_trace();
} 
