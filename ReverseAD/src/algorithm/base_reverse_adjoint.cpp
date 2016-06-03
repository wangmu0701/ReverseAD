#include <set>
#include <map>
#include <memory>

#include "reversead/common/opcodes.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_adjoint.hpp"
#include "reversead/forwardtype/single_forward.hpp"

namespace ReverseAD {

template <typename Base>
void BaseReverseAdjoint<Base>::enable_preacc() {
  preacc_enabled = true;
}

template <typename Base>
std::shared_ptr<DerivativeTensor<int, Base>>
    BaseReverseAdjoint<Base>::get_tensor() const {
  int dep_size = dep_deriv.size();
  int ind_size = indep_index_map.size();
  std::shared_ptr<DerivativeTensor<int, Base>> ret =
    std::make_shared<DerivativeTensor<int, Base>>(dep_size, ind_size, 1);
  BaseReverseMode<Base>::transcript_dep_value(ret);
  transcript_adjoint(ret);

  return std::move(ret);
}

template <typename Base>
void BaseReverseAdjoint<Base>::transcript_adjoint(
    std::shared_ptr<DerivativeTensor<int, Base>> tensor) const{
  for (auto& kv : dep_deriv) {
    int dep = dep_index_map.find(kv.first)->second - 1;
    int size = kv.second.adjoint_vals->get_size();
    tensor->init_single_tensor(dep, 1, size);
    locint t[1];
    int x[1];
    Base w;
    int l = 0;
    typename type_adjoint::enumerator a_enum = kv.second.adjoint_vals->get_enumerator();
    bool has_next = a_enum.has_next();
    while (has_next) {
      has_next = a_enum.get_next(t[0], w);
      x[0] = indep_index_map.find(t[0])->second - 1;
      tensor->put_value(dep, 1, l, x, w);
      l++;
    }
  }
}

template <typename Base>
void BaseReverseAdjoint<Base>::init_dep_deriv(locint dep, int dep_count) {
  dep_deriv[dep].adjoint_vals->increase(dep, 1.0);
  reverse_live[dep].insert(dep); 
}

template <typename Base>
void BaseReverseAdjoint<Base>::accumulate_sac(
    const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) {
  Base w = deriv.adjoint_vals->get_and_erase(info.r);
  accumulate_adjoint_sac(info, *(deriv.adjoint_vals), w);
}

template <typename Base>
void BaseReverseAdjoint<Base>::accumulate_adjoint_sac(
    const DerivativeInfo<locint, Base>& info,
    type_adjoint& adjoint_vals,
    const Base& w) {
  if (info.x != NULL_LOC) {
    adjoint_vals.increase(info.x, w * info.dx);
  }
  if (info.y != NULL_LOC) {
    adjoint_vals.increase(info.y, w * info.dy);
  }
}

template <typename Base>
void BaseReverseAdjoint<Base>::accumulate_deriv(
    locint local_dep,
    SingleDeriv& local_deriv,
    SingleDeriv& deriv) {
  Base w = deriv.adjoint_vals->get_and_erase(local_dep);
  // compute adjoint;
  accumulate_adjoint_deriv(*(local_deriv.adjoint_vals),
                           *(deriv.adjoint_vals),
                           w);
}
template <typename Base>
void BaseReverseAdjoint<Base>::accumulate_adjoint_deriv(
    const type_adjoint& local_adjoint,
    type_adjoint& global_adjoint,
    const Base& w) {
   
  if (!IsZero(w)) {
      locint v;
      Base vw;
      typename type_adjoint::enumerator l_enum = local_adjoint.get_enumerator();
      bool has_next = l_enum.has_next();
      while(has_next) {
          has_next = l_enum.get_next(v, vw);
          global_adjoint.increase(v, w * vw);
      }
  }
}

// here we can do something to enable preaccumulation
template <typename Base>
void BaseReverseAdjoint<Base>::process_sac(const DerivativeInfo<locint, Base>& info) {
  if (preacc_enabled) {
    process_preacc(info);
    return;
  }
  if (info.r != NULL_LOC) {
    std::set<locint> dep_set = std::move(reverse_live[info.r]);
    reverse_live.erase(info.r);
    for (const locint& dep : dep_set) {
      accumulate_sac(info, dep_deriv[dep]);
      if (info.x != NULL_LOC) {
        reverse_live[info.x].insert(dep);
      }
      if (info.y != NULL_LOC) {
        reverse_live[info.y].insert(dep);
      }
    }
  }
}

template <typename Base>
void BaseReverseAdjoint<Base>::process_preacc(
    const DerivativeInfo<locint, Base>& info) {
  switch (info.opcode) {
    case start_of_tape:
    case assign_a:
    case assign_d:
    case assign_param:
    case eq_plus_a:
    case eq_plus_d:
    case eq_minus_a:
    case eq_mult_a:
    case eq_mult_d:
    case eq_div_a:
      std::set<locint> dep_set = std::move(reverse_live[temp_local_dep]);
      reverse_live.erase(temp_local_dep);
      for (const locint& dep : dep_set) {
        accumulate_deriv(temp_local_dep, temp_local_deriv, dep_deriv[dep]);
        for (const locint& p : temp_local_live) {
          reverse_live[p].insert(dep);
        }
      }
      temp_local_dep = info.r;
      temp_local_live.clear();
      temp_local_live.insert(info.r);
      temp_local_deriv.clear();
      temp_local_deriv.adjoint_vals->increase(info.r, 1.0);
      break;
  }
  if (info.r != NULL_LOC) {
    accumulate_sac(info, temp_local_deriv);
    temp_local_live.erase(info.r);
    if (info.x != NULL_LOC) {
      temp_local_live.insert(info.x);
    }
    if (info.y != NULL_LOC) {
      temp_local_live.insert(info.y);
    }
  }
}

} // namespace ReverseAD

template class ReverseAD::BaseReverseAdjoint<double>;
template class ReverseAD::BaseReverseAdjoint<ReverseAD::SingleForward>;
