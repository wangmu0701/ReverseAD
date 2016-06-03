#ifndef REVERSEAD_BASE_REVERSE_THIRD_H_
#define REVERSEAD_BASE_REVERSE_THIRD_H_

#include <set>
#include <map>
#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/algorithm/base_reverse_hessian.hpp"
#include "reversead/algorithm/derivative_info.hpp"
#include "reversead/algorithm/trivial_deriv.hpp"

namespace ReverseAD {

template <typename Base>
class BaseReverseThird : public virtual BaseReverseHessian<Base> {
 public:
  typedef typename TrivialDeriv<Base>::type_adjoint type_adjoint;
  typedef typename TrivialDeriv<Base>::type_hessian type_hessian;
  typedef typename TrivialDeriv<Base>::type_third type_third;
  typedef TrivialDeriv<Base> SingleDeriv;

  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::dep_index_map;
  using BaseReverseMode<Base>::indep_index_map;

  // in template, name resolve will not look in base class
  using BaseReverseAdjoint<Base>::accumulate_adjoint_sac;
  using BaseReverseAdjoint<Base>::accumulate_adjoint_deriv;
  using BaseReverseHessian<Base>::accumulate_hessian_sac;
  using BaseReverseHessian<Base>::accumulate_hessian_deriv;

  BaseReverseThird(const std::shared_ptr<TrivialTrace<Base>>& trace)
      : BaseReverseAdjoint<Base>(trace) {}

  ~BaseReverseThird() = default;

  std::shared_ptr<DerivativeTensor<int, Base>> get_tensor() const override;

 protected:
  BaseReverseThird() = default;

  void accumulate_sac(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) override;

  void accumulate_deriv(locint local_dep,
                        SingleDeriv& local_deriv,
                        SingleDeriv& deriv) override;
    
  void transcript_third(std::shared_ptr<DerivativeTensor<int, Base>> tensor) const;

  void accumulate_third_sac(const DerivativeInfo<locint, Base>& info,
                         type_third& third_vals,
                         const Base& w,
                         const type_adjoint& r,
                         const type_hessian& e);

  void accumulate_third_deriv(locint local_dep,
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
