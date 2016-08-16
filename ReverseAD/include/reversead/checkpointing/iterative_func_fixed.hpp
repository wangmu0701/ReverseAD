#ifndef REVERSEAD_ITERATIVE_FUNC_FIXED_H_
#define REVERSEAD_ITERATIVE_FUNC_FIXED_H_

#include "reversead/activetype/base_active.hpp"
#include "reversead/algorithm/derivative_tensor.hpp"

namespace ReverseAD {

// A special version of iterative function that the number of iteration is fixed
// So instead of setting a termindate condition, we only need to set num_iter
class IterativeFuncFixed {
 public:
  IterativeFuncFixed(size_t x_num, size_t t_num, size_t y_num,
                     void (*set_up)(adouble*, size_t, adouble*, size_t),
                     void (*tear_down)(adouble*, size_t, adouble*, size_t),
                     void (*run)(adouble*, size_t),
                     size_t num_iter);
  void run(double*, size_t, double*, size_t);
  std::shared_ptr<DerivativeTensor<size_t, double>> compute(
      double*, size_t, double*, size_t, size_t);
 
  void set_min_op_per_cp(size_t min_op_per_cp);
 private:
  size_t _x_num;
  size_t _t_num;
  size_t _y_num;
  size_t _num_iter;
  size_t _min_op_per_cp; // minimum ops per checkpoint

  void (*_set_up)(adouble* x_values, size_t x_num, adouble* t, size_t t_num);
  void (*_tear_down)(adouble* t, size_t t_num, adouble* y_values, size_t y_num);
  void (*_run)(adouble* t, size_t t_num);
};

} // namespace ReverseAD

#endif // REVERSEAD_ITERATIVE_FUNC_FIXED_H_
