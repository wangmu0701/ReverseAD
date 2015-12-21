#ifndef REVERSEAD_BASE_H_
#define REVERSEAD_BASE_H_

#include <cstdint>

#include "reversead/common/reversead_type.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/util/logger.hpp"

namespace ReverseAD {

  extern Log logger; 
  extern void* global_trace;
  extern bool is_tracing;
  extern locint curr_loc;
  extern locint curr_ind_loc;
  extern locint curr_dummy_loc;
  
  // declarions for indexing functions
  locint get_next_loc();
  locint get_next_ind_loc();
  locint get_next_dummy_loc();
  void logging_on();

  template <typename Base>
  void trace_on() {
    global_trace = (void*)new TrivialTrace<Base>();
    is_tracing = true;
    curr_loc = BASE_LOC;
    curr_dummy_loc = BASE_LOC - 1;
    // independent location begins with 1 so that null_loc can be 0
    curr_ind_loc = 1;
    ((TrivialTrace<Base>*)global_trace)->put_op(start_of_tape);
  }

  template <typename Base>
  TrivialTrace<Base>* trace_off() {
    logger.info << "number of indepent = " << curr_ind_loc - 1 << std::endl;
    logger.info << "number of intermediate = " << (curr_loc-BASE_LOC) << std::endl;
    if (curr_loc >= BASE_LOC * 2) {
      logger.fatal << "Overflow in intermedite indexing" << std::endl;
    }
    ((TrivialTrace<Base>*)global_trace)->put_op(end_of_tape);
    is_tracing = false;
    return (TrivialTrace<Base>*)global_trace;
  }
  
  template <typename Base>
  void trace_declare_ind() {
    ((TrivialTrace<Base>*)global_trace)->declare_ind();
  }

  template <typename Base>
  void trace_declare_dep() {
    ((TrivialTrace<Base>*)global_trace)->declare_dep();
  }

  // o: opbyte
  // l: locint
  // d: double cons
  // b: Base type value
  template <typename Base>
  void trace_put_o(opbyte op) {
    if (is_tracing) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
    }
  }
  
  template <typename Base>
  void trace_put_oll(opbyte op, locint res, locint arg) {
    if (is_tracing) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }

  template <typename Base>
  void trace_put_olll(opbyte op, locint res, locint arg1, locint arg2) {
    if (is_tracing) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg1);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg2);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }

  template <typename Base>
  void trace_put_old(opbyte op, locint res, double coval) {
    if (is_tracing) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_coval(coval);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
  template <typename Base>
  void trace_put_olb(opbyte op, locint res, Base val) {
    if (is_tracing) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_val(val);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
  template <typename Base>
  void trace_put_olp(opbyte op, locint res, Base param) {
    if (is_tracing) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_param(param);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
 
  template <typename Base>
  void trace_put_olld(opbyte op, locint res, locint arg, double coval) {
    if (is_tracing) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_coval(coval);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
  
  template <typename Base>
  void trace_put_ollb(opbyte op, locint res, locint arg, Base val) {
    if (is_tracing) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_val(val);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
  
  template <typename Base>
  void trace_put_ollbd(opbyte op, locint res, locint arg,
                 Base val, double coval) {
    if (is_tracing) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_val(val);
      ((TrivialTrace<Base>*)global_trace)->put_coval(coval);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }

  template <typename Base>
  void trace_put_olllbb(opbyte op, locint res, locint arg1, locint arg2,
                 double val1, double val2) {
    if (is_tracing) {
      ((TrivialTrace<Base>*)global_trace)->put_op(op);
      ((TrivialTrace<Base>*)global_trace)->put_val(val1);
      ((TrivialTrace<Base>*)global_trace)->put_val(val2);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg1);
      ((TrivialTrace<Base>*)global_trace)->put_loc(arg2);
      ((TrivialTrace<Base>*)global_trace)->put_loc(res);
    }
  }
} // namespace ReverseAD

#endif // REVERSEAD_BASE_H_
