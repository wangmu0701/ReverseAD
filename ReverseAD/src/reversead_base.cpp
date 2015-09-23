#include <iostream>

#include "reversead/reversead_base.hpp"
#include "reversead/opcodes.hpp"
#include "reversead/trace/trivial_trace.hpp"

namespace ReverseAD {

  TrivialTrace* global_trace;
  bool is_tracing = false;
  locint curr_loc = 0;
  locint curr_ind_loc = 0;
  int rank = 0;
  void trace_on() {
    global_trace = new TrivialTrace();
    is_tracing = true;
    curr_loc = BASE_LOC;
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

  TrivialTrace* trace_off() {
    std::cout << "number of indepent = " << curr_ind_loc - 1 << std::endl;
    std::cout << "number of intermediate = " << curr_loc-BASE_LOC << std::endl;
    global_trace->put_op(end_of_tape);
    is_tracing = false;
    return global_trace;
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
