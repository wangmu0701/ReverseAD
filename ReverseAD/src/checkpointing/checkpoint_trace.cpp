#include <memory>

#include "reversead/checkpointing/checkpoint_trace.hpp"
#include "reversead/common/reversead_type.hpp"
#include "reversead/common/runtime_env.hpp"
#include "reversead/tape/trivial_tape.hpp"
#include "reversead/tape/disk_tape.hpp"

namespace ReverseAD {

CheckpointTrace::CheckpointTrace() {
  _checkpoint_num = 0;
  _tape_x_num = std::make_shared<TrivialTape<size_t>>();
  _tape_iter_num = std::make_shared<TrivialTape<size_t>>();
  _tape_x_values = std::make_shared<VirtualTape<double>>();
  _tape_x_locint = std::make_shared<VirtualTape<locint>>();
  _tape_runtime_env = std::make_shared<TrivialTape<RuntimeEnv>>();
  _tape_x_num->init_taping();
  _tape_iter_num->init_taping();
  _tape_x_values->init_taping();
  _tape_x_locint->init_taping();
  _tape_runtime_env->init_taping();
}

void CheckpointTrace::end_checkpointing() {
  _tape_x_num->end_taping();
  _tape_iter_num->end_taping();
  _tape_x_values->end_taping();
  _tape_x_locint->end_taping();
  _tape_runtime_env->end_taping();
}
void CheckpointTrace::init_reverse() {
  _tape_x_num->init_reverse();
  _tape_iter_num->init_reverse();
  _tape_x_values->init_reverse();
  _tape_x_locint->init_reverse();
  _tape_runtime_env->init_reverse();
}
void CheckpointTrace::end_reverse() {
  _tape_x_num->end_reverse();
  _tape_iter_num->end_reverse();
  _tape_x_values->end_reverse();
  _tape_x_locint->end_reverse();
  _tape_runtime_env->end_reverse();
}

size_t CheckpointTrace::make_checkpoint(
    adouble* x, size_t x_num, std::shared_ptr<RuntimeEnv>& runtime_env) {
  _checkpoint_num++; 
  _tape_x_num->put(x_num);
  for (size_t i = 0; i < x_num; i++) {
    _tape_x_values->put(x[i].getVal());
    _tape_x_locint->put(x[i].getLoc());
  }
  _tape_runtime_env->put(*(runtime_env.get()));
  return _checkpoint_num;
}

void CheckpointTrace::set_iteration_num(size_t iter_num) {
  _tape_iter_num->put(iter_num);
}
size_t CheckpointTrace::get_iteration_num() {
  return _tape_iter_num->get_next_r();
}
size_t CheckpointTrace::get_checkpoint(
   adouble* x, size_t x_num, std::shared_ptr<RuntimeEnv>& runtime_env) {
  if (_tape_x_num->get_next_r() != x_num) {
    std::cerr << "checkpointing x_num mismatch" << std::endl;
  }

  // In place construction
  for (size_t i = x_num - 1; i >= 0; i--) {
    new(&x[i]) adouble(_tape_x_values->get_next_r(),
                       _tape_x_locint->get_next_r());
  }
  // build shared_ptr form a copy constructor
  runtime_env = std::make_shared<RuntimeEnv>(_tape_runtime_env->get_next_r());
  return --_checkpoint_num;
}

void CheckpointTrace::dump_trace() const {
  std::cout << "num of checkpoints : " << _checkpoint_num << std::endl;
  _tape_x_num->dump_tape();
  _tape_iter_num->dump_tape();
  _tape_x_values->dump_tape();
  _tape_x_locint->dump_tape();
  _tape_runtime_env->dump_tape();
}
} // namespace ReverseAD
