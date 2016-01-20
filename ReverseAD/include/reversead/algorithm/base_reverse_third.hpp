#ifndef REVERSEAD_BASE_REVERSE_THIRD_H_
#define REVERSEAD_BASE_REVERSE_THIRD_H_

#include <set>
#include <map>
#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_hessian.hpp"
#include "reversead/algorithm/single_derivative.hpp"

namespace ReverseAD {

template <typename Base>
class BaseReverseThird : public virtual BaseReverseHessian<Base> {
 public:
  typedef typename SingleDerivative<Base>::type_adjoint type_adjoint;
  typedef typename SingleDerivative<Base>::type_hessian type_hessian;
  typedef typename SingleDerivative<Base>::type_third type_third;
  typedef SingleDerivative<Base> SingleDeriv;

  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::dep_index_map;
  using BaseReverseMode<Base>::indep_index_map;

  // in template, name resolve will not look in base class
  using BaseReverseAdjoint<Base>::compute_adjoint_sac;
  using BaseReverseAdjoint<Base>::compute_adjoint_deriv;
  using BaseReverseHessian<Base>::compute_hessian_sac;
  using BaseReverseHessian<Base>::compute_hessian_deriv;

  BaseReverseThird(const std::shared_ptr<TrivialTrace<Base>>& trace)
      : BaseReverseAdjoint<Base>(trace) {}

  ~BaseReverseThird() = default;

 protected:
  BaseReverseThird() = default;
 
  virtual DerivativeTensor<int, Base> transcript_result();

  virtual void accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv);

  virtual void process_single_deriv(locint local_dep,
                                    SingleDeriv& local_deriv,
                                    SingleDeriv& deriv);
    
  void transcript_third(DerivativeTensor<int, Base>& tensor);

  void compute_third_sac(const DerivativeInfo<locint, Base>& info,
                         type_third& third_vals,
                         const Base& w,
                         const type_adjoint& r,
                         const type_hessian& e);

  void compute_third_deriv(locint local_dep,
                           const type_adjoint& local_adjoint,
                           const type_hessian& local_hessian,
                           const type_third& local_third,
                           type_third& global_third,
                           const Base& w,
                           const type_adjoint& r,
                           const type_hessian& e);

};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_THIRD_H_
