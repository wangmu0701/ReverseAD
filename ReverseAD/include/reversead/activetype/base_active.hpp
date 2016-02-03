#ifndef BASE_ACBaseIVE_H_
#define BASE_ACBaseIVE_H_

#include <cmath>
#include <iostream>
#include "reversead/common/reversead_base.hpp"
#include "reversead/common/opcodes.hpp"

//#define REVERSEAD_BASE_ACTIVE_DEBUG

#define REVERSE_AD_ONLY_REVERSE

namespace ReverseAD {

template <typename Base>
class BaseActive {
 public:

  #include "base_active_assign.ipp" // constructor and assignment
  #include "base_active_comparison.ipp" // ==, !=, <, >, <=, >=
  #include "base_active_incdec.ipp" // ++a, a++, --a, a--
  #include "base_active_plus.ipp" // plus +, +=
  #include "base_active_mult.ipp" // mult *, *=
  #include "base_active_minus.ipp" // minus -, -=
  #include "base_active_div.ipp" // div /, /=
  #include "base_active_powexp.ipp" // pow, sqrt, exp, log
  #include "base_active_trigono.ipp" // sin, cos, tan, asin, acos, atan
  #include "base_active_hyperbolic.ipp" // sinh, cosh, tanh, asinh, acosh, atanh
  #include "base_active_other.ipp" // fabs

  inline Base getVal() const {return val;}
  inline locint getLoc() const {return loc;}
  static BaseActive<Base> markParam(const Base& param) {
    BaseActive res(param, get_next_loc());
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "markParam : " << &res <<"["<<res.getLoc()<<"]" << " = " << param << std::endl;
#endif
    trace_put_olp<Base>(assign_param, res.getLoc(), param);
    return res;
  }
 private:
  // Private c-tor is only used internally for operators returning a L-value
  // For example, plus_d_a, with a L-value.
  BaseActive(const Base& val, const locint& loc) {
    this->val = val;
    this->loc = loc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "Private c-tor: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
#endif
  }

  Base val;
  locint loc;
};  

typedef ReverseAD::BaseActive<double> adouble;

} // namespace ReverseAD



#endif // BASE_ACTIVE_H_
