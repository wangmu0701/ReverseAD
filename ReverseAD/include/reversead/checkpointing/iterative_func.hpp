#ifndef REVERSEAD_ITERATIVE_FUNC_H_
#define REVERSEAD_ITERATIVE_FUNC_H_

#include "reversead/activetype/base_active.hpp"
#include "reversead/algorithm/derivative_tensor.hpp"

namespace ReverseAD {

// In ideal, IterativeFunc should provide both plain and overloaded
// function evaluation. But, since C++ does not support template function
// overload. To do that requires the user to registrate two sets of function
// pointers. So for now, this class only consider overloaded type.
class IterativeFunc {
 public:
  IterativeFunc(int x_num, int t_num, int y_num,
                void (*set_up)(adouble*, int, adouble*, int),
                void (*tear_down)(adouble*, int, adouble*, int),
                void (*run)(adouble*, int),
                bool (*while_condition)(const adouble* const, int));
  void run(double*, int, double*, int);
  std::shared_ptr<DerivativeTensor<int, double>> compute(
      double*, int, double*, int, int);
 
 private:
  int _x_num;
  int _t_num;
  int _y_num;

  void (*_set_up)(adouble* x_values, int x_num, adouble* t, int t_num);
  void (*_tear_down)(adouble* t, int t_num, adouble* y_values, int y_num);
  void (*_run)(adouble* t, int t_num);
  // const adouble* const make t only readable, implies no changes in loc?
  bool (*_while_condition)(const adouble* const t, int t_num);
};

} // namespace ReverseAD

#endif // REVERSEAD_ITERATIVE_FUNC_H_
