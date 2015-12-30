#include <memory>
#include <iostream>
#include "reversead/reversead.hpp"
#include "reversead/forwardtype/single_forward.hpp"

using ReverseAD::BaseActive;
using ReverseAD::TrivialTrace;
using ReverseAD::SingleForward;
using ReverseAD::trace_on;
using ReverseAD::trace_off;
using ReverseAD::BaseReverseAdjoint;
using ReverseAD::locint;
using ReverseAD::DerivativeTensor;

typedef BaseActive<SingleForward> fdouble;

void check_answer(DerivativeTensor<locint, SingleForward> tensor) {
  int size;
  locint** tind;
  SingleForward* values;

  tensor.get_internal_coordinate_list(0, 1, &size, &tind, &values);

  std::cout << "adjoint size = "<<size << std::endl;
  for(int i = 0; i < size; i++) {
    std::cout << "A[" << tind[i][0] << "] = " << values[i] << std::endl;
  }
}

int main() {
  SingleForward a(1, 3);
  SingleForward b(2, 4);
  SingleForward y;
  fdouble af;
  fdouble bf;
  fdouble yf;
  ReverseAD::trace_on<SingleForward>();
  af <<= a;
  bf <<= b;
  yf = af * bf;
  yf >>= y;
  std::shared_ptr<ReverseAD::TrivialTrace<SingleForward>> trace =
      ReverseAD::trace_off<SingleForward>();
  trace->dump_trace();
  BaseReverseAdjoint<SingleForward> adjoint(trace);
  SingleForward ay(1, 0);
  DerivativeTensor<locint, SingleForward> tensor = adjoint.compute(2, 1);
  check_answer(tensor);
}
