#include <iostream>

#include "reversead/reversead_base.hpp"
#include "reversead/opcodes.hpp"
#include "reversead/trace/trivial_trace.hpp"

namespace ReverseAD {

  TrivialTrace* global_trace;
  bool is_tracing = false;
  locint curr_loc = 0;
  locint curr_ind_loc = 0;
  locint curr_dummy_loc = 0;
  int rank = 0;
  void trace_on() {
    global_trace = new TrivialTrace();
    is_tracing = true;
    curr_loc = BASE_LOC;
    curr_dummy_loc = BASE_LOC - 1;
    // independent location begins with 1 so that null_loc can be 0
    curr_ind_loc = 1;
    global_trace->put_op(start_of_tape);
  }

  locint get_next_loc() {
    locint ret = curr_loc++;
    ret = (ret << RANK_SHIFT) | (rank & RANK_BASE); 
    return ret;
  }

  locint get_next_ind_loc() {
    locint ret = curr_ind_loc++;
    ret = (ret << RANK_SHIFT) | (rank & RANK_BASE);
    return ret;
  }

  locint get_next_dummy_loc() {
    locint ret = curr_dummy_loc--;
    ret = (ret << RANK_SHIFT) | (rank & RANK_BASE);
    return ret;
  }

  void logging_on() {
    log.reset_info(&(std::cout));   
  }

  TrivialTrace* trace_off() {
    log.warning << "number of indepent = " << curr_ind_loc - 1 << std::endl;
    log.warning << "number of intermediate = " << curr_loc-BASE_LOC << std::endl;
    if (curr_loc >= BASE_LOC * 2) {
      log.fatal << "Overflow in intermedite indexing" << std::endl;
    }
    global_trace->put_op(end_of_tape);
    is_tracing = false;
    return global_trace;
  }

  void trace_put(opbyte op) {
    if (is_tracing) {
      global_trace->put_op(op);
    }
  }

  void trace_put(opbyte op, locint res, locint arg) {
    if (is_tracing) {
      global_trace->put_op(op);
      global_trace->put_loc(arg);
      global_trace->put_loc(res);
    }
  }
  void trace_put(opbyte op, locint res, locint arg1, locint arg2) {
    if (is_tracing) {
      global_trace->put_op(op);
      global_trace->put_loc(arg1);
      global_trace->put_loc(arg2);
      global_trace->put_loc(res);
    }
  }
  void trace_put(opbyte op, locint res, double val) {
    if (is_tracing) {
      global_trace->put_op(op);
      global_trace->put_val(val);
      global_trace->put_loc(res);
    }
  }
  void trace_put(opbyte op, locint res, locint arg, double val) {
    if (is_tracing) {
      global_trace->put_op(op);
      global_trace->put_val(val);
      global_trace->put_loc(arg);
      global_trace->put_loc(res);
    }
  }
  void trace_put(opbyte op, locint res, locint arg1, locint arg2,
                 double val1, double val2) {
    if (is_tracing) {
      global_trace->put_op(op);
      global_trace->put_val(val1);
      global_trace->put_val(val2);
      global_trace->put_loc(arg1);
      global_trace->put_loc(arg2);
      global_trace->put_loc(res);
    }
  }
} // ReverseAD
