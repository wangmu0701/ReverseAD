/* Core runtime functions for ReverseAD : tracing and indexing */

#ifndef REVERSEAD_CORE_H_
#define REVERSEAD_CORE_H_

#include <cstdint>
#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/common/runtime_env.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/util/logger.hpp"

namespace ReverseAD {

  extern Log logger; 
  extern void* global_trace;
  //extern RuntimeEnv* runtime_env;
  extern std::shared_ptr<RuntimeEnv> runtime_env;
  
  // declarions for indexing functions
  locint get_next_loc();
  locint get_next_ind_loc();
  locint get_next_dummy_loc();
  void logging_on();
  void runtime_env_on(std::shared_ptr<RuntimeEnv> _runtime_env);
  void runtime_env_off();

  template <typename Base>
  void trace_on_runtime_env(std::shared_ptr<RuntimeEnv> _runtime_env) {
    if (!std::is_pod<Base>::value) {
      std::cerr << "ReverseAD works only with POD types!" << std::endl;
    }
    global_trace = (void*)new TrivialTrace<Base>();
    ((TrivialTrace<Base>*)global_trace)->init_tracing();
    runtime_env_on(_runtime_env);
    // independent location begins with 1 so that null_loc can be 0
    ((TrivialTrace<Base>*)global_trace)->put_op(start_of_tape);
  }

  template <typename Base>
  void trace_on() {
    std::shared_ptr<RuntimeEnv> _runtime_env = std::make_shared<RuntimeEnv>();
    _runtime_env->init();
    trace_on_runtime_env<Base>(_runtime_env);
  }

  template <typename Base>
  std::shared_ptr<TrivialTrace<Base>> trace_off() {
    ((TrivialTrace<Base>*)global_trace)->put_op(end_of_tape);
    ((TrivialTrace<Base>*)global_trace)->end_tracing();
    std::shared_ptr<TrivialTrace<Base>> ret((TrivialTrace<Base>*)global_trace);
    global_trace = nullptr;
    runtime_env_off();
    return std::move(ret);
  }

  template <typename Base>
  void trace_declare_ind() {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->declare_ind();
    }
  }

  template <typename Base>
  void trace_declare_dep() {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->declare_dep();
    }
  }

  // o: opbyte
  // l: locint
  // d: double cons
  // b: Base type value
  template <typename Base>
  void trace_put_o(opbyte op) {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
    }
  }
  
  template <typename Base>
  void trace_put_oll(opbyte op, locint res, locint arg) {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }

  template <typename Base>
  void trace_put_olll(opbyte op, locint res, locint arg1, locint arg2) {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg1);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg2);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }

  template <typename Base>
  void trace_put_old(opbyte op, locint res, double coval) {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_coval(coval);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
  template <typename Base>
  void trace_put_olb(opbyte op, locint res, Base val) {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_val(val);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
  template <typename Base>
  void trace_put_olp(opbyte op, locint res, Base param) {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_param(param);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
 
  template <typename Base>
  void trace_put_olld(opbyte op, locint res, locint arg, double coval) {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_coval(coval);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
  
  template <typename Base>
  void trace_put_ollb(opbyte op, locint res, locint arg, Base val) {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_val(val);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
  
  template <typename Base>
  void trace_put_ollbd(opbyte op, locint res, locint arg,
                 Base val, double coval) {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_val(val);
      ((TrivialTrace<Base>*)global_trace)->put_coval(coval);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }

  template <typename Base>
  void trace_put_olllbb(opbyte op, locint res, locint arg1, locint arg2,
                 Base val1, Base val2) {
    if (global_trace) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_val(val1);
      ((TrivialTrace<Base>*)global_trace)->put_val(val2);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg1);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg2);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
} // namespace ReverseAD

#endif // REVERSEAD_CORE_H_
