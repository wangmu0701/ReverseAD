#ifndef TRIVIAL_TRACE_H_
#define TRIVIAL_TRACE_H_

#include "reversead/reversead_base.hpp"
#include "reversead/tape/trivial_tape.hpp"
#include "reversead/trace/abstract_trace.hpp"

namespace ReverseAD {

class TrivialTrace : public AbstractTrace {
 public:
  // Default c-tor and d-tor
  TrivialTrace();
  ~TrivialTrace();

  // Write
  inline void put_op(opbyte opcode);
  inline void put_loc(locint loc);
  inline void put_val(double val);
  
  // forward sweep
  inline void init_forward();
  inline void end_forward();
  inline opbyte get_next_op_f();
  inline locint get_next_loc_f();
  inline double get_next_val_f();
  inline void rewrite_curr_loc_f(locint loc);

  // reverse sweep
  inline void init_reverse();
  inline void end_reverse();
  inline opbyte get_next_op_r();
  inline locint get_next_loc_r();
  inline double get_next_val_r();

  // for debug
  inline void dump_trace();
   
 private:
  TrivialTape<opbyte> *op_tape;
  TrivialTape<locint> *loc_tape;
  TrivialTape<double> *val_tape;
};

} // namespace ReverseAD

#endif // TRIVIAL_TRACE_H_
