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
      : trace(_trace),
        _use_dep_init_adjoint(false) {}

  virtual DerivativeTensor<int, Base> compute(
      int ind_num, int dep_num);
  virtual DerivativeTensor<int, Base> compute(
      int ind_num, int dep_num, Base* init_dep_adjoints);

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

  virtual void init_dep_deriv(locint dep, int dep_count) = 0;

  virtual DerivativeTensor<int, Base> transcript_result() = 0;
  
  void transcript_dep_value(DerivativeTensor<int, Base>& tensor);

  std::shared_ptr<TrivialTrace<Base>> trace;
  std::map<locint, std::set<locint> > reverse_live;
  std::map<locint, SingleDeriv> dep_deriv;
  std::map<locint, int> indep_index_map;
  std::map<locint, int> dep_index_map;
  std::map<int, Base> dep_init_adjoint;
  std::map<locint, Base> dep_value;
  
  bool _use_dep_init_adjoint;
};

} // namespace ReverseAD

#endif // BASE_REVERSE_MODE_H_
