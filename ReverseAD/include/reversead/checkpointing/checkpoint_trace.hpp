#ifndef REVERSEAD_CHECKPOINT_TRACE_H_
#define REVERSEAD_CHECKPOINT_TRACE_H_

#include "reversead/activetype/base_active.hpp"
#include "reversead/common/reversead_type.hpp"
#include "reversead/common/runtime_env.hpp"
#include "reversead/tape/trivial_tape.hpp"

namespace ReverseAD {

class CheckpointTrace {
 public:
  CheckpointTrace();
  ~CheckpointTrace() = default;

  void end_checkpointing();
  void init_reverse();
  void end_reverse();
  // the return value is the current number of checkpoints
  size_t make_checkpoint(adouble* x, size_t x_num,
                       std::shared_ptr<RuntimeEnv>& _runtime_env);
  void set_iteration_num(size_t);
  size_t get_checkpoint(adouble* x, size_t x_num,
                      std::shared_ptr<RuntimeEnv>& _runtime_env);
  size_t get_iteration_num();
  void dump_trace() const;
 private:
  size_t _checkpoint_num;
  std::shared_ptr<TrivialTape<size_t>> _tape_x_num;
  std::shared_ptr<TrivialTape<size_t>> _tape_iter_num;
  std::shared_ptr<VirtualTape<double>> _tape_x_values;
  std::shared_ptr<VirtualTape<locint>> _tape_x_locint;
  std::shared_ptr<TrivialTape<RuntimeEnv>> _tape_runtime_env;
};

} //namespace ReverseAD

#endif // REVERSEAD_CHECKPOINT_TRACE_H
