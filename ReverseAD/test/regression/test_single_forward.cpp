#include <memory>
#include <iostream>
#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::BaseActive;
using ReverseAD::TrivialTrace;
using ReverseAD::SingleForward;
using ReverseAD::trace_on;
using ReverseAD::trace_off;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseAdjoint;
using ReverseAD::BaseReverseHessian;
using ReverseAD::BaseReverseThird;
using ReverseAD::BaseReverseGeneric;
using ReverseAD::DerivativeTensor;

double myEps = 1.E-10;

void symmetric_matrix_vector(
    size_t n, size_t h_size, size_t** h_tind,
    double* h_value, double* v, double* hv);

void symmetric_third_vector(
    size_t n, size_t t_size, size_t** t_ind, double* t_value,
    double* v, double** tv);


void check_forward_over_second(
    size_t ind_num,
    double** ctv,
    double** tv,
    std::shared_ptr<DerivativeTensor<size_t, SingleForward>> s_tensor) {
  for (size_t i = 0; i < ind_num; i++) {
    for (size_t j = 0; j < ind_num; j++) {
      tv[i][j] = 0.0;
    }
  }
  size_t size;
  size_t** tind;
  SingleForward* values;
  s_tensor->get_internal_coordinate_list(0, 2, &size, &tind, &values);
  for (size_t i = 0; i < size; i++) {
    tv[tind[i][0]][tind[i][1]] = values[i].getDer();
  }
  for (size_t i=0; i<ind_num; i++) {
    for(size_t j=0;j<ind_num; j++) {
      if (fabs(tv[i][j] - ctv[i][j]) > myEps) {
        std::cout << "Single Forward over second error!" << std::endl;
        exit(-1);
      }
    }
  }
  std::cout << "Single Forward over second OK!" << std::endl;
}
void test_forward_over_second(
    std::shared_ptr<TrivialTrace<double>> trace,
    size_t ind_num, size_t dep_num,
    double* ind_init_values,
    double* adjoint_init_values) {
  BaseReverseThird<double> third(trace);
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor =
      third.compute(ind_num, dep_num);
  size_t t_size = 0;
  size_t** t_tind = nullptr;
  double* t_value = nullptr;
  tensor->get_internal_coordinate_list(0, 3, &t_size, &t_tind, &t_value);

  double** tv = new double*[ind_num];
  double** ctv = new double*[ind_num];
  for (size_t i=0; i<ind_num; i++) {
    tv[i] = new double[ind_num];
    ctv[i] = new double[ind_num];
  }
  symmetric_third_vector(ind_num, t_size, t_tind, t_value, adjoint_init_values, ctv);

  SingleForward* x = new SingleForward[ind_num];

  for (size_t i = 0; i < ind_num; i++) {
    new(&x[i]) SingleForward(ind_init_values[i], adjoint_init_values[i]);
  }
  std::shared_ptr<TrivialTrace<SingleForward>> new_trace =
    BaseFunctionReplay::replay_forward<double, SingleForward>(
      trace, x, ind_num);

  BaseReverseHessian<SingleForward> hessian(new_trace);
  std::shared_ptr<DerivativeTensor<size_t, SingleForward>> s_tensor = hessian.compute(ind_num, 1);
  std::cout << "BaseReverseHessian : ";
  check_forward_over_second(ind_num, ctv, tv, s_tensor);

  BaseReverseGeneric<SingleForward> generic(new_trace, 2);
  s_tensor = generic.compute(ind_num, 1);
  std::cout << "BaseReverseGeneric : ";
  check_forward_over_second(ind_num, ctv, tv, s_tensor);

  for (size_t i=0; i<ind_num; i++) {
    delete[] tv[i];
    delete[] ctv[i];
  }
  delete[] tv;
  delete[] ctv; 
  delete[] x;
}

