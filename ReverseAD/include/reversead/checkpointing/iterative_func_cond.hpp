#ifndef REVERSEAD_ITERATIVE_FUNC_COND_H_
#define REVERSEAD_ITERATIVE_FUNC_COND_H_

#include "reversead/checkpointing/iterative_func_base.hpp"

namespace ReverseAD {

class IterativeFuncCond : public IterativeFuncBase {
 public:
  IterativeFuncCond(size_t x_num, size_t t_num, size_t y_num,
                    void (*set_up)(),
                    void (*tear_down)(),
                    void (*initial_step)(adouble*, size_t, adouble*, size_t),
                    void (*iteration_step)(adouble*, size_t),
                    void (*final_step)(adouble*, size_t, adouble*, size_t),
                    bool (*while_condition)(const adouble* const, size_t));

  bool iteration_done(adouble*, size_t) override final;

 private:
  bool (*_while_condition)(const adouble* const t, size_t t_num);
};

} // namespace ReverseAD

#endif // REVERSEAD_ITERATIVE_FUNC_COND_H_
