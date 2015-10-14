#include <iostream>

#include "reversead/reversead.hpp"
#include "reversead/algorithm/base_reverse_hessian.hpp"

using ReverseAD::locint;

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
  yad = sin(a) + cos(b) + c / d + 1.0/c;
  yad >>= y;
  std::cout << "yad = " << yad.getVal() << std::endl;
  ReverseAD::TrivialTrace* trace = ReverseAD::trace_off();
  trace->dump_trace();
  ReverseAD::BaseReverseHessian<double> hessian(trace);
  int *size;
  locint **rind;
  locint **cind;
  double** values;
  hessian.compute(4, 1);
  hessian.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
  std::cout << "hessian size = "<<size[0] << std::endl;
  for(int i = 0; i < size[0]; i++) {
    std::cout << "H["<<rind[0][i]<<","<<cind[0][i]<<"] = "<<values[0][i] << std::endl;
  }
}
