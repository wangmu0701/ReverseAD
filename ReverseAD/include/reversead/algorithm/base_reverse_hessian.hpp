#ifndef BASE_REVERSE_HESSIAN_H_
#define BASE_REVERSE_HESSIAN_H_

#include <set>
#include <map>
#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/base_reverse_adjoint.hpp"
#include "reversead/algorithm/derivative_info.hpp"
#include "reversead/algorithm/trivial_deriv.hpp"

namespace ReverseAD {

template <typename Base>
class BaseReverseHessian : public virtual BaseReverseAdjoint<Base> {
 public:
  typedef typename TrivialDeriv<Base>::type_adjoint type_adjoint;
  typedef typename TrivialDeriv<Base>::type_hessian type_hessian;
  typedef TrivialDeriv<Base> SingleDeriv;

  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::dep_index_map;
  using BaseReverseMode<Base>::indep_index_map;

  // in template, name resolve will not look in base class
  using BaseReverseAdjoint<Base>::compute_adjoint_sac;
  using BaseReverseAdjoint<Base>::compute_adjoint_deriv;

  BaseReverseHessian(const std::shared_ptr<TrivialTrace<Base>>& trace)
      : BaseReverseAdjoint<Base>(trace) {}

  ~BaseReverseHessian() = default;

  std::shared_ptr<DerivativeTensor<int, Base>> get_tensor() const override;
  
 protected:
  BaseReverseHessian() = default;

  void accumulate_deriv(
      const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) override;

  void process_single_deriv(locint local_dep,
                            SingleDeriv& local_deriv,
                            SingleDeriv& deriv) override;

  void transcript_hessian(
      std::shared_ptr<DerivativeTensor<int, Base>> tensor) const;

  void compute_hessian_sac(const DerivativeInfo<locint, Base>& info,
                           type_hessian& hessian_vals,
                           const Base& w,
                           const type_adjoint& r);

  void compute_hessian_deriv(locint local_dep,
                             const type_adjoint& local_adjoint,
                             const type_hessian& local_hessian,
                             type_hessian& global_hessian,
                             const Base& w,
                             const type_adjoint& r);

};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_HESSIAN_H_
