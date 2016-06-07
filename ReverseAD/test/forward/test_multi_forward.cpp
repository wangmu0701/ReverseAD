#include <memory>
#include <iostream>
#include "reversead/reversead.hpp"
#include "reversead/forwardtype/single_forward.hpp"
#include "reversead/forwardtype/multi_forward.hpp"
#include "reversead/driver/forward_over_reverse.hpp"

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


void check_forward_over_second(
    std::shared_ptr<TrivialTrace<double>> trace,
    int ind_num, int dep_num,
    double ind_init_values[],
    double adjoint_init_values[][5]) {
  BaseReverseThird<double> third(trace);
  std::shared_ptr<DerivativeTensor<int, double>> tensor =
      third.compute(ind_num, dep_num).get_tensor();
  int t_size;
  int** t_tind;
  double* t_value;
  tensor->get_internal_coordinate_list(0, 3, &t_size, &t_tind, &t_value);
//  std::cout << "t_size = " << t_size << std::endl;
//  for (int i=0; i<t_size; i++) {
//    std::cout<<"T["<<t_tind[i][0]<<", "<<t_tind[i][1]
//             <<", "<<t_tind[i][2] <<"] = "<<t_value[i]<<std::endl;
//  }
  double** tv = new double*[ind_num];
  double** ctv = new double*[ind_num];
  for (int i=0; i<ind_num; i++) {
    tv[i] = new double[ind_num];
    ctv[i] = new double[ind_num];
  }
/*
  forward_over_second(trace, ind_num, dep_num,
      ind_init_values, adjoint_init_values, &tv);
*/
  void* raw_memory = ::operator new[] (ind_num * sizeof(MultiForward<5>));
  MultiForward<5>* x = static_cast<MultiForward<5>*>(raw_memory);
  for (int i = 0; i < ind_num; i++) {
    new(&x[i]) MultiForward<5>(ind_init_values[i], adjoint_init_values[i]);
  }
  std::shared_ptr<TrivialTrace<MultiForward<5>>> new_trace = 
      BaseFunctionReplay::replay_forward<double, MultiForward<5>>(
          trace, x, ind_num);

  BaseReverseHessian<MultiForward<5>> hessian(new_trace);
  hessian.compute(ind_num, dep_num);
  std::shared_ptr<DerivativeTensor<int, MultiForward<5>>> m_tensor =
      hessian.get_tensor();
  int size;
  int** tind;
  MultiForward<5>* values;
  m_tensor->get_internal_coordinate_list(0, 2, &size, &tind, &values);
  for (int i = 0; i < size; i++) {
    std::cout << "H["<< tind[i][0]<<", "<<tind[i][1] << "] = "
              << values[i] << std::endl;
  }
}
int main() {
  std::shared_ptr<TrivialTrace<double>> trace = foo<double>(1,2,3);
  double x[3] = {1, 2, 3};
  double a[3][5] = {{10, 4, 1, 0, 0},
                    {20, 5, 0, 1, 0},
                    {30, 6, 0, 0, 1}};
  check_forward_over_second(trace, 3, 1, x, a);
  trace = bar<double>(1, 2, 3);
  check_forward_over_second(trace, 3, 1, x, a);
  return 0;
}
