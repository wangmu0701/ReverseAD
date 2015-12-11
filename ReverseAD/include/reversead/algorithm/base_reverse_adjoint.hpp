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

  using BaseReverseMode<Base>::compute_adjoint_sac;

  BaseReverseAdjoint(AbstractTrace<Base>* trace) : BaseReverseMode<Base>(trace) {}


  void retrieve_adjoint(Base*** values) {
    int dep_size = dep_deriv.size();
    (*values) = new Base*[dep_size];
    for (auto& kv : dep_deriv) {
      locint dep = dep_index_map[kv.first] - 1;
      int size = indep_index_map.size();
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

  void retrieve_adjoint_sparse_format(int* ssize,
                                      locint** rind, locint** cind,
                                      Base** values) {
    int dep_size = dep_deriv.size();
    int total_size = 0;
    for (auto& kv : dep_deriv) {
      total_size += kv.second.adjoint_vals->get_size();
    }
    (*ssize) = total_size;
    (*rind) = new locint[total_size];
    (*cind) = new locint[total_size];
    (*values) = new double[total_size];
    int l = 0;
    for (auto& kv : dep_deriv) {
      locint dep = dep_index_map[kv.first] - 1;
      typename type_adjoint::enumerator a_enum = kv.second.adjoint_vals->get_enumerator();
      bool has_next = a_enum.has_next();
      locint x;
      Base w;
      while (has_next) {
        has_next = a_enum.get_next(x, w);
        (*rind)[l] = dep;
        (*cind)[l] = indep_index_map[x] - 1;
        (*values)[l] = w;
        l++;
      } 
    }
  }


 protected:
  void init_dep_deriv(SingleDeriv& deriv, locint dep) {
    (*deriv.adjoint_vals)[dep] = 1.0;
  }

  virtual void accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) {
    Base w = deriv.adjoint_vals->get_and_erase(info.r);
    compute_adjoint_sac(info, *(deriv.adjoint_vals), w);
  }

  void process_sac(const DerivativeInfo<locint, Base>& info) {
    if (info.r != NULL_LOC) {
      std::set<locint> dep_set = std::move(reverse_live[info.r]);
      reverse_live.erase(info.r);
      for (const locint& dep : dep_set) {
        accumulate_deriv(info, dep_deriv[dep]);
        if (info.x != NULL_LOC) {
          reverse_live[info.x].insert(dep);
        }
        if (info.y != NULL_LOC) {
          reverse_live[info.y].insert(dep);
        }
      }
    }
  }
};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_ADJOINT_H_
