#ifndef TRIVIAL_TRACE_H_
#define TRIVIAL_TRACE_H_

#include <iostream>
#include <memory>

#include "reversead/common/reversead_config.h"
#include "reversead/common/reversead_type.hpp"
#include "reversead/tape/trivial_tape.hpp"
#include "reversead/tape/disk_tape.hpp"
#include "reversead/trace/abstract_trace.hpp"

namespace ReverseAD {

#ifdef ENABLE_DISK_TAPE
template <typename T>
using VirtualTape = DiskTape<T>;
#else
template <typename T>
using VirtualTape = TrivialTape<T>;
#endif

template<typename Base>
class TrivialTrace : public AbstractTrace<Base> {
  using AbstractTrace<Base>::num_ind;
  using AbstractTrace<Base>::num_dep;
  using AbstractTrace<Base>::num_dummy_ind;
  using AbstractTrace<Base>::num_dummy_dep;
  using AbstractTrace<Base>::num_param;

 public:
  template <typename OldBase, typename NewBase>
  friend std::shared_ptr<TrivialTrace<NewBase>> copy_tape(
    const std::shared_ptr<TrivialTrace<OldBase>>& other,
    const std::shared_ptr<VirtualTape<NewBase>>& val_tape,
    const std::shared_ptr<VirtualTape<NewBase>>& param_tape);
  template <typename OldBase, typename NewBase>
  friend std::shared_ptr<TrivialTrace<NewBase>> copy_tape(
    const std::shared_ptr<TrivialTrace<OldBase>>& other,
    const std::shared_ptr<VirtualTape<NewBase>>& val_tape);

  // Default c-tor and d-tor
  TrivialTrace() {
    op_tape = std::make_shared<VirtualTape<opbyte>>();
    loc_tape = std::make_shared<VirtualTape<locint>>();
    val_tape = std::make_shared<VirtualTape<Base>>();
    param_tape = std::make_shared<VirtualTape<Base>>();
    coval_tape = std::make_shared<VirtualTape<double>>();
  }
  ~TrivialTrace() {
    op_tape.reset();
    loc_tape.reset();
    val_tape.reset();
    param_tape.reset();
    coval_tape.reset();
  }

  void init_tracing() {
    op_tape->init_taping();
    loc_tape->init_taping();
    val_tape->init_taping();
    param_tape->init_taping();
    coval_tape->init_taping();
  }
  void end_tracing() {
    op_tape->end_taping();
    loc_tape->end_taping();
    val_tape->end_taping();
    param_tape->end_taping();
    coval_tape->end_taping();
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
  inline void put_param(const Base& param) {
    num_param++;
    param_tape->put(param);
  }
  inline void put_coval(const double& coval) {
    coval_tape->put(coval);
  }

  // forward sweep
  inline void init_forward() {
    op_tape->init_forward();
    loc_tape->init_forward();
    val_tape->init_forward();
    param_tape->init_forward();
    coval_tape->init_forward();
  }
  inline void end_forward() {
    op_tape->end_forward();
    loc_tape->end_forward();
    val_tape->end_forward();
    param_tape->end_forward();
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
  inline Base get_next_param_f() {
    return param_tape->get_next_f();
  }
  inline double get_next_coval_f() {
    return coval_tape->get_next_f();
  }

  // reverse sweep
  inline void init_reverse() {
    op_tape->init_reverse();
    loc_tape->init_reverse();
    val_tape->init_reverse();
    param_tape->init_reverse();
    coval_tape->init_reverse();
  }
  inline void end_reverse() {
    op_tape->end_reverse();
    loc_tape->end_reverse();
    val_tape->end_reverse();
    param_tape->end_reverse();
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
  inline Base get_next_param_r() {
    return param_tape->get_next_r();
  }
  inline double get_next_coval_r() {
    return coval_tape->get_next_r();
  }


  // for debug
  inline void dump_trace_info() {
  }

  inline void dump_trace() {
    std::cout << "Op tape:" << std::endl;
    op_tape->dump_tape();
    std::cout << "Loc tape:" << std::endl;
    loc_tape->dump_tape();
    std::cout << "Val tape:" << std::endl;
    val_tape->dump_tape();
    std::cout << "Param tape:" << std::endl;
    param_tape->dump_tape();
    std::cout << "Const tape:" << std::endl;
    coval_tape->dump_tape();
  }
   
 private:
  std::shared_ptr<VirtualTape<opbyte>> op_tape;
  std::shared_ptr<VirtualTape<locint>> loc_tape;
  std::shared_ptr<VirtualTape<Base>> val_tape;
  std::shared_ptr<VirtualTape<Base>> param_tape;
  std::shared_ptr<VirtualTape<double>> coval_tape;
};

template <typename OldBase, typename NewBase>
std::shared_ptr<TrivialTrace<NewBase>> copy_tape(
      const std::shared_ptr<TrivialTrace<OldBase>>& other,
      const std::shared_ptr<VirtualTape<NewBase>>& val_tape,
      const std::shared_ptr<VirtualTape<NewBase>>& param_tape) {
    std::shared_ptr<TrivialTrace<NewBase>> ret =
        std::make_shared<TrivialTrace<NewBase>>();
    ret->op_tape = other->op_tape;
    ret->loc_tape = other->loc_tape;
    ret->val_tape = val_tape;
    ret->param_tape = param_tape;
    ret->coval_tape = other->coval_tape;
    ret->num_ind = other->num_ind;
    ret->num_dep = other->num_dep;
    return ret;
  }

template <typename OldBase, typename NewBase>
static std::shared_ptr<TrivialTrace<NewBase>> copy_tape(
      const std::shared_ptr<TrivialTrace<OldBase>>& other,
      const std::shared_ptr<VirtualTape<NewBase>>& val_tape) {
    // TODO(some warning message when other trace has non empty parameter)
    return copy_tape<OldBase, NewBase>(
        other, val_tape, std::make_shared<VirtualTape<NewBase>>());
}

} // namespace ReverseAD

#endif // TRIVIAL_TRACE_H_
