#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;
using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;

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
  yad[0] = xad[0] * xad[0] * xad[0] * xad[0] * xad[0];
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
  DerivativeTensor<locint, double> tensor = third.compute(N, M);
  int size;
  locint** tind;
  double* values; 

  tensor.get_internal_coordinate_list(0, 1, &size, &tind, &values);
  
  std::cout << "adjoint size = "<<size << std::endl;
  for(int i = 0; i < size; i++) {
    std::cout << "A[" << tind[i][0] << "] = " << values[i] << std::endl;
  }

  tensor.get_internal_coordinate_list(0, 2, &size, &tind, &values);
  std::cout << "hessian size = " <<size << std::endl;
  for(int i = 0; i < size; i++) {
    std::cout << "H["<<tind[i][0]<<","<<tind[i][1]<<"] = "<<values[i] << std::endl;
  }

  tensor.get_internal_coordinate_list(0, 3, &size, &tind, &values);
  std::cout << "third order size = " << size << std::endl;
  for (int i=0; i<size; i++) {
    std::cout << "T[" << tind[i][0] << ", " << tind[i][1]
              << ", " << tind[i][2] << " ] =" << values[i] << std::endl;
  }
}
