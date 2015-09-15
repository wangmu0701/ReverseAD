#ifndef REVERSE_AD_H_
#define REVERSE_AD_H_


namespace ReverseAD {
  class AbstractTrace;

  typedef unsigned int opbyte;
  typedef unsigned int locint;

  void trace_on();
  locint get_next_loc();
  AbstractTrace* trace_off();
  void trace_done(AbstractTrace* trace);
  
  void trace_put(opbyte, locint, locint);
  void trace_put(opbyte, locint, locint, locint);
  void trace_put(opbyte, locint, double);
  void trace_put(opbyte, locint, locint, double);
} // namespace ReverseAD

#endif // REVERSE_AD_H_
