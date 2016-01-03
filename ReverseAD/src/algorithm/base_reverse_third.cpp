#include "reversead/algorithm/base_reverse_third.hpp"
#include "reversead/forwardtype/single_forward.hpp"

namespace ReverseAD {

template <typename Base>

void BaseReverseThird<Base>::accumulate_deriv(
    const DerivativeInfo<locint, Base>& info,
    SingleDeriv& deriv) {
  Base w = deriv.adjoint_vals->get_and_erase(info.r);
  type_adjoint r = deriv.hessian_vals->get_and_erase(info.r);
  type_hessian e = deriv.third_vals->get_and_erase(info.r);
  compute_adjoint_sac(info, *(deriv.adjoint_vals), w);
  compute_hessian_sac(info, *(deriv.hessian_vals), w, r);
  compute_third_sac(info, *(deriv.third_vals), w, r, e);
}

template <typename Base>
int BaseReverseThird<Base>::retrieve_third_sparse_format(
    int** ssize, locint**** tind, Base*** values) {
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

template <typename Base>
DerivativeTensor<int, Base> BaseReverseThird<Base>::transcript_result() {
  int dep_size = dep_deriv.size();
  int ind_size = indep_index_map.size();
  DerivativeTensor<int, Base> ret(dep_size, ind_size, 3);
  BaseReverseMode<Base>::transcript_dep_value(ret);
  BaseReverseAdjoint<Base>::transcript_adjoint(ret);
  BaseReverseHessian<Base>::transcript_hessian(ret);
  transcript_third(ret);
  
  BaseReverseMode<Base>::clear();
  return ret;
}

template <typename Base>
void BaseReverseThird<Base>::transcript_third(
    DerivativeTensor<int, Base>& tensor) {
  for (auto& kv : dep_deriv) {
    locint dep = dep_index_map[kv.first] - 1;
    int size = kv.second.third_vals->get_size();
    tensor.init_single_tensor(dep, 3, size);
    locint t[3];
    int x[3];
    Base w;
    int l = 0;
    typename type_third::enumerator t_enum = kv.second.third_vals->get_enumerator();
    bool has_next = t_enum.has_next();
    while (has_next) {
      has_next = t_enum.get_next(t[0], t[1], t[2], w);
      x[0] = indep_index_map[t[0]] - 1;
      x[1] = indep_index_map[t[1]] - 1;
      x[2] = indep_index_map[t[2]] - 1;
      tensor.put_value(dep, 3, l, x, w);
      l++;
    }
  }
}

template <typename Base>
void BaseReverseThird<Base>::process_single_deriv(locint local_dep,
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

} //namespace ReverseAD

template class ReverseAD::BaseReverseThird<double>;
template class ReverseAD::BaseReverseThird<ReverseAD::SingleForward>;
