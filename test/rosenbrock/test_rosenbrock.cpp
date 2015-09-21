#include <iostream>

#include "src/reverse_ad_common.hpp"

#define N 5

int main() {
  adouble* xad = new adouble[N];
  adouble yad;
  double* x = new double[N];
  double y;
  for (int i = 0; i < N; i++) {
    x[i] = i;
  }
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
  ReverseAD::BaseFunctionReplay<double> replay(trace);
  double* ry = replay.replay(x, N, 1);
  std::cout << " ry = " << ry[0] << std::endl;
  ReverseAD::BaseReverseAdjoint<double> adjoint(trace);
  double ay = 1;
  double** ax = adjoint.compute(&ay, N, 1);
  for (int i = 0; i < N; i++) {
    std::cout<<"ax["<<i<<"] = " << ax[0][i] << std::endl;
  }
  delete x;
}
