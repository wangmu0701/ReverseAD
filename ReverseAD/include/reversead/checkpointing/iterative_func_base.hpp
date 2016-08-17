#ifndef REVERSEAD_ITERATIVE_FUNC_BASE_H_
#define REVERSEAD_ITERATIVE_FUNC_BASE_H_

#include <cstddef>

#include "reversead/activetype/base_active.hpp"
#include "reversead/algorithm/derivative_tensor.hpp"

namespace ReverseAD {

// In ideal, IterativeFunc should provide both plain and overloaded
// function evaluation. But, since C++ does not support template function
// overload. To do that requires the user to registrate two sets of function
// pointers. So for now, this class only consider overloaded type.
class IterativeFuncBase {
 public:
  IterativeFuncBase(size_t x_num, size_t t_num, size_t y_num,
                    void (*set_up)(),
                    void (*tear_down)(),
                    void (*initial_step)(adouble*, size_t, adouble*, size_t),
                    void (*iteration_step)(adouble*, size_t),
                    void (*final_step)(adouble*, size_t, adouble*, size_t)); 

  virtual void iteration_init() {}
  virtual bool iteration_done(adouble*, size_t) = 0;

  void run(double*, size_t, double*, size_t);

  std::shared_ptr<DerivativeTensor<size_t, double>> compute(
      double*, size_t, size_t);
  
  void set_min_op_per_cp(size_t min_op_per_cp);

 protected:
  size_t _x_num;
  size_t _t_num;
  size_t _y_num;
  size_t _min_op_per_cp; // minimum ops per checkpoint

  void (*_set_up)();
  void (*_tear_down)();
  void (*_initial_step)(adouble*, size_t, adouble* , size_t);
  void (*_iteration_step)(adouble*, size_t);
  void (*_final_step)(adouble*, size_t, adouble*, size_t);
};

} // namespace ReverseAD

#endif // REVERSEAD_ITERATIVE_FUNC_BASE_H_
