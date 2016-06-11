#include <memory>
#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::TrivialTrace;
using ReverseAD::BaseReverseHessian;
using ReverseAD::DerivativeTensor;
using ReverseAD::trace_on;
using ReverseAD::trace_off;

template <typename T>
T foo(T x1, T x2) {
  return pow(x1+1, 2) + pow(x1*x1 - x2, 2);
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
  std::cout << "y = " << vy << std::endl;

  std::unique_ptr<BaseReverseHessian<double>> hessian(
      new BaseReverseHessian<double>(trace));
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor = hessian->compute(2,1);
  hessian.release();

  // retrieve results
  size_t size;
  size_t** tind;
  double* values;
  // adjoints : dep[0].order[1]
  tensor->get_internal_coordinate_list(0, 1, &size, &tind, &values);
  std::cout << "size of adjoints = " << size << std::endl;
  for (size_t i = 0; i < size; i++) {
    std::cout << "A["<< tind[i][0] << "] = " << values[i] << std::endl;
  }
  // hessian : dep[0].order[2]
  tensor->get_internal_coordinate_list(0, 2, &size, &tind, &values);
  std::cout << "size of hessian = " << size << std::endl;
  for (size_t i = 0; i < size; i++) {
    std::cout << "H["<< tind[i][0] << ", " << tind[i][1]
              << "] = " << values[i] << std::endl;
  }
}
