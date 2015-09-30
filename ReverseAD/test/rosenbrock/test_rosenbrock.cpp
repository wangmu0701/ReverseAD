#include <iostream>

#include "reversead/reversead.hpp"

#define N 4000

int main() {
  adouble* xad = new adouble[N];
  adouble yad;
  double* x = new double[N];
  double y;
  for (int i = 0; i < N; i++) {
    x[i] = i+1;
  }
  //ReverseAD::logging_on();
  ReverseAD::get_timing();
  ReverseAD::trace_on();
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
  ReverseAD::TrivialTrace* trace = ReverseAD::trace_off();
  double time_elapsed = ReverseAD::get_timing();
  std::cout << "overloaded function time = " << time_elapsed << std::endl;

  ReverseAD::BaseFunctionReplay<double> replay(trace);
  double* ry = replay.replay(x, N, 1);
  std::cout << " ry = " << ry[0] << std::endl;
  ReverseAD::BaseReverseHessian<double> hessian(trace);
  hessian.compute(N, 1);
  delete[] x;
  delete[] xad;
}
