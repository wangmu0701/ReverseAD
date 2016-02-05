#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::locint;
using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;

#define N 4

int main() {
  adouble* xad = new adouble[N];
  adouble yad;
  double* x = new double[N];
  double y;
  for (int i = 0; i < N; i++) {
    x[i] = i;
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
  std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
  double time_elapsed = ReverseAD::get_timing();
  std::cout << "overloaded function time = " << time_elapsed << std::endl;

  //double* ry = replay.replay(x, N, 1);
  double* ry = new double[1];
  for (int i=0; i<N; i++) {x[i]=x[i]+1;}
  std::shared_ptr<TrivialTrace<double>> new_trace =
    ReverseAD::BaseFunctionReplay::replay_ind(trace, ry,1 ,x, N); 
  std::cout << " ry = " << ry[0] << std::endl;
  ReverseAD::BaseReverseHessian<double> hessian(new_trace);
  std::shared_ptr<DerivativeTensor<int, double>> tensor =
      hessian.compute(N, 1).get_tensor();
  int size;
  int** tind;
  double* values;
  tensor->get_internal_coordinate_list(0, 1, &size, &tind, &values);
  std::cout << "adjoint size = " << size << std::endl;
  for (int i=0; i<size; i++) {
    std::cout << "A["<<tind[i][0] << "] = " << values[i] << std::endl;
  }
  tensor->get_internal_coordinate_list(0, 2, &size, &tind, &values);
  std::cout << "hessian size = "<<size << std::endl;
  for(int i = 0; i < size; i++) {
    std::cout << "H["<<tind[i][0]<<","<<tind[i][1]<<"] = "<<values[i] << std::endl;
  }
}
