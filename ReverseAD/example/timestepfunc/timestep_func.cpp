/* An example showing how to use ReverseAD to evaluate derivatives for
   a timestep function.
   A timestep function iteratively does some computation until a certain
   condition is met.
     x (ind) --> t0 --> t1 --> ... --> tn (condition met) --> y (dep)
 set_up()   init()   iter()  iter() while_condition()  final()    tear_down()


   void set_up();
   void tear_down();
   void initial_step(adobule* x, size_t x_num, adouble* t, size_t t_num);
   void iteration_step(adouble* t, size_t t_num) {
   void final_step(adouble* t, size_t t_num, adouble* y, size_t y_num) {
   bool while_condition(const adouble* const t, size_t t_num) {

   IterativeFuncCond iter_func(
       ind_num, intermediate_num, dep_num,
       &set_up, &tear_down,
       &(initial_step<adouble>), &(iteration_step<adouble>),
       &(final_step<adouble>), &(while_condition<adouble>));
*/

#include <iostream>
#include <memory>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;
using ReverseAD::IterativeFuncCond;

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

void dummy_func() {}

template <typename T>
void initial_step(T* x, size_t x_num, T* t, size_t t_num) {
  t[0] = x[0];
  t[1] = x[1];
}

template <typename T>
void iteration_step(T* t, size_t t_num) {
  t[0] = t[1]+t[0];
  t[1] = t[0]*t[1];
}

template <typename T>
void final_step(T* t, size_t t_num, T* y, size_t y_num) {
  y[0] = t[1] * t[0];
}

template <typename T>
bool while_condition(const T* const t, size_t t_num) {
  return t[0] * t[1] < 10000;
}

int main() {
  double x[2] = {2, 1};
  double y;
  IterativeFuncCond iter_func_cond(
      2, 2, 1, 
      &dummy_func, &dummy_func,
      &(initial_step<adouble>), &(iteration_step<adouble>),
      &(final_step<adouble>), &(while_condition<adouble>));
  iter_func_cond.run(x, 2, &y, 1);
  std::cout << "y = " << y << std::endl;
  std::shared_ptr<DerivativeTensor<size_t, double>> i_tensor =
      iter_func_cond.compute(x, 2, 3);
  dump_tensor(i_tensor);
  return 0;
} 
