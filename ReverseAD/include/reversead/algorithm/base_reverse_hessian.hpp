#ifndef BASE_REVERSE_HESSIAN_H_
#define BASE_REVERSE_HESSIAN_H_

#include <set>
#include <vector>
#include <map>
#include <iostream>

#include "reversead/common/reversead_base.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_mode.hpp"
#include "reversead/algorithm/base_reverse_adjoint.hpp"
#include "single_derivative.hpp"


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

  void accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) {
    Base w = deriv.adjoint_vals->get_and_erase(info.r);
    type_adjoint r = deriv.hessian_vals->get_and_erase(info.r);

    compute_adjoint_sac(info, *(deriv.adjoint_vals), w);
    compute_hessian_sac(info, *(deriv.hessian_vals), w, r);
  }

  int retrieve_hessian_sparse_format(int** ssize, locint*** rind, locint*** cind, Base*** values) {
    int dep_size = dep_deriv.size();
    (*ssize) = new int[dep_size];
    (*rind) = new locint*[dep_size];
    (*cind) = new locint*[dep_size];
    (*values) = new Base*[dep_size];
    for (auto& kv : dep_deriv) {
      locint dep = dep_index_map[kv.first] - 1;
      int size = kv.second.hessian_vals->get_size();
      (*ssize)[dep] = size;
      (*rind)[dep] = new locint[size];
      (*cind)[dep] = new locint[size];
      (*values)[dep] = new Base[size];
      typename type_hessian::enumerator h_enum = kv.second.hessian_vals->get_enumerator();
      bool has_next = h_enum.has_next();
      locint x,y;
      int l =0;
      while(has_next) {
        has_next = h_enum.get_next(x, y, (*values)[dep][l]);
        (*rind)[dep][l] = indep_index_map[x] - 1;
        (*cind)[dep][l] = indep_index_map[y] - 1;
        l++;
      }
    }
    return dep_size;
  }

 protected:
  BaseReverseHessian() : BaseReverseAdjoint<Base>() {}

  virtual void process_single_deriv(locint local_dep,
                                    SingleDeriv& local_deriv,
                                    SingleDeriv& deriv) {
    Base w = deriv.adjoint_vals->get_and_erase(local_dep);
    type_adjoint r = deriv.hessian_vals->get_and_erase(local_dep);
    // compute adjoint;
    compute_adjoint_deriv(*(local_deriv.adjoint_vals),
                          *(deriv.adjoint_vals),
                          w);
    // compute hessian;
    compute_hessian_deriv(local_dep,
                          *(local_deriv.adjoint_vals),
                          *(local_deriv.hessian_vals),
                          *(deriv.hessian_vals),
                          w,
                          r);
  }  
};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_HESSIAN_H_
