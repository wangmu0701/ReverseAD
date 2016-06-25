#include <memory>
#include <iostream>
#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::BaseActive;
using ReverseAD::TrivialTrace;
using ReverseAD::SingleForward;
using ReverseAD::MultiForward;
using ReverseAD::trace_on;
using ReverseAD::trace_off;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseAdjoint;
using ReverseAD::BaseReverseHessian;
using ReverseAD::BaseReverseThird;
using ReverseAD::DerivativeTensor;

#define N 3
#define DIRECTION 5

template <typename T>
std::shared_ptr<TrivialTrace<T>> foo(T* x, size_t n) {
  typedef BaseActive<T> AT;
  T y;
  AT* xad = new AT[n];
  ReverseAD::trace_on<T>();
  for (size_t i = 0; i < n; i++) {
    xad[i] <<= x[i];
  }
  AT yad = 1.0;
  for (size_t i = 0; i < n; i++) {
    yad = yad * xad[i];
  }
  yad >>= y;
  delete[] xad;
  return ReverseAD::trace_off<T>();
}

void single_forward(double ind_init_values[],
                    double adjoint_init_values[][DIRECTION]) {
  SingleForward* x = new SingleForward[N];
  for (size_t i = 0; i < DIRECTION; i++) {
    for (size_t j = 0; j < N; j++) {
      new(&x[j]) SingleForward(ind_init_values[j], adjoint_init_values[j][i]);
    }
    std::shared_ptr<TrivialTrace<SingleForward>> trace = foo(x, N);
    BaseReverseHessian<SingleForward> hessian(trace);
    std::shared_ptr<DerivativeTensor<size_t, SingleForward>> tensor = hessian.compute(N, 1);
    size_t size;
    size_t** tind;
    SingleForward* values;
    tensor->get_internal_coordinate_list(0, 1, &size, &tind, &values);
    std::cout << "Directional adjoint along : ["
              << adjoint_init_values[0][i] << ", "
              << adjoint_init_values[1][i] << ", "
              << adjoint_init_values[2][i] << " ] is : " << std::endl;
    for (size_t j = 0; j < size; j++) {
      std::cout << "    A[" << tind[j][0] << "] = "
                << " { val : " << values[j].getVal()
                << ", der : " << values[j].getDer() << " }"<< std::endl;
    }
    tensor->get_internal_coordinate_list(0, 2, &size, &tind, &values);
    std::cout << "Directional Hessian along : ["
              << adjoint_init_values[0][i] << ", "
              << adjoint_init_values[1][i] << ", "
              << adjoint_init_values[2][i] << " ] is : " << std::endl;
    for (size_t j = 0; j < size; j++) {
      std::cout << "    H[" << tind[j][0] << ", " << tind[j][1] << "] = "
                << " { val : " << values[j].getVal()
                << ", der : " << values[j].getDer() << " }"<< std::endl;
    }
  }
  delete[] x;
}

void multi_forward(double ind_init_values[],
                   double adjoint_init_values[][DIRECTION]) {
  MultiForward<DIRECTION>* x = new MultiForward<DIRECTION>[N];
  for (size_t i = 0; i < N; i++) {
    new(&x[i]) MultiForward<DIRECTION>(ind_init_values[i], adjoint_init_values[i]);
  }
  std::shared_ptr<TrivialTrace<MultiForward<DIRECTION>>> trace = foo(x, N);
  BaseReverseHessian<MultiForward<DIRECTION>> hessian(trace);
  std::shared_ptr<DerivativeTensor<size_t, MultiForward<DIRECTION>>> tensor = hessian.compute(N, 1);
  size_t size;
  size_t** tind;
  MultiForward<DIRECTION>* values;
  tensor->get_internal_coordinate_list(0, 1, &size, &tind, &values);
  for (size_t i = 0; i < DIRECTION; i++){
    std::cout << "Directional adjoint along : ["
              << adjoint_init_values[0][i] << ", "
              << adjoint_init_values[1][i] << ", "
              << adjoint_init_values[2][i] << " ] is : " << std::endl;
    for (size_t j = 0; j < size; j++) {
      std::cout << "    A[" << tind[j][0] << "] = "
                << " { val : " << values[j].getVal()
                << ", der : " << values[j].getDer(i) << " }"<< std::endl;
    }
  }
  
  tensor->get_internal_coordinate_list(0, 2, &size, &tind, &values);
  for (size_t i =0; i < DIRECTION; i++){
    std::cout << "Directional Hessian along : ["
              << adjoint_init_values[0][i] << ", "
              << adjoint_init_values[1][i] << ", "
              << adjoint_init_values[2][i] << " ] is : " << std::endl;
    for (size_t j = 0; j < size; j++) {
      std::cout << "    H[" << tind[j][0] << ", " << tind[j][1] << "] = "
                << " { val : " << values[j].getVal()
                << ", der : " << values[j].getDer(i) << " }"<< std::endl;
    }
  }
  delete[] x;
}
int main() {
  double x[3] = {1, 2, 3};
  double a[3][5] = {{1, 0, 0, 1, 1},
                    {0, 1, 0, 1, 2},
                    {0, 0, 1, 1, 3}};

  std::cout << "---------------------------" << std::endl;
  std::cout << "Running SingleForward ... " << std::endl << std::endl;
  single_forward(x, a);
  std::cout << std::endl;

  std::cout << "---------------------------" << std::endl;
  std::cout << "Running MulfiForward<5> ..." << std::endl << std::endl;
  multi_forward(x, a);
  return 0;
}
