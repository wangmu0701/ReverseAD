#ifndef REVERSE_AD_BASE_H_
#define REVERSE_AD_BASE_H_

#include <cstdint>

#define NULL_LOC 0

#define RANK_SHIFT 16
#define RANK_BASE 0x000000000000fffful
#define BASE_LOC 0x800000000000ul

/*
#define RANK_SHIFT 8
#define RANK_BASE 0x000000ff
#define BASE_LOC 0x800000
*/

#include "reversead/util/logger.hpp"

namespace ReverseAD {

  extern Log log;

  class TrivialTrace;

  typedef uint8_t opbyte;
  typedef uint64_t locint;

  void logging_on();
  void trace_on();
  locint get_next_loc();
  locint get_next_ind_loc();
  locint get_next_dummy_loc();
  TrivialTrace* trace_off();

  void trace_declare_ind();
  void trace_declare_dep();
  void trace_put(opbyte);
  void trace_put(opbyte, locint, locint);
  void trace_put(opbyte, locint, locint, locint);
  void trace_put(opbyte, locint, double);
  void trace_put(opbyte, locint, locint, double);
  void trace_put(opbyte, locint, locint, double, double);
  void trace_put(opbyte, locint, locint, locint, double, double);

} // namespace ReverseAD

#endif // REVERSE_AD_BASE_H_
