#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;
#define N 4

int main() {
  adouble a,b,c,d;
  adouble yad;
  double y;
  ReverseAD::trace_on<double>();
  a <<= 2.0;
  b <<= 3.0;
  c <<= 3.0;
  d <<= 4.0;
  //yad = a * b * c * d;
  yad = sin(a) + sqrt(b) + c / d + 1.0/c;
  //yad = (2*a)/(1/a);
  yad >>= y;
  std::cout << "yad = " << yad.getVal() << std::endl;
  ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
  trace->dump_trace();
  ReverseAD::BaseReverseHessian<double> hessian(trace);
  hessian.compute(N, 1);
  double** adjoints;
  hessian.retrieve_adjoint(&adjoints);
  for(int i = 0; i < N; i++) {
    std::cout << "A[" << i << "] = " << adjoints[0][i] << std::endl;
  }
  int *size;
  locint **rind;
  locint **cind;
  double** values;
  hessian.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
  std::cout << "hessian size = "<<size[0] << std::endl;
  for(int i = 0; i < size[0]; i++) {
    std::cout << "H["<<rind[0][i]<<","<<cind[0][i]<<"] = "<<values[0][i] << std::endl;
  }
}
