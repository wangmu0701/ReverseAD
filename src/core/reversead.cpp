#include <iostream>

#include "src/core/reversead.hpp"
#include "src/core/opcodes.hpp"
#include "src/trace/abstract_trace.hpp"
#include "src/trace/trivial_trace.hpp"

namespace ReverseAD {

  AbstractTrace *global_trace;
  bool is_tracing = false;
  locint curr_loc = 0;
  void trace_on() {
    global_trace = new TrivialTrace();
    is_tracing = true;
    curr_loc = 0;
    global_trace->put_op(start_of_tape);
  }

  locint get_next_loc() {
    return curr_loc++;
  }

  AbstractTrace* trace_off() {
    global_trace->put_op(end_of_tape);
    is_tracing = false;
    return global_trace;
  }
  void trace_done(AbstractTrace* trace) {
    delete trace;
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
} // ReverseAD
