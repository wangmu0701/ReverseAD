#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;

#define N 2

int main() {
  adouble* xad = new adouble[N];
  adouble yad;
  double* x = new double[N];
  double y;
  for (int i = 0; i < N; i++) {
    x[i] = i + 1;
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

  //double* ry = replay.replay(x, N, 1);
  double* ry = new double[1];
  for (int i=0; i<N; i++) {x[i]=x[i]+1;}
  ReverseAD::TrivialTrace<double>* new_trace =
    ReverseAD::BaseFunctionReplay::replay_ind(trace, ry,1 ,x, N); 
  std::cout << " ry = " << ry[0] << std::endl;
  ReverseAD::BaseReverseHessian<double> hessian(new_trace);
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
  delete[] x;
  delete[] xad;
}
