#include <iostream>
#include <memory>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::BaseReverseThird;
using ReverseAD::BaseReverseGeneric;
using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;
using ReverseAD::IterativeFunc;
using ReverseAD::IterativeFuncFixed;

double myEps = 1.0e-10;

void dump_tensor(std::shared_ptr<DerivativeTensor<size_t, double>> tensor) {
  size_t size = 0;
  size_t** tind = nullptr;
  double* values = nullptr;

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

void check_fail() {
  std::cout << "IterativeFunc test fail!" << std::endl;
  exit(-1);
}
void check_answer(std::shared_ptr<DerivativeTensor<size_t, double>> tensor1,
                  std::shared_ptr<DerivativeTensor<size_t, double>> tensor2) {
  size_t size1 = 0;
  size_t **tind1 = nullptr;
  double *values1 = nullptr;
  size_t size2 = 0;
  size_t **tind2 = nullptr;
  double *values2 = nullptr;
  for (size_t k = 1; k <=3; k++) {
    tensor1->get_internal_coordinate_list(0, k, &size1, &tind1, &values1);
    tensor2->get_internal_coordinate_list(0, k, &size2, &tind2, &values2);
    if (size1 != size2) {
      check_fail();
    }
    for (size_t i = 0; i < size1; i++) {
      for (size_t j = 0; j < k; j++) {
        if (tind1[i][j] != tind2[i][j]) {
          check_fail();
        }
      }
      if (fabs(values1[i] - values2[i]) > myEps) {
        check_fail();
      }
    }
  }
}

template <typename T>
void set_up(T* x, size_t x_num, T* t, size_t t_num) {
  t[0] = x[0];
  t[1] = x[1];
}
template <typename T>
void run(T* t, size_t t_num) {
//  printf("<%.5f, %.5f> -->", (double)t[0], (double)t[1]);
  t[0] = t[1]+t[0];
  t[1] = t[0]*t[1];
//  printf("<%.5f, %.5f>\n", (double)t[0], (double)t[1]);
}
template <typename T>
bool while_condition(const T* const t, size_t t_num) {
  return t[0] * t[1] < 10000;
}
template <typename T>
void tear_down(T* t, size_t t_num, T* y, size_t y_num) {
  y[0] = t[1] * t[0];
}
int main() {
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
  //std::cout << "t[0] = " << tad[0].getVal() << std::endl;
  //std::cout << "t[1] = " << tad[1].getVal() << std::endl;
  //std::cout << "y = " << yad.getVal() << std::endl;
  BaseReverseThird<double> third(trace);
  std::shared_ptr<DerivativeTensor<size_t, double>> r_tensor =
      third.compute(2, 1);
  //dump_tensor(r_tensor);
  BaseReverseGeneric<double> generic(trace, 3);
  std::shared_ptr<DerivativeTensor<size_t, double>> g_tensor =
      generic.compute(2, 1);
  //dump_tensor(g_tensor);

  IterativeFunc iter_func(2, 1, 2, &(set_up<adouble>), &(tear_down<adouble>),
                          &(run<adouble>), &(while_condition<adouble>));
  // Force iter_func to create multiple checkpoints
  iter_func.set_min_op_per_cp(1);
  iter_func.run(x, 2, &y, 1);
  std::shared_ptr<DerivativeTensor<size_t, double>> i_tensor =
      iter_func.compute(x, 2, &y, 1, 3);
  //dump_tensor(i_tensor);
  check_answer(r_tensor, i_tensor);
  check_answer(g_tensor, i_tensor);
  IterativeFuncFixed iter_func_fixed(2, 1, 2, &(set_up<adouble>), &(tear_down<adouble>), &(run<adouble>), 3);
  iter_func_fixed.set_min_op_per_cp(1);
  std::shared_ptr<DerivativeTensor<size_t, double>> f_tensor = 
      iter_func_fixed.compute(x, 2, &y, 1, 3);
  check_answer(i_tensor, f_tensor);
  std::cout << "IterativeFunc test OK!" << std::endl;
  return 0;
} 
