#ifndef TRIVIAL_TRACE_H_
#define TRIVIAL_TRACE_H_

#include "src/core/reversead.hpp"
#include "src/tape/abstract_tape.hpp"
#include "src/tape/trivial_tape.hpp"
#include "src/trace/abstract_trace.hpp"

namespace ReverseAD {

class TrivialTrace : public AbstractTrace {
 public:
  // Default c-tor and d-tor
  TrivialTrace();
  ~TrivialTrace();

  // Write
  void putOp(opbyte opcode);
  void putLoc(locint loc);
  void putVal(double val);
  
  // forward sweep
  void init_forward();
  void end_forward();
  opbyte get_next_op_f();
  locint get_next_loc_f();
  double get_next_val_f();
  void rewrite_curr_loc_f(locint loc);

  // reverse sweep
  void init_reverse();
  void end_reverse();
  opbyte get_next_op_r();
  locint get_next_loc_r();
  double get_next_val_r();
 
 private:
  TrivialTape<opbyte> *op_tape;
  TrivialTape<locint> *loc_tape;
  TrivialTape<double> *val_tape;
};

} // namespace ReverseAD

#endif // TRIVIAL_TRACE_H_
