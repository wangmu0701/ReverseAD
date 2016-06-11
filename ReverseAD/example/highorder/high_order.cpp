#include <memory>
#include <iostream>

#include "reversead/reversead.hpp"

#define ORDER 5

using ReverseAD::adouble;
using ReverseAD::TrivialTrace;
using ReverseAD::BaseReverseGeneric;
using ReverseAD::BaseReverseTensor;
using ReverseAD::DerivativeTensor;
using ReverseAD::trace_on;
using ReverseAD::trace_off;

void dump_tensor(std::shared_ptr<DerivativeTensor<size_t, double>> tensor) {
  size_t size;
  size_t **tind;
  double *values;
  for (size_t k = 1; k <= ORDER; k++) {
    tensor->get_internal_coordinate_list(0, k, &size, &tind, &values);
    std::cout << "Size of derivative order["<<k<<"] = " << size << std::endl;
    for (size_t i = 0; i < size; i++) {
      std::cout << "T[";
      for (size_t j = 0; j < k; j++) {
        std::cout << " " << tind[i][j];
      }
      std::cout << " ] = " << values[i] << std::endl;
    } 
  }
}
template <typename T>
T foo(T x1, T x2) {
  return exp(pow(x1+1, 2) + pow(x1*x1 - x2, 2));
}

int main() {
  adouble x1, x2;
  adouble y;
  double vy;
  trace_on<double>(); // begin tracing
  x1 <<= 2.0; // independent variable #0
  x2 <<= 3.0; // independent variable #1
  y = foo<adouble>(x1, x2); // function evaluation
  y >>= vy; // dependent variable
  std::shared_ptr<TrivialTrace<double>> trace =
      trace_off<double>(); // end tracing

  std::unique_ptr<BaseReverseGeneric<double>> generic(
      new BaseReverseGeneric<double>(trace, 5));
  std::unique_ptr<BaseReverseTensor<double>> generator(
      new BaseReverseTensor<double>(trace, 5));
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor = 
      generic->compute(2, 1);
  std::cout << std::endl << "-----  BaseReverseGeneric  -----" << std::endl << std::endl;
  dump_tensor(tensor);
  tensor = generator->compute(2, 1);
  std::cout << std::endl << "-----  BaseReverseTensor   -----" << std::endl << std::endl;
  dump_tensor(tensor);
}
