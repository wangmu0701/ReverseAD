#include <cassert>

#include "reversead/activetype/base_active.hpp"
#include "reversead/checkpointing/iterative_func_cond.hpp"

namespace ReverseAD {

IterativeFuncCond::IterativeFuncCond(
    size_t x_num, size_t t_num, size_t y_num,
    void (*set_up)(),
    void (*tear_down)(),
    void (*initial_step)(adouble*, size_t, adouble*, size_t),
    void (*iteration_step)(adouble*, size_t),
    void (*final_step)(adouble*, size_t, adouble*, size_t),
    bool (*while_condition)(const adouble* const, size_t)) :
  IterativeFuncBase(x_num, t_num, y_num, set_up, tear_down,
                    initial_step, iteration_step, final_step) {

  _while_condition = while_condition; 
}

bool IterativeFuncCond::iteration_done(adouble* t_values, size_t t_num) {
  assert(t_num == _t_num);
  return !(*_while_condition)(t_values, _t_num);
}

} // namespace ReverseAD
