#ifndef REVERSEAD_BASE_REVERSE_THIRD_H_
#define REVERSEAD_BASE_REVERSE_THIRD_H_

#include <math.h>

#include <set>
#include <vector>
#include <map>
#include <iostream>

#include "reversead/common/reversead_base.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_mode.hpp"
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

  void accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) {
    Base w = deriv.adjoint_vals->get_and_erase(info.r);
    type_adjoint r = deriv.hessian_vals->get_and_erase(info.r);
    type_hessian e = deriv.third_vals->get_and_erase(info.r);
    compute_adjoint_sac(info, *(deriv.adjoint_vals), w);
    compute_hessian_sac(info, *(deriv.hessian_vals), w, r);
    compute_third_sac(info, *(deriv.third_vals), w, r, e);
  }

  int retrieve_third_sparse_format(int** ssize, locint**** tind, Base*** values) {
    int dep_size = dep_deriv.size();
    (*ssize) = new int[dep_size];
    (*tind) = new locint**[dep_size];
    (*values) = new Base*[dep_size];
    for (auto& kv : dep_deriv) {
      locint dep = dep_index_map[kv.first] - 1;
      int size = kv.second.third_vals->get_size();
      (*ssize)[dep] = size;
      (*tind)[dep] = new locint*[size];
      (*values)[dep] = new Base[size];
      typename type_third::enumerator t_enum =
          kv.second.third_vals->get_enumerator();
      int l = 0;
      locint x,y,z;
      while(t_enum.has_next()) {
        t_enum.get_next(x, y, z, (*values)[dep][l]);
        (*tind)[dep][l] = new locint[3];
        (*tind)[dep][l][0] = indep_index_map[x];
        (*tind)[dep][l][1] = indep_index_map[y];
        (*tind)[dep][l][2] = indep_index_map[z];
        l++;
      }
    }
    return dep_size;
  }

 protected:
  BaseReverseThird() : BaseReverseAdjoint<Base>() {}
 
  virtual DerivativeTensor<locint, Base> transcript_result() {
    int dep_size = dep_deriv.size();
    int ind_size = indep_index_map.size();
    DerivativeTensor<locint, Base> ret(dep_size, ind_size, 3);
    BaseReverseAdjoint<Base>::transcript_adjoint(ret);
    BaseReverseHessian<Base>::transcript_hessian(ret);
    transcript_third(ret);
    return ret;
  } 
    
  void transcript_third(DerivativeTensor<locint, Base>& tensor) {
    for (auto& kv : dep_deriv) {
      locint dep = dep_index_map[kv.first] - 1;
      int size = kv.second.third_vals->get_size();
      tensor.init_single_tensor(dep, 3, size);
      locint x[3];
      Base w;             
      int l = 0;          
      typename type_third::enumerator t_enum = kv.second.third_vals->get_enumerator();
      bool has_next = t_enum.has_next();
      while (has_next) {
        has_next = t_enum.get_next(x[0], x[1], x[2], w);
        x[0] = indep_index_map[x[0]] - 1;
        x[1] = indep_index_map[x[1]] - 1;
        x[2] = indep_index_map[x[2]] - 1;
        tensor.put_value(dep, 3, l, x, w);
        l++;
      }
    }
  }

  virtual void process_single_deriv(locint local_dep,
                                    SingleDeriv& local_deriv,
                                    SingleDeriv& deriv) {
    Base w = deriv.adjoint_vals->get_and_erase(local_dep);
    type_adjoint r = deriv.hessian_vals->get_and_erase(local_dep);
    type_hessian e = deriv.third_vals->get_and_erase(local_dep);
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
    // compute third
    compute_third_deriv(local_dep,
                        *(local_deriv.adjoint_vals),
                        *(local_deriv.hessian_vals),
                        *(local_deriv.third_vals),
                        *(deriv.third_vals),
                        w,
                        r,
                        e);
  }  
};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_THIRD_H_
