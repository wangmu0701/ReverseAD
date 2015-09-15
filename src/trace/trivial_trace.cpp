#include <iostream>

#include "src/core/reversead.hpp"
#include "src/tape/abstract_tape.hpp"
#include "src/tape/trivial_tape.hpp"
#include "abstract_trace.hpp"
#include "trivial_trace.hpp"

namespace ReverseAD {

TrivialTrace::TrivialTrace() {
  op_tape = new TrivialTape<opbyte>();
  loc_tape = new TrivialTape<locint>();
  val_tape = new TrivialTape<double>();
}

TrivialTrace::~TrivialTrace() {
  delete op_tape;
  delete loc_tape;
  delete val_tape;
}

inline void TrivialTrace::put_op(opbyte opcode) {
  op_tape->put(opcode);
}
inline void TrivialTrace::put_loc(locint loc) {
  loc_tape->put(loc);
}
inline void TrivialTrace::put_val(double val) {
  val_tape->put(val);
}

inline void TrivialTrace::init_forward() {
  op_tape->init_forward();
  loc_tape->init_forward();
  val_tape->init_forward();
}

inline void TrivialTrace::end_forward() {
  op_tape->end_forward();
  loc_tape->end_forward();
  val_tape->end_forward();
}

inline opbyte TrivialTrace::get_next_op_f() {
  return op_tape->get_next_f();
}

inline void TrivialTrace::rewrite_curr_loc_f(locint loc) {
  loc_tape->rewrite_curr_f(loc);
}

inline locint TrivialTrace::get_next_loc_f() {
  return loc_tape->get_next_f();
}

inline double TrivialTrace::get_next_val_f() {
  return val_tape->get_next_f();
}

inline void TrivialTrace::init_reverse() {
  op_tape->init_reverse();
  loc_tape->init_reverse();
  val_tape->init_reverse();
}

inline void TrivialTrace::end_reverse() {
  op_tape->end_reverse();
  loc_tape->end_reverse();
  val_tape->end_reverse();
}

inline opbyte TrivialTrace::get_next_op_r() {
  return op_tape->get_next_r();
}

inline locint TrivialTrace::get_next_loc_r() {
  return loc_tape->get_next_r();
}

inline double TrivialTrace::get_next_val_r() {
  return val_tape->get_next_r();
}

inline void TrivialTrace::dump_trace() {
  std::cout << "Op tape:" << std::endl;
  op_tape->dump_tape();
  std::cout << "Loc tape:" << std::endl;
  loc_tape->dump_tape();
  std::cout << "Val tape:" << std::endl;
  val_tape->dump_tape();
}

} // namespace ReverseAD

