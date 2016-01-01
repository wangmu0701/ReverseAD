#include <memory>
#include <iostream>
#include "reversead/reversead.hpp"
#include "reversead/forwardtype/single_forward.hpp"
#include "reversead/driver/forward_over_reverse.hpp"

using ReverseAD::BaseActive;
using ReverseAD::TrivialTrace;
using ReverseAD::SingleForward;
using ReverseAD::trace_on;
using ReverseAD::trace_off;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseAdjoint;
using ReverseAD::locint;
using ReverseAD::DerivativeTensor;

typedef BaseActive<SingleForward> fdouble;

template <typename T>
void check_answer(DerivativeTensor<locint, T> tensor) {
  int size;
  locint** tind;
  T* values;

  tensor.get_internal_coordinate_list(0, 1, &size, &tind, &values);

  std::cout << "adjoint size = "<<size << std::endl;
  for(int i = 0; i < size; i++) {
    std::cout << "A[" << tind[i][0] << "] = " << values[i] << std::endl;
  }
}

template <typename T>
std::shared_ptr<TrivialTrace<T>> foo(T a, T b) {
  typedef BaseActive<T> AT;
  T y;
  AT af, bf, yf;
  ReverseAD::trace_on<T>();
  af <<= a;
  bf <<= b;
  yf = af * bf;
  yf >>= y;
  return ReverseAD::trace_off<T>();

}
int main() {
/*
  SingleForward a(1, 3);
  SingleForward b(2, 4);
  std::shared_ptr<TrivialTrace<SingleForward>> trace =
      foo(a, b);
  trace->dump_trace();
  BaseReverseAdjoint<SingleForward> adjoint(trace);
  SingleForward ay(1, 0);
  DerivativeTensor<locint, SingleForward> tensor = adjoint.compute(2, 1);
  check_answer(tensor);
*/
  std::shared_ptr<TrivialTrace<double>> trace = foo<double>(1,2);
  double v[2] = {0, 2};
  double a[2] = {3, 4};
  double* h = new double[2];
  forward_over_reverse(trace, 2, 1, v, a, &h);
  std::cout << "h[0] = " << h[0] << " h[1] = " << h[1] << std::endl;
}
