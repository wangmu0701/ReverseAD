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
  using BaseReverseMode<Base>::compute_adjoint_sac;
  using BaseReverseMode<Base>::compute_hessian_sac;
  using BaseReverseMode<Base>::compute_third_sac;
  using BaseReverseMode<Base>::compute_adjoint_deriv;
  using BaseReverseMode<Base>::compute_hessian_deriv;
  using BaseReverseMode<Base>::compute_third_deriv;

  BaseReverseThird(const std::shared_ptr<TrivialTrace<Base>>& trace)
      : BaseReverseAdjoint<Base>(trace) {}

  void accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv);

  int retrieve_third_sparse_format(int** ssize, locint**** tind, Base*** values);

 protected:
  BaseReverseThird() : BaseReverseAdjoint<Base>() {}
 
  virtual DerivativeTensor<locint, Base> transcript_result();
    
  void transcript_third(DerivativeTensor<locint, Base>& tensor);

  virtual void process_single_deriv(locint local_dep,
                                    SingleDeriv& local_deriv,
                                    SingleDeriv& deriv);

};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_THIRD_H_
