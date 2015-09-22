#ifndef REVERSE_AD_BASE_H_
#define REVERSE_AD_BASE_H_

#define NULL_LOC 0

namespace ReverseAD {

  class TrivialTrace;

  typedef unsigned int opbyte;
  typedef unsigned int locint;

  void trace_on();
  locint get_next_loc();
  TrivialTrace* trace_off();
  
  void trace_put(opbyte, locint, locint);
  void trace_put(opbyte, locint, locint, locint);
  void trace_put(opbyte, locint, double);
  void trace_put(opbyte, locint, locint, double);
  void trace_put(opbyte, locint, locint, locint, double, double);
} // namespace ReverseAD

#endif // REVERSE_AD_BASE_H_
