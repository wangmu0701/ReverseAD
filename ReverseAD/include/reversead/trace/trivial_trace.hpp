#ifndef TRIVIAL_TRACE_H_
#define TRIVIAL_TRACE_H_

#include <iostream>
#include <memory>

#include "reversead/common/reversead_config.h"
#include "reversead/common/reversead_type.hpp"
#include "reversead/tape/trivial_tape.hpp"
#include "reversead/trace/abstract_trace.hpp"

namespace ReverseAD {

template<typename Base>
class TrivialTrace : public AbstractTrace<Base> {
  using AbstractTrace<Base>::num_ind;
  using AbstractTrace<Base>::num_dep;
  using AbstractTrace<Base>::num_dummy_ind;
  using AbstractTrace<Base>::num_dummy_dep;

 public:
  TrivialTrace(TrivialTrace* other,
               std::shared_ptr<TrivialTape<Base>> val_tape) {
    this->op_tape = other->op_tape;
    this->loc_tape = other->loc_tape;
    this->val_tape = val_tape;
    this->coval_tape = other->coval_tape;
    this->num_ind = other->num_ind;
    this->num_dep = other->num_dep;
#ifdef ENABLE_REVERSEAD_MPI
    this->sr_info_tape = other->sr_info_tape;
    this->comm_loc_tape = other->comm_loc_tape;
    this->num_dummy_ind = other->num_dummy_ind;
    this->num_dummy_dep = other->num_dummy_dep;
#endif
  }
  // Default c-tor and d-tor
  TrivialTrace() {
    op_tape = std::make_shared<TrivialTape<opbyte>>();
    loc_tape = std::make_shared<TrivialTape<locint>>();
    val_tape = std::make_shared<TrivialTape<Base>>();
    coval_tape = std::make_shared<TrivialTape<double>>();
#ifdef ENABLE_REVERSEAD_MPI
    sr_info_tape = std::make_shared<TrivialTape<SendRecvInfo>>();
    comm_loc_tape = std::make_shared<TrivialTape<locint>>();
#endif
  }
  ~TrivialTrace() {
    op_tape.reset();
    loc_tape.reset();
    val_tape.reset();
    coval_tape.reset();
#ifdef ENABLE_REVERSEAD_MPI
    sr_info_tape.reset();
    comm_loc_tape.reset();
#endif
  }

  // Write
  inline void put_op(const opbyte& opcode) {
    op_tape->put(opcode);
  }
  inline void put_loc(const locint& loc) {
    loc_tape->put(loc);
  }
  inline void put_val(const Base& val) {
    val_tape->put(val);
  }
  inline void put_coval(const double& coval) {
    coval_tape->put(coval);
  }

  inline void put_sr_info(const SendRecvInfo& sr_info) {
    sr_info_tape->put(sr_info);
  }
  inline void put_comm_loc(const locint& comm_loc) {
    std::cout << "trace->put_comm_loc : " << comm_loc << std::endl;
    comm_loc_tape->put(comm_loc);
  }
  inline void init_comm_forward() {
    sr_info_tape->init_forward();
    comm_loc_tape->init_forward();
  }
  inline void end_comm_forward() {
    sr_info_tape->end_forward();
    comm_loc_tape->end_forward();
  }
  inline bool has_next_sr_info_f() {
    return sr_info_tape->has_next_f();
  }
  inline SendRecvInfo get_next_sr_info_f() {
    return sr_info_tape->get_next_f();
  }
  inline locint get_next_comm_loc_f() {
    return comm_loc_tape->get_next_f();
  }
 
  // forward sweep
  inline void init_forward() {
    op_tape->init_forward();
    loc_tape->init_forward();
    val_tape->init_forward();
    coval_tape->init_forward();
  }
  inline void end_forward() {
    op_tape->end_forward();
    loc_tape->end_forward();
    val_tape->end_forward();
    coval_tape->end_forward();
  }
  inline opbyte get_next_op_f() {
    return op_tape->get_next_f();
  }
  inline locint get_next_loc_f() {
    return loc_tape->get_next_f();
  }
  inline Base get_next_val_f() {
    return val_tape->get_next_f();
  }
  inline double get_next_coval_f() {
    return coval_tape->get_next_f();
  }

  // reverse sweep
  inline void init_reverse() {
    op_tape->init_reverse();
    loc_tape->init_reverse();
    val_tape->init_reverse();
    coval_tape->init_reverse();
  }
  inline void end_reverse() {
    op_tape->end_reverse();
    loc_tape->end_reverse();
    val_tape->end_reverse();
    coval_tape->end_reverse();
  }
  inline opbyte get_next_op_r() {
    return op_tape->get_next_r();
  }
  inline locint get_next_loc_r() {
    return loc_tape->get_next_r();
  }
  inline Base get_next_val_r() {
    return val_tape->get_next_r();
  }
  inline double get_next_coval_r() {
    return coval_tape->get_next_r();
  }

  // for debug
  inline void dump_trace() {
    std::cout << "Op tape:" << std::endl;
    op_tape->dump_tape();
    std::cout << "Loc tape:" << std::endl;
    loc_tape->dump_tape();
    std::cout << "Val tape:" << std::endl;
    val_tape->dump_tape();
    std::cout << "Const tape:" << std::endl;
    coval_tape->dump_tape();
    if (sr_info_tape) {
      std::cout << "SendRecvInfo tape:" << std::endl;
      sr_info_tape->dump_tape();
      std::cout << "Comm Info tape:" << std::endl;
      comm_loc_tape->dump_tape();
    }
  }
   
  inline void dump_trace(Logger& logger) {
    logger << "Op tape:" << std::endl;
    op_tape->dump_tape(logger);
    logger << "Loc tape:" << std::endl;
    loc_tape->dump_tape(logger);
    logger << "Val tape:" << std::endl;
    val_tape->dump_tape(logger);
    logger << "Const tape:" << std::endl;
    coval_tape->dump_tape(logger);
    if (sr_info_tape) {
      std::cout << "SendRecvInfo tape:" << std::endl;
      sr_info_tape->dump_tape();
      std::cout << "Comm Info tape:" << std::endl;
      comm_loc_tape->dump_tape();
    }
  }
 private:
  std::shared_ptr<TrivialTape<opbyte>> op_tape;
  std::shared_ptr<TrivialTape<locint>> loc_tape;
  std::shared_ptr<TrivialTape<Base>> val_tape;
  std::shared_ptr<TrivialTape<double>> coval_tape;
  std::shared_ptr<TrivialTape<SendRecvInfo>> sr_info_tape;
  std::shared_ptr<TrivialTape<locint>> comm_loc_tape;
};

} // namespace ReverseAD

#endif // TRIVIAL_TRACE_H_
