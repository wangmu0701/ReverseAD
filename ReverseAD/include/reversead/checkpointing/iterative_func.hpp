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
  IterativeFunc(size_t x_num, size_t t_num, size_t y_num,
                void (*set_up)(adouble*, size_t, adouble*, size_t),
                void (*tear_down)(adouble*, size_t, adouble*, size_t),
                void (*run)(adouble*, size_t),
                bool (*while_condition)(const adouble* const, size_t));
  void run(double*, size_t, double*, size_t);
  std::shared_ptr<DerivativeTensor<size_t, double>> compute(
      double*, size_t, double*, size_t, size_t);

  void set_min_op_per_cp(size_t min_op_per_cp); 
 private:
  size_t _x_num;
  size_t _t_num;
  size_t _y_num;
  size_t _min_op_per_cp; // minimum ops per checkpoint

  void (*_set_up)(adouble* x_values, size_t x_num, adouble* t, size_t t_num);
  void (*_tear_down)(adouble* t, size_t t_num, adouble* y_values, size_t y_num);
  void (*_run)(adouble* t, size_t t_num);
  // const adouble* const make t only readable, implies no changes in loc?
  bool (*_while_condition)(const adouble* const t, size_t t_num);
};

} // namespace ReverseAD

#endif // REVERSEAD_ITERATIVE_FUNC_H_
