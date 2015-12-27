#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;
using ReverseAD::TrivialTrace;

#define N 1
#define M 1

int main() {
  double x[4] = {2, 3, 4, 5};
  double y[M];
  adouble yad[M];
  adouble xad[N];
  adouble a1, a2;
  ReverseAD::logging_on();
  ReverseAD::trace_on<double>();
  for (int i=0; i<N; i++) {
    xad[i] <<= x[i];
  }
  double vp = 3.0;
  //adouble p = adouble::markParam(vp);
  yad[0] = 0;

  //for (int i=0; i<N-1; i++) {
    //a1 = xad[i]*xad[i]-xad[i+1];
    //a2 = xad[i] - 1.;
    //yad[0] = yad[0] + 100*a1*a1 + a2*a2;
  //}
  //a1 = xad[0]*xad[0]*p+xad[0]*p;
  //yad[0] = a1-xad[0]*p;
  //yad[0] = xad[0] * p;
  //yad[0] = log(exp(xad[0]));
  //yad[0] *= pow(xad[0], 3);
  yad[0] = xad[0];
  yad[0] >>= y[0];
  //yad[1] >>= y[1];
  std::cout << "yad[0] = " << yad[0].getVal() << std::endl;
  //std::cout << "yad[1] = " << yad[1].getVal() << std::endl;
  std::shared_ptr<TrivialTrace<double>> trace =
      ReverseAD::trace_off<double>();

  trace->dump_trace();
  //vp = 5.0;

  //ReverseAD::TrivialTrace<double>* new_trace =
    //ReverseAD::BaseFunctionReplay::replay(trace, y, M, x, N, &vp, 1);
  std::cout << "new y[0] = " << y[0] << std::endl;
  //std::cout << "new y[1] = " << y[0] << std::endl;
  
  std::shared_ptr<TrivialTrace<double>> new_trace =
    ReverseAD::BaseFunctionReplay::replay_ind<double> (trace, x, N);
  new_trace->dump_trace();

  ReverseAD::BaseReverseThird<double> third(new_trace);
  third.compute(N, M);
  int size_j;
  locint* rind_j;
  locint* cind_j;
  double* values_j;
  third.retrieve_adjoint_sparse_format(&size_j, &rind_j, &cind_j, &values_j);
  for(int i = 0; i < size_j; i++) {
    std::cout << "A[" << rind_j[i] << "," << cind_j[i]
               << "] = " << values_j[i] << std::endl;
  }
  int *size;
  locint **rind;
  locint **cind;
  double** values;
  third.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
  std::cout << "hessian size = "<<size[0] << std::endl;
  for(int i = 0; i < size[0]; i++) {
    std::cout << "H["<<rind[0][i]<<","<<cind[0][i]<<"] = "<<values[0][i] << std::endl;
  }
  locint*** tind;
  third.retrieve_third_sparse_format(&size, &tind, &values);
  std::cout << "third order size = " << size[0] << std::endl;
  for (int i=0; i<size[0]; i++) {
    std::cout << "T[" << tind[0][i][0] << ", " << tind[0][i][1]
              << ", " << tind[0][i][2] << " ] =" << values[0][i] << std::endl;
  }
}
