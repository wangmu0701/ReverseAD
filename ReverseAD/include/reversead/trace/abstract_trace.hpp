#ifndef ABSTRACT_TRACE_H_
#define ABSTRACT_TRACE_H_

#include "reversead/reversead_base.hpp"

namespace ReverseAD {

class AbstractTrace {
 public:
  virtual ~AbstractTrace() {}

  inline virtual void put_op(opbyte) = 0;
  inline virtual void put_loc(locint) = 0;
  inline virtual void put_val(double) = 0;
  
  // forward sweep
  virtual void init_forward() = 0;
  virtual void end_forward() = 0;
  virtual opbyte get_next_op_f() = 0;
  virtual locint get_next_loc_f() = 0;
  virtual double get_next_val_f() = 0;
  virtual void rewrite_curr_loc_f(locint) = 0;

  // reverse sweep
  virtual void init_reverse() = 0;
  virtual void end_reverse() = 0;
  virtual opbyte get_next_op_r() = 0;
  virtual locint get_next_loc_r() = 0;
  virtual double get_next_val_r() = 0;

  // for debug
  virtual void dump_trace() = 0;
};

} // namespace ReverseAD

#endif // ABSTRACT_TRACT_H_
