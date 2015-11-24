#ifndef BASE_REVERSE_ADJOINT_H_
#define BASE_REVERSE_ADJOINT_H_

#include <math.h>

#include <set>
#include <vector>
#include <map>
#include <iostream>

#include "reversead/common/reversead_base.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/trace/abstract_trace.hpp"
#include "reversead/tape/abstract_tape.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_mode.hpp"
#include "single_derivative.hpp"

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

  BaseReverseAdjoint(AbstractTrace<Base>* trace) : BaseReverseMode<Base>(trace) {}

  void init_dep_deriv(SingleDeriv& deriv, locint dep) {
    (*deriv.adjoint_vals)[dep] = 1.0;
  }

  void process_sac(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) {
    Base w = deriv.adjoint_vals->get_and_erase(info.r);
    compute_adjoint_sac(info, *(deriv.adjoint_vals), w);
  }

  void retrieve_adjoint(Base*** values) {
    int dep_size = dep_deriv.size();
    (*values) = new Base*[dep_size];
    for (auto& kv : dep_deriv) {
      locint dep = dep_index_map[kv.first] - 1;
      int size = kv.second.adjoint_vals->get_size();
      (*values)[dep] = new Base[size];
      for (int i = 0; i < size; i++) {(*values)[dep][i] = 0.0;}
      typename type_adjoint::enumerator a_enum = kv.second.adjoint_vals->get_enumerator();
      bool has_next = a_enum.has_next();
      locint x;
      Base w;
      while (has_next) {
        has_next = a_enum.get_next(x, w);
        (*values)[dep][indep_index_map[x] - 1] = w;
      } 
    }
  }
/*
  void retrieve_hessian_sparse_format(int** ssize, locint*** rind, locint*** cind, Base*** values) {
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
      Base w;
      int l =0;
      while(has_next) {
        has_next = h_enum.get_next(x, y, (*values)[dep][l]);
        (*rind)[dep][l] = indep_index_map[x];
        (*cind)[dep][l] = indep_index_map[y];
        l++;
      }
    }
  }
*/

  void compute_adjoint_sac(const DerivativeInfo<locint, Base>& info,
                           type_adjoint& adjoint_vals,
                           Base& w) {
    if (info.x != NULL_LOC) {
      adjoint_vals[info.x] += w * info.dx;
    }
    if (info.y != NULL_LOC) {
      adjoint_vals[info.y] += w * info.dy;
    }
  }

};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_ADJOINT_H_
