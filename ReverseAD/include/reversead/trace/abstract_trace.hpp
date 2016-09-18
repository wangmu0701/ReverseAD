#ifndef ABSTRACT_TRACE_H_
#define ABSTRACT_TRACE_H_


#include "reversead/common/reversead_type.hpp"

namespace ReverseAD {

template<typename Base>
class AbstractTrace {
 public:
  AbstractTrace() {
    num_ind = 0;
    num_dep = 0;
    num_dummy_ind = 0;
    num_dummy_dep = 0;
    num_param = 0;
  }
  virtual ~AbstractTrace() {}

  virtual void put_op(const opbyte&) = 0;
  virtual void put_loc(const locint&) = 0;
  virtual void put_val(const Base&) = 0;
  virtual void put_param(const Base&) = 0;
  virtual void put_coval(const double&) = 0;
  
  // forward sweep
  virtual void init_forward() = 0;
  virtual void end_forward() = 0;
  virtual opbyte get_next_op_f() = 0;
  virtual locint get_next_loc_f() = 0;
  virtual Base get_next_val_f() = 0;
  virtual Base get_next_param_f() = 0;
  virtual double get_next_coval_f() = 0;

  // reverse sweep
  virtual void init_reverse() = 0;
  virtual void end_reverse() = 0;
  virtual opbyte get_next_op_r() = 0;
  virtual locint get_next_loc_r() = 0;
  virtual Base get_next_val_r() = 0;
  virtual Base get_next_param_r() = 0;
  virtual double get_next_coval_r() = 0;

  // for debug
  virtual void dump_trace_info() = 0;
  virtual void dump_trace() = 0;
  
  // independent and dependent counters
  void declare_ind() {num_ind++;}
  void declare_dep() {num_dep++;}
  size_t get_num_ind() {return num_ind;}
  size_t get_num_dep() {return num_dep;}
  void increase_dummy_ind(int size) {num_dummy_ind += size;}
  void increase_dummy_dep(int size) {num_dummy_dep += size;}
  size_t get_num_dummy_ind() {return num_dummy_ind;}
  size_t get_num_dummy_dep() {return num_dummy_dep;}
  size_t get_num_param() {return num_param;}
 protected:
  size_t num_ind;
  size_t num_dep;
  size_t num_dummy_ind;
  size_t num_dummy_dep;
  size_t num_param;
};

} // namespace ReverseAD

#endif // ABSTRACT_TRACT_H_
