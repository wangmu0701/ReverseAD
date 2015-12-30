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

  using BaseReverseMode<Base>::compute_adjoint_sac;
  using BaseReverseMode<Base>::compute_adjoint_deriv;

  BaseReverseAdjoint(const std::shared_ptr<TrivialTrace<Base>>& trace)
      : BaseReverseMode<Base>(trace), preacc_enabled(false) {}

  void enable_preacc();
  int retrieve_adjoint(Base*** values);

  void retrieve_adjoint_sparse_format(int* ssize,
                                     locint** rind, locint** cind,
                                     Base** values);

 protected:
  BaseReverseAdjoint() {}
  
  virtual DerivativeTensor<locint, Base> transcript_result();

  void transcript_adjoint(DerivativeTensor<locint, Base>& tensor);

  void init_dep_deriv(locint dep, int dep_count);

  virtual void accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv);

  virtual void process_single_deriv(locint local_dep,
                                    SingleDeriv& local_deriv,
                                    SingleDeriv& deriv);

  // here we can do something to enable preaccumulation
  virtual void process_sac(const DerivativeInfo<locint, Base>& info) final;

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
