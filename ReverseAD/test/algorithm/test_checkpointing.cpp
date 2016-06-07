#include <iostream>
#include <memory>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::BaseReverseThird;
using ReverseAD::BaseReverseGeneric;
using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;
using ReverseAD::IterativeFunc;

void check_answer(std::shared_ptr<DerivativeTensor<size_t, double>> tensor) {
  size_t size;
  size_t** tind;
  double* values;

  tensor->get_internal_coordinate_list(0, 1, &size, &tind, &values);

  std::cout << "adjoint size = "<<size << std::endl;
  for(size_t i = 0; i < size; i++) {
    std::cout << "A[" << tind[i][0] << "] = " << values[i] << std::endl;
  }

  tensor->get_internal_coordinate_list(0, 2, &size, &tind, &values);
  std::cout << "hessian size = " <<size << std::endl;
  for(size_t i = 0; i < size; i++) {
    std::cout << "H["<<tind[i][0]<<","<<tind[i][1]<<"] = "<<values[i] << std::endl;
  }

  tensor->get_internal_coordinate_list(0, 3, &size, &tind, &values);
  std::cout << "third order size = " << size << std::endl;
  for (size_t i=0; i<size; i++) {
    std::cout << "T[" << tind[i][0] << ", " << tind[i][1]
              << ", " << tind[i][2] << " ] =" << values[i] << std::endl;
  }
}

template <typename T>
void set_up(T* x, size_t x_num, T* t, size_t t_num) {
  t[0] = x[0];
  t[1] = x[1];
}
template <typename T>
void run(T* t, size_t t_num) {
  t[0] = t[1]+t[0];
  t[1] = t[0]*t[1];
}
template <typename T>
bool while_condition(const T* const t, size_t t_num) {
  return t[0] * t[1] < 1000;
}
template <typename T>
void tear_down(T* t, size_t t_num, T* y, size_t y_num) {
  y[0] = t[1] * t[0];
}
int main() {
  ReverseAD::trace_on<double>();
  double x[2] = {2, 1};
  double y;
  adouble xad[2];
  adouble tad[2];
  adouble yad;
  ReverseAD::trace_on<double>();
  xad[0] <<= x[0];
  xad[1] <<= x[1];
  set_up<adouble>(xad, 2, tad, 2);
  while (while_condition<adouble>(tad, 2)) {
    run<adouble>(tad, 2);
  }
  tear_down<adouble>(tad, 2, &yad, 1);
  yad >>= y;
  std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
  std::cout << "t[0] = " << tad[0].getVal() << std::endl;
  std::cout << "t[1] = " << tad[1].getVal() << std::endl;
  std::cout << "y = " << yad.getVal() << std::endl;
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor;
  BaseReverseThird<double> third(trace);
  tensor = third.compute(2, 1).get_tensor();
  check_answer(tensor);
  BaseReverseGeneric<double> generic(trace, 3);
  tensor = generic.compute(2, 1).get_tensor();
  check_answer(tensor);

  IterativeFunc iter_func(2, 1, 2, &(set_up<adouble>), &(tear_down<adouble>),
                          &(run<adouble>), &(while_condition));
  iter_func.run(x, 2, &y, 1);
  std::cout << "y = " << y << std::endl;
  tensor = iter_func.compute(x, 2, &y, 1, 3);
  check_answer(tensor);
} 
