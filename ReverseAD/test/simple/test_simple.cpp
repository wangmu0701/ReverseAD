#include <iostream>

#include "reversead/reversead.hpp"
#include "reversead/algorithm/base_reverse_hessian.hpp"

int main() {
  adouble a,b,c,d;
  adouble yad;
  double y;
  ReverseAD::trace_on();
  yad = 0;
  a <<= 1.0;
  b <<= 2.0;
  c <<= 3.0;
  d <<= 4.0;
  yad = a * b * c * d;
  yad >>= y;
  std::cout << "yad = " << yad.getVal() << std::endl;
  ReverseAD::TrivialTrace* trace = ReverseAD::trace_off();
  trace->dump_trace();
  ReverseAD::BaseReverseHessian<double> hessian(trace);
  unsigned int *rind;
  unsigned int *cind;
  double* values;
  hessian.compute(4, 1, &rind, &cind, &values);
}
