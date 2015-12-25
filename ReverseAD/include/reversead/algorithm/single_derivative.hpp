#ifndef SINGLE_DERIVATIVE_H_
#define SINGLE_DERIVATIVE_H_

#include "reversead/algorithm/trivial_adjoint.hpp"
#include "reversead/algorithm/trivial_hessian.hpp"
#include "reversead/algorithm/trivial_third.hpp"
#include "reversead/util/logger.hpp"

namespace ReverseAD {

template <typename Base>
class SingleDerivative : AbstractSerializable{
 public:

  typedef TrivialAdjoint<locint, Base> type_adjoint;
  typedef TrivialHessian<locint, Base> type_hessian;
  typedef TrivialThird<locint, Base> type_third;

  SingleDerivative() {
    adjoint_vals = new type_adjoint();
    hessian_vals = new type_hessian();
    third_vals = new type_third();
  }

  SingleDerivative(char* buf) {
    int buf_size = 0;
    adjoint_vals = new type_adjoint(buf);
    buf_size += adjoint_vals->byte_size();
    hessian_vals = new type_hessian(&(buf[buf_size]));
//    buf_size += third_vals->byte_size();
//    third_vals = new type_third(&buf[buf_size]);
  }

  int byte_size() const {
    int ret = adjoint_vals->byte_size();
    if (hessian_vals) {
      ret += hessian_vals->byte_size();
    }
/*
    if (third_vals) {
      ret += third_vals->byte_size();
    }
*/
    return ret;
  }
  void clear() {
    adjoint_vals->clear();
    hessian_vals->clear();
    //third_vals->clear();
  }
  void write_to_byte(char* const buf) const {
    int buf_size = 0;
    adjoint_vals->write_to_byte(buf);
    buf_size = adjoint_vals->byte_size();
    hessian_vals->write_to_byte(&buf[buf_size]);
    buf_size += hessian_vals->byte_size();
    //third_vals->write_to_byte(&buf[buf_size]);
  }
  
  void debug() const {
    adjoint_vals->debug();
    hessian_vals->debug();
    third_vals->debug();
  }
  void debug(Logger& logger) const {
    adjoint_vals->debug(logger);
    hessian_vals->debug(logger);
    third_vals->debug(logger);
  }

  type_adjoint* adjoint_vals;
  type_hessian* hessian_vals;
  type_third* third_vals;
};

}

#endif // SINGLE_DERIVATIVE_H_
