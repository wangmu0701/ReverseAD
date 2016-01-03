#include <set>
#include <map>
#include <memory>

#include "reversead/common/opcodes.hpp"
#include "reversead/algorithm/base_reverse_adjoint.hpp"
#include "reversead/forwardtype/single_forward.hpp"

namespace ReverseAD {

template <typename Base>
void BaseReverseAdjoint<Base>::enable_preacc() {
  preacc_enabled = true;
}

template <typename Base>
int BaseReverseAdjoint<Base>::retrieve_adjoint(Base*** values) {
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
  return dep_size;
}

template <typename Base>
void BaseReverseAdjoint<Base>::retrieve_adjoint_sparse_format(int* ssize,
                                    locint** rind, locint** cind,
                                    Base** values) {
  int total_size = 0;
  for (auto& kv : dep_deriv) {
    total_size += kv.second.adjoint_vals->get_size();
  }
  (*ssize) = total_size;
  (*rind) = new locint[total_size];
  (*cind) = new locint[total_size];
  (*values) = new Base[total_size];
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

template <typename Base>
DerivativeTensor<int, Base> BaseReverseAdjoint<Base>::transcript_result() {
  int dep_size = dep_deriv.size();
  int ind_size = indep_index_map.size();
  DerivativeTensor<int, Base> ret(dep_size, ind_size, 1);
  BaseReverseMode<Base>::transcript_dep_value(ret);
  transcript_adjoint(ret);

  BaseReverseMode<Base>::clear();
  return ret;
}

template <typename Base>
void BaseReverseAdjoint<Base>::transcript_adjoint(
    DerivativeTensor<int, Base>& tensor) {
  for (auto& kv : dep_deriv) {
    locint dep = dep_index_map[kv.first] - 1;
    int size = kv.second.adjoint_vals->get_size();
    tensor.init_single_tensor(dep, 1, size);
    locint t[1];
    int x[1];
    Base w;
    int l = 0;
    typename type_adjoint::enumerator a_enum = kv.second.adjoint_vals->get_enumerator();
    bool has_next = a_enum.has_next();
    while (has_next) {
      has_next = a_enum.get_next(t[0], w);
      x[0] = indep_index_map[t[0]] - 1;
      tensor.put_value(dep, 1, l, x, w);
      l++;
    }
  }
}

template <typename Base>
void BaseReverseAdjoint<Base>::init_dep_deriv(locint dep, int dep_count) {
  if (!_use_dep_init_adjoint) {
    dep_deriv[dep].adjoint_vals->increase(dep, 1.0);
  } else {
    dep_deriv[dep].adjoint_vals->increase(dep, dep_init_adjoint[dep_count]);
  }
  reverse_live[dep].insert(dep); 
}

template <typename Base>
void BaseReverseAdjoint<Base>::accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) {
  Base w = deriv.adjoint_vals->get_and_erase(info.r);
  compute_adjoint_sac(info, *(deriv.adjoint_vals), w);
}

template <typename Base>
void BaseReverseAdjoint<Base>::process_single_deriv(locint local_dep,
                                  SingleDeriv& local_deriv,
                                  SingleDeriv& deriv) {
  Base w = deriv.adjoint_vals->get_and_erase(local_dep);
  // compute adjoint;
  compute_adjoint_deriv(*(local_deriv.adjoint_vals),
                        *(deriv.adjoint_vals),
                        w);
}

// here we can do something to enable preaccumulation
template <typename Base>
void BaseReverseAdjoint<Base>::process_sac(const DerivativeInfo<locint, Base>& info) {
  if (preacc_enabled) {
    compute_preacc(info);
    return;
  }
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

template <typename Base>
void BaseReverseAdjoint<Base>::compute_preacc(
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
        process_single_deriv(temp_local_dep, temp_local_deriv, dep_deriv[dep]);
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
    accumulate_deriv(info, temp_local_deriv);
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
