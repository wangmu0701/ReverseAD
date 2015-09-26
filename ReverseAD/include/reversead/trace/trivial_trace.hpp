#ifndef TRIVIAL_TRACE_H_
#define TRIVIAL_TRACE_H_

#include "reversead/reversead_base.hpp"
#include "reversead/reversead_mpi.hpp"
#include "reversead/tape/trivial_tape.hpp"
#include "reversead/trace/abstract_trace.hpp"

namespace ReverseAD {

class TrivialTrace : public AbstractTrace {
 public:
  // Default c-tor and d-tor
  TrivialTrace() {
    op_tape = new TrivialTape<opbyte>();
    loc_tape = new TrivialTape<locint>();
    val_tape = new TrivialTape<double>();
  }
  ~TrivialTrace() {
    delete op_tape;
    delete loc_tape;
    delete val_tape;
  }

  // Write
  inline void put_op(opbyte opcode) {
    op_tape->put(opcode);
  }
  inline void put_loc(locint loc) {
    loc_tape->put(loc);
  }
  inline void put_val(double val) {
    val_tape->put(val);
  }
  
  // forward sweep
  inline void init_forward() {
    op_tape->init_forward();
    loc_tape->init_forward();
    val_tape->init_forward();
  }
  inline void end_forward() {
    op_tape->end_forward();
    loc_tape->end_forward();
    val_tape->end_forward();
  }
  inline opbyte get_next_op_f() {
    return op_tape->get_next_f();
  }
  inline locint get_next_loc_f() {
    return loc_tape->get_next_f();
  }
  inline double get_next_val_f() {
    return val_tape->get_next_f();
  }
  inline void rewrite_curr_loc_f(locint loc) {
    loc_tape->rewrite_curr_f(loc);
  }

  // reverse sweep
  inline void init_reverse() {
    op_tape->init_reverse();
    loc_tape->init_reverse();
    val_tape->init_reverse();
  }
  inline void end_reverse() {
    op_tape->end_reverse();
    loc_tape->end_reverse();
    val_tape->end_reverse();
  }
  inline opbyte get_next_op_r() {
    return op_tape->get_next_r();
  }
  inline locint get_next_loc_r() {
    return loc_tape->get_next_r();
  }
  inline double get_next_val_r() {
    return val_tape->get_next_r();
  }

  // for debug
  inline void dump_trace() {
    std::cout << "Op tape:" << std::endl;
    op_tape->dump_tape();
    std::cout << "Loc tape:" << std::endl;
    loc_tape->dump_tape();
    std::cout << "Val tape:" << std::endl;
    val_tape->dump_tape();
  }
   
  inline void dump_trace(Logger& logger) {
    logger << "Op tape:" << std::endl;
    op_tape->dump_tape(logger);
    logger << "Loc tape:" << std::endl;
    loc_tape->dump_tape(logger);
    logger << "Val tape:" << std::endl;
    val_tape->dump_tape(logger);
  }
 private:
  TrivialTape<opbyte> *op_tape;
  TrivialTape<locint> *loc_tape;
  TrivialTape<double> *val_tape;
};

} // namespace ReverseAD

#endif // TRIVIAL_TRACE_H_
