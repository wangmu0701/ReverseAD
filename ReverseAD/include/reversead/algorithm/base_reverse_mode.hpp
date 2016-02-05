#ifndef REVERSEAD_BASE_REVERSE_MODE_H_
#define REVERSEAD_BASE_REVERSE_MODE_H_

#include <set>
#include <map>
#include <memory>

#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/single_derivative.hpp"
#include "reversead/algorithm/derivative_tensor.hpp"

//class ReverseAD::IterativeFunc;

namespace ReverseAD {

template <typename Base>
class BaseReverseMode {
 public:
  typedef typename SingleDerivative<Base>::type_adjoint type_adjoint;
  typedef typename SingleDerivative<Base>::type_hessian type_hessian;
  typedef typename SingleDerivative<Base>::type_third type_third;
  typedef SingleDerivative<Base> SingleDeriv;

  BaseReverseMode(const std::shared_ptr<TrivialTrace<Base>>& _trace)
      : trace(_trace) {}

  virtual ~BaseReverseMode() = default;

  BaseReverseMode<Base>& compute(int ind_num, int dep_num);

  virtual std::shared_ptr<DerivativeTensor<int, Base>> get_tensor() const = 0;

  virtual void clear();

 protected:
  BaseReverseMode() = default;

  virtual void init_dep_deriv(locint dep, int dep_count) = 0;

  virtual void process_sac(const DerivativeInfo<locint, Base>& info) = 0;
  
  void reverse_local_computation(int, int);

  void transcript_dep_value(std::shared_ptr<DerivativeTensor<int, Base>> tensor) const;

  std::shared_ptr<TrivialTrace<Base>> trace;
  std::map<locint, std::set<locint> > reverse_live;
  mutable std::map<locint, SingleDeriv> dep_deriv;
  mutable std::map<locint, int> indep_index_map;
  mutable std::map<locint, int> dep_index_map;
  mutable std::map<locint, Base> dep_value;

 private:
  // This class will only be invoked by InterativeFunc
  void compute_iterative();
  void reset_trace(std::shared_ptr<TrivialTrace<Base>> _trace);
  friend class IterativeFunc;
};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_MODE_H_
