#ifndef REVERSEAD_TRIVIAL_DERIV_H_
#define REVERSEAD_TRIVIAL_DERIV_H_

#include <memory>

#include "reversead/algorithm/trivial_adjoint.hpp"
#include "reversead/algorithm/trivial_hessian.hpp"
#include "reversead/algorithm/trivial_third.hpp"

namespace ReverseAD {

template <typename Base>
class TrivialDeriv {
 public:

  typedef TrivialAdjoint<locint, Base> type_adjoint;
  typedef TrivialHessian<locint, Base> type_hessian;
  typedef TrivialThird<locint, Base> type_third;

  TrivialDeriv() {
    adjoint_vals.reset(new type_adjoint());
    hessian_vals.reset(new type_hessian());
    third_vals.reset(new type_third());
  }

  TrivialDeriv(char* buf) {
    int buf_size = 0;
    adjoint_vals.reset(new type_adjoint(buf));
    buf_size += adjoint_vals->byte_size();
    hessian_vals.reset(new type_hessian(&buf[buf_size]));
    buf_size += hessian_vals->byte_size();
    third_vals.reset(new type_third(&buf[buf_size]));
  }

  int byte_size() const {
    int ret = adjoint_vals->byte_size();
    if (hessian_vals) {
      ret += hessian_vals->byte_size();
    }
    if (third_vals) {
      ret += third_vals->byte_size();
    }
    return ret;
  }

  void clear() {
    adjoint_vals->clear();
    hessian_vals->clear();
    third_vals->clear(); 
  }

  void write_to_byte(char* const buf) const {
    int buf_size = 0;
    adjoint_vals->write_to_byte(buf);
    buf_size = adjoint_vals->byte_size();
    hessian_vals->write_to_byte(&buf[buf_size]);
    buf_size += hessian_vals->byte_size();
    third_vals->write_to_byte(&buf[buf_size]);
  }
  
  void debug() const {
    adjoint_vals->debug();
    hessian_vals->debug();
    third_vals->debug();
  }

  std::unique_ptr<type_adjoint> adjoint_vals;
  std::unique_ptr<type_hessian> hessian_vals;
  std::unique_ptr<type_third> third_vals;
};

}

#endif // REVERSEAD_TRIVIAL_DERIV_H_
