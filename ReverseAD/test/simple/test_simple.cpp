#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;
using ReverseAD::BaseReverseTensor;
using ReverseAD::BaseReverseGeneric;

#define N 1

int main() {
  double x[4] = {1, 2, 3, 4};
  double y;
  adouble yad;
  adouble xad[N];
  adouble a1, a2;
  ReverseAD::trace_on<double>();
  for (int i=0; i<N; i++) {
    xad[i] <<= x[i];
  }
  yad = erf(xad[0]);
  yad >>= y;
  std::cout << "y = " << y << std::endl;
  std::shared_ptr<TrivialTrace<double>> trace =
      ReverseAD::trace_off<double>();
  size_t order = 6;
  ReverseAD::BaseReverseGeneric<double> reverse_tensor(trace, order);
//  ReverseAD::BaseReverseThird<double> reverse_tensor(trace);
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor =
      reverse_tensor.compute(N, 1);
  reverse_tensor.clear();
  std::cout << "done" << std::endl;
  size_t size;
  size_t** tind = nullptr;
  double* values = nullptr; 

  for (size_t i = 1; i <= order; i++) {
    tensor->get_internal_coordinate_list(0, i, &size, &tind, &values);
    std::cout << "Order : " << i << " size = " << size << std::endl;
    for (size_t j = 0; j < size; j++) {
      std::cout << "T[" << tind[j][0];
      for (size_t k = 1; k < i; k++) {
        std::cout << ", " << tind[j][k];
      }
      std::cout << "] = " << values[j] << std::endl;
    }
  }
}