void check_forward_over_reverse(
    size_t ind_num,
    double* chv,
    std::shared_ptr<DerivativeTensor<size_t, SingleForward>> s_tensor) {
  size_t size;
  size_t** tind;
  SingleForward* values;
  s_tensor->get_internal_coordinate_list(0, 1, &size, &tind, &values);
  double* hv = new double[ind_num];
  for (size_t i = 0; i < ind_num; i++) {hv[i] = 0.0;}
  for (size_t i = 0; i < size; i++) {
    hv[tind[i][0]] = values[i].getDer();
  }
  for (size_t i=0; i<ind_num; i++) {
    if (fabs(hv[i] - chv[i]) > myEps) {
      std::cout << "Single Forward over reverse error!" << std::endl;
      exit(-1);
    }
  }
  std::cout << "Single Forward over reverse OK!" << std::endl;
  delete[] hv;
}

void test_forward_over_reverse(
    std::shared_ptr<TrivialTrace<double>> trace,
    size_t ind_num, size_t dep_num,
    double* ind_init_values,
    double* adjoint_init_values) {
  BaseReverseHessian<double> hessian(trace);
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor =
      hessian.compute(ind_num, dep_num);
  size_t h_size = 0;
  size_t** h_tind = nullptr;
  double* h_value = nullptr;
  tensor->get_internal_coordinate_list(0, 2, &h_size, &h_tind, &h_value);
  double* chv = new double[ind_num];
  symmetric_matrix_vector(ind_num, h_size, h_tind, h_value, adjoint_init_values, chv);

  SingleForward *x = new SingleForward[ind_num];
  for (size_t i =0 ; i < ind_num; i++) {
    new(&x[i]) SingleForward(ind_init_values[i], adjoint_init_values[i]);
  }
  std::shared_ptr<TrivialTrace<SingleForward>> new_trace = 
      BaseFunctionReplay::replay_forward<double, SingleForward>(trace, x, ind_num);
  BaseReverseAdjoint<SingleForward> adjoint(new_trace);
  std::shared_ptr<DerivativeTensor<size_t, SingleForward>> s_tensor =
    adjoint.compute(ind_num, 1);
  std::cout << "BaseReverseAdjoint : ";
  check_forward_over_reverse(ind_num, chv, s_tensor);
  BaseReverseAdjoint<SingleForward> generic(new_trace);
  s_tensor = generic.compute(ind_num, 1);
  std::cout << "BaseReverseGeneric : ";
  check_forward_over_reverse(ind_num, chv, s_tensor);
  delete[] chv;
  delete[] x;
}

template <typename T>
std::shared_ptr<TrivialTrace<T>> foo(T a, T b, T c) {
  typedef BaseActive<T> AT;
  T y;
  AT af, bf, cf, yf;
  ReverseAD::trace_on<T>();
  af <<= a;
  bf <<= b;
  cf <<= c;
  yf = af * bf * cf;
  yf >>= y;
  return ReverseAD::trace_off<T>();
}
template <typename T>
std::shared_ptr<TrivialTrace<T>> bar(T a, T b, T c) {
  typedef BaseActive<T> AT;
  T y;
  AT af, bf, cf, yf;
  ReverseAD::trace_on<T>();
  af <<= a;
  bf <<= b;
  cf <<= c;
  yf = af * bf;
  yf += sin(cf);
  yf *= cos(af);
  yf /= log(bf);
  yf >>= y;
  return ReverseAD::trace_off<T>();
}
int main() {
  double x[3] = {1, 2, 3};
  double a[3] = {10, 20, 30};
  std::shared_ptr<TrivialTrace<double>> trace = foo<double>(1,2,3);
  test_forward_over_reverse(trace, 3, 1, x, a);
  test_forward_over_second(trace, 3, 1, x, a);
  trace = bar<double>(1, 2, 3);
  test_forward_over_reverse(trace, 3, 1, x, a);
  test_forward_over_second(trace, 3, 1, x, a);
  return 0;
}
