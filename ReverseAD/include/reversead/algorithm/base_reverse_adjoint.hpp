#ifndef BASE_REVERSE_ADJOINT_H_
#define BASE_REVERSE_ADJOINT_H_

#include <set>
#include <map>

#include "reversead/common/reversead_type.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_mode.hpp"
#include "reversead/algorithm/single_derivative.hpp"

namespace ReverseAD {

template <typename Base>
class BaseReverseAdjoint : public BaseReverseMode<Base> {
 public:
  typedef typename SingleDerivative<Base>::type_adjoint type_adjoint;
  typedef SingleDerivative<Base> SingleDeriv;

  using BaseReverseMode<Base>::_use_dep_init_adjoint;
  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::dep_index_map;
  using BaseReverseMode<Base>::indep_index_map;
  using BaseReverseMode<Base>::dep_init_adjoint;

  BaseReverseAdjoint(const std::shared_ptr<TrivialTrace<Base>>& trace)
      : BaseReverseMode<Base>(trace), preacc_enabled(false) {}

  ~BaseReverseAdjoint() = default;

  void enable_preacc();

 protected:
  BaseReverseAdjoint() = default;
 
  // From BaseReverseMode 
  virtual void init_dep_deriv(locint dep, int dep_count);

  // here we can do something to enable preaccumulation
  virtual void process_sac(const DerivativeInfo<locint, Base>& info) final;

  virtual DerivativeTensor<int, Base> transcript_result();

  // From BaseReverseAdjoint
  virtual void accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv);

  virtual void process_single_deriv(locint local_dep,
                                    SingleDeriv& local_deriv,
                                    SingleDeriv& deriv);

  void transcript_adjoint(DerivativeTensor<int, Base>& tensor);

  void compute_adjoint_sac(const DerivativeInfo<locint, Base>& info,
                           type_adjoint& adjoint_vals,
                           const Base& w);

  void compute_adjoint_deriv(const type_adjoint& local_adjoint,
                             type_adjoint& global_adjoint,
                             const Base& w);

 // preaccumulation stuff
 private:
  bool preacc_enabled;
  locint temp_local_dep;
  SingleDeriv temp_local_deriv;
  std::set<locint> temp_local_live;
  void compute_preacc(const DerivativeInfo<locint, Base>& info);
};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_ADJOINT_H_
