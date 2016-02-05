#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/common/runtime_env.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/trace/trivial_trace.hpp"

namespace ReverseAD {
  
  void* global_trace = nullptr;
  std::shared_ptr<RuntimeEnv> runtime_env = nullptr;
  int _disk_tape_id = 0;
  
  extern Log logger;

  locint get_next_loc() {
    if (!runtime_env) {return 0;}
    return runtime_env->get_next_loc();
  }

  locint get_next_ind_loc() {
    if (!runtime_env) {return 0;}
    return runtime_env->get_next_ind_loc();
  }

  locint get_next_dummy_loc() {
    if (!runtime_env) {return 0;}
    return runtime_env->get_next_dummy_loc();
  }

  void runtime_env_on(std::shared_ptr<RuntimeEnv> _runtime_env) {
    runtime_env = std::move(_runtime_env);
  }

  std::shared_ptr<RuntimeEnv> runtime_env_off() {
    return std::move(runtime_env);
  }
  
  // turn on some internal loggerging
  void logging_on() {
    logger.reset_info(&(std::cout));   
  }

} // namespace ReverseAD
