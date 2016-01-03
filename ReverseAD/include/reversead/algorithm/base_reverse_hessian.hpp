#ifndef BASE_REVERSE_HESSIAN_H_
#define BASE_REVERSE_HESSIAN_H_

#include <set>
#include <map>
#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_adjoint.hpp"
#include "reversead/algorithm/single_derivative.hpp"


namespace ReverseAD {

template <typename Base>
class BaseReverseHessian : public virtual BaseReverseAdjoint<Base> {
 public:
  typedef typename SingleDerivative<Base>::type_adjoint type_adjoint;
  typedef typename SingleDerivative<Base>::type_hessian type_hessian;
  typedef SingleDerivative<Base> SingleDeriv;

  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::dep_index_map;
  using BaseReverseMode<Base>::indep_index_map;

  // in template, name resolve will not look in base class
  using BaseReverseMode<Base>::compute_adjoint_sac;
  using BaseReverseMode<Base>::compute_hessian_sac;
  using BaseReverseMode<Base>::compute_adjoint_deriv;
  using BaseReverseMode<Base>::compute_hessian_deriv;

  BaseReverseHessian(const std::shared_ptr<TrivialTrace<Base>>& trace)
      : BaseReverseAdjoint<Base>(trace) {}

  void accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv);

 protected:
  BaseReverseHessian() : BaseReverseAdjoint<Base>() {}

  virtual DerivativeTensor<int, Base> transcript_result();

  void transcript_hessian(DerivativeTensor<int, Base>& tensor);
  virtual void process_single_deriv(locint local_dep,
                                    SingleDeriv& local_deriv,
                                    SingleDeriv& deriv);

};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_HESSIAN_H_
