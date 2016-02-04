#include <iostream>
#include <memory>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::BaseReverseThird;
using ReverseAD::BaseReverseGeneric;
using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;


void check_answer(DerivativeTensor<int, double> tensor) {
  int size;
  int** tind;
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

int main() {
  ReverseAD::trace_on<double>();
  adouble a, b, c, d;
  a <<= 1;
  b <<= 2;
  c <<= 3;
  d <<= 4;
  adouble z = a*b*c*d;
  double vz;
  z >>= vz;
  std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
  std::cout << "z = " << z.getVal() << std::endl;
  DerivativeTensor<int, double> tensor;
  BaseReverseThird<double> third(trace);
  tensor = third.compute(4, 1);
  check_answer(tensor);
  BaseReverseGeneric<double> generic(trace, 3);
  tensor = generic.compute(4, 1);
  check_answer(tensor);
} 
