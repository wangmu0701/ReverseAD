#include <iostream>

#include "reversead/activetype/base_active.hpp"
#include "reversead/algorithm/base_reverse_hessian.hpp"
#include "reversead/common/reversead_base.hpp"
#include "reversead/common/runtime_env.hpp"
#include "reversead/checkpointing/iterative_func.hpp"
#include "reversead/checkpointing/checkpoint_trace.hpp"

namespace ReverseAD {

locint kMIN_OP_PER_CP = 100000000;

IterativeFunc::IterativeFunc(
    int x_num, int y_num, int t_num,
    void (*set_up)(adouble*, int, adouble*, int),
    void (*tear_down)(adouble*, int, adouble*, int),
    void (*run)(adouble*, int),
    bool (*while_condition)(const adouble* const, int)) {
  _x_num = x_num;
  _y_num = y_num;
  _t_num = t_num;
  _set_up = set_up;
  _tear_down = tear_down;
  _run = run;
  _while_condition = while_condition; 
}

void IterativeFunc::run(double* x_values, int x_num,
                        double* y_values, int y_num) {
  adouble* x_adouble = new adouble[_x_num];
  adouble* y_adouble = new adouble[_y_num];
  adouble* t_adouble = new adouble[_t_num];
  for (int i = 0; i < _x_num; i++) {
    x_adouble[i] = x_values[i];
  }
  (*_set_up)(x_adouble, _x_num, t_adouble, _t_num);
  while((*_while_condition)(t_adouble, _t_num)) {
    (*_run)(t_adouble, _t_num);
  }
  (*_tear_down)(t_adouble, _t_num, y_adouble, _y_num);
  for (int i = 0; i < _y_num; i++) {
    y_values[i] = y_adouble[i].getVal();
  }
}

std::shared_ptr<DerivativeTensor<int, double>> IterativeFunc::compute(
    double* x_values, int x_num,
    double* y_values, int y_num) {
  CheckpointTrace cp_trace;

  //TODO(muwang)
  // first recompute the function, no tracing
  // but record the initial values for each step, and also runtime env.
  adouble* x_adouble = new adouble[_x_num];
  adouble* y_adouble = new adouble[_y_num];
  adouble* t_adouble = new adouble[_t_num];
  // set_up trace, store initial value and RuntimeEnv
  std::shared_ptr<RuntimeEnv> runtime_env = std::make_shared<RuntimeEnv>();
  runtime_env->init();
  cp_trace.make_checkpoint(x_adouble, _x_num, runtime_env);
  runtime_env_on(runtime_env);
  for (int i = 0; i < _x_num; i++) {
    x_adouble[i] <<= x_values[i];
  }
  (*_set_up)(x_adouble, _x_num, t_adouble, _t_num);
  runtime_env_off();
  cp_trace.set_iteration_num(0); // 0 for set_up 
  // set_up trace done, get RuntimeEnv
  locint prev_loc = runtime_env->curr_loc;
  bool is_tracing = false;
  int iter_num = 0;
  while((*_while_condition)(t_adouble, _t_num)) {
    // iterative trace, store initial values and RuntimeEnv
    if (!is_tracing) {
      cp_trace.make_checkpoint(t_adouble, _t_num, runtime_env);
      prev_loc = runtime_env->curr_loc;
      is_tracing = true;
      iter_num = 0;
    } 
    runtime_env_on(runtime_env);
    (*_run)(t_adouble, _t_num);
    iter_num++;
    runtime_env_off();
    if (runtime_env->curr_loc - prev_loc >= kMIN_OP_PER_CP) {
      cp_trace.set_iteration_num(iter_num);
      is_tracing = false;
    }
    // one around of iterative trace done, get RuntimeRnv
  }
  if (is_tracing) {
    cp_trace.set_iteration_num(iter_num);
    is_tracing = false;
    runtime_env_off();
  } 
  cp_trace.make_checkpoint(t_adouble, _t_num, runtime_env);
  runtime_env_on(runtime_env);
  (*_tear_down)(t_adouble, _t_num, y_adouble, _y_num);
  runtime_env_off();
  cp_trace.set_iteration_num(0);
  cp_trace.end_checkpointing();
  //cp_trace.dump_trace();
  // reversely evaluat the derivative
  // pass runtime env so that indexing is exactly the same
  // in BaseReverseMode, seems we don't need to hi-jack anything
  // just make it be able to reset trace.
 
  cp_trace.init_reverse(); 
  // Step 1 : get initial values and runtime for tear_down
  int cp_num = cp_trace.get_checkpoint(t_adouble, _t_num, runtime_env);
  cp_trace.get_iteration_num(); // 0
  trace_on_runtime_env<double>(runtime_env);
  (*_tear_down)(t_adouble, _t_num, y_adouble, _y_num);
  for(int i = 0; i < _y_num; i++) {
    y_adouble[i] >>= y_values[i];
  }
  std::shared_ptr<TrivialTrace<double>> trace = trace_off<double>();
  BaseReverseHessian<double> hessian(trace);
  hessian.compute_iterative();
  
  // Step 2 : get initial values and runtime for iterative_step
  while (cp_num > 1) {
    cp_num = cp_trace.get_checkpoint(t_adouble, _t_num, runtime_env);
    int iter_num = cp_trace.get_iteration_num();
    trace_on_runtime_env<double>(runtime_env);
    while (iter_num > 0) {
      (*_run)(t_adouble, _t_num);
      --iter_num;
    }
    trace = trace_off<double>();
    hessian.reset_trace(trace);
    hessian.compute_iterative();
  }
  // Step 3 : get initial values and runtime for set_up
  cp_num = cp_trace.get_checkpoint(t_adouble, _t_num, runtime_env);
  cp_trace.get_iteration_num(); // 0
  trace_on_runtime_env<double>(runtime_env);
  for (int i = 0; i < _x_num; i++) {
    x_adouble[i] <<= x_values[i];
  }
  (*_set_up)(x_adouble, _x_num, t_adouble, _t_num);
  trace = trace_off<double>();
  hessian.reset_trace(trace);
  std::shared_ptr<DerivativeTensor<int, double>> tensor =
      hessian.compute(_x_num, 0).get_tensor();
  return tensor;
}

} // namespace ReverseAD
