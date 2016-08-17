#ifndef REVERSEAD_ITERATIVE_FUNC_FIXED_H_
#define REVERSEAD_ITERATIVE_FUNC_FIXED_H_

#include "reversead/checkpointing/iterative_func_base.hpp"

namespace ReverseAD {

// A special version of iterative function that the number of iteration is fixed
// So instead of setting a termindate condition, we only need to set num_iter
class IterativeFuncFixed : public IterativeFuncBase {
 public:
  IterativeFuncFixed(size_t x_num, size_t t_num, size_t y_num,
                     void (*set_up)(),
                     void (*tear_down)(),
                     void (*initial_step)(adouble*, size_t, adouble*, size_t),
                     void (*iteration_step)(adouble*, size_t),
                     void (*final_step)(adouble*, size_t, adouble*, size_t),
                     size_t max_num_iter);

  void iteration_init() override final;
  bool iteration_done(adouble*, size_t) override final;
 private:
  size_t _max_num_iter;
  size_t _curr_iter;
};

} // namespace ReverseAD

#endif // REVERSEAD_ITERATIVE_FUNC_FIXED_H_
