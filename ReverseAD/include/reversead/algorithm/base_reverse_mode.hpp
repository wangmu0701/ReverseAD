#ifndef BASE_REVERSE_MODE_H_
#define BASE_REVERSE_MODE_H_

#include <set>
#include <map>
#include <memory>

#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/single_derivative.hpp"
#include "reversead/algorithm/derivative_tensor.hpp"

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

  virtual DerivativeTensor<locint, Base> compute(int ind_num, int dep_num);

 protected:
  BaseReverseMode() {}

  void reverse_local_computation(int, int);

  void compute_adjoint_sac(const DerivativeInfo<locint, Base>& info,
                           type_adjoint& adjoint_vals,
                           const Base& w);

  void compute_hessian_sac(const DerivativeInfo<locint, Base>& info,
                           type_hessian& hessian_vals,
                           const Base& w,
                           const type_adjoint& r);

  void compute_third_sac(const DerivativeInfo<locint, Base>& info,
                         type_third& third_vals,
                         const Base& w,
                         const type_adjoint& r,
                         const type_hessian& e);

  void compute_adjoint_deriv(const type_adjoint& local_adjoint,
                             type_adjoint& global_adjoint,
                             const Base& w);

  void compute_hessian_deriv(locint local_dep,
                             const type_adjoint& local_adjoint,
                             const type_hessian& local_hessian,
                             type_hessian& global_hessian,
                             const Base& w,
                             const type_adjoint& r);

  void compute_third_deriv(locint local_dep,
                           const type_adjoint& local_adjoint,
                           const type_hessian& local_hessian,
                           const type_third& local_third,
                           type_third& global_third,
                           const Base& w,
                           const type_adjoint& r,
                           const type_hessian& e);

  
  virtual void process_sac(const DerivativeInfo<locint, Base>& info) = 0;

  virtual void init_dep_deriv(SingleDeriv& deriv, locint dep) = 0;

  virtual DerivativeTensor<locint, Base> transcript_result() = 0;

  std::shared_ptr<TrivialTrace<Base>> trace;
  std::map<locint, std::set<locint> > reverse_live;
  std::map<locint, SingleDeriv> dep_deriv;
  std::map<locint, locint> indep_index_map;
  std::map<locint, locint> dep_index_map;
};

} // namespace ReverseAD

#endif // BASE_REVERSE_MODE_H_
