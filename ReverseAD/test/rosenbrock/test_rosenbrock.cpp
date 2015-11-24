#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;

#define N 4

int main() {
  adouble* xad = new adouble[N];
  adouble yad;
  double* x = new double[N];
  double y;
  for (int i = 0; i < N; i++) {
    x[i] = i+1;
  }
  ReverseAD::logging_on();
  ReverseAD::get_timing();
  ReverseAD::trace_on<double>();
  yad = 0;
  for (int i = 0; i < N; i++) {
    xad[i] <<= x[i];
  }
  for (int i = 0; i < N - 1; i++) {
    yad = yad+100*(xad[i+1]-xad[i]*xad[i])*(xad[i+1]-xad[i]*xad[i])
          +(xad[i]-1)*(xad[i]-1);
  }
  yad >>= y;
  std::cout << "yad = " << yad.getVal() << std::endl;
  ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
  double time_elapsed = ReverseAD::get_timing();
  std::cout << "overloaded function time = " << time_elapsed << std::endl;

  ReverseAD::BaseFunctionReplay<double> replay(trace);
  double* ry = replay.replay(x, N, 1);
  std::cout << " ry = " << ry[0] << std::endl;
  ReverseAD::BaseReverseHessian<double> hessian(trace);
  hessian.compute(N, 1);
  int *size;
  locint **rind;
  locint **cind;
  double** values;
  hessian.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
  std::cout << "hessian size = "<<size[0] << std::endl;
  for(int i = 0; i < size[0]; i++) {
    std::cout << "H["<<rind[0][i]<<","<<cind[0][i]<<"] = "<<values[0][i] << std::endl;
  }
  delete[] x;
  delete[] xad;
}
