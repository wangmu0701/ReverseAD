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

  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::dep_index_map;
  using BaseReverseMode<Base>::indep_index_map;

  BaseReverseAdjoint(const std::shared_ptr<TrivialTrace<Base>>& trace)
      : BaseReverseMode<Base>(trace), preacc_enabled(false) {}

  ~BaseReverseAdjoint() = default;

  std::shared_ptr<DerivativeTensor<int, Base>> get_tensor() const override;

  void enable_preacc();

 protected:
  BaseReverseAdjoint() = default;
 
  // From BaseReverseMode 
  void init_dep_deriv(locint dep, int dep_count) override final;

  // here we can do something to enable preaccumulation
  void process_sac(const DerivativeInfo<locint, Base>& info) override final;

  // Originate BaseReverseAdjoint
  virtual void accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv);

  virtual void process_single_deriv(locint local_dep,
                                    SingleDeriv& local_deriv,
                                    SingleDeriv& deriv);

  void transcript_adjoint(std::shared_ptr<DerivativeTensor<int, Base>> tensor) const;

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
