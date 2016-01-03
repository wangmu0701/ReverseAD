#include "reversead/common/opcodes.hpp"
#include "reversead/algorithm/base_reverse_hessian.hpp"
#include "reversead/forwardtype/single_forward.hpp"

namespace ReverseAD {

template <typename Base>
void BaseReverseHessian<Base>::accumulate_deriv(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) {
  Base w = deriv.adjoint_vals->get_and_erase(info.r);
  type_adjoint r = deriv.hessian_vals->get_and_erase(info.r);
  
  compute_adjoint_sac(info, *(deriv.adjoint_vals), w);
  compute_hessian_sac(info, *(deriv.hessian_vals), w, r);
}

template <typename Base>
int BaseReverseHessian<Base>::retrieve_hessian_sparse_format(int** ssize, locint*** rind, locint*** cind, Base*** values) {
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

template <typename Base>
DerivativeTensor<int, Base> BaseReverseHessian<Base>::transcript_result() {
  int dep_size = dep_deriv.size();
  int ind_size = indep_index_map.size();
  DerivativeTensor<int, Base> ret(dep_size, ind_size, 2);
  BaseReverseMode<Base>::transcript_dep_value(ret);
  BaseReverseAdjoint<Base>::transcript_adjoint(ret);
  transcript_hessian(ret);
 
  BaseReverseMode<Base>::clear();
  return ret;
}

template <typename Base>
void BaseReverseHessian<Base>::transcript_hessian(
    DerivativeTensor<int, Base>& tensor) {
  for (auto& kv : dep_deriv) {
    locint dep = dep_index_map[kv.first] - 1;
    int size = kv.second.hessian_vals->get_size();
    tensor.init_single_tensor(dep, 2, size);
    locint t[2];
    int x[2];
    Base w;
    int l = 0;
    typename type_hessian::enumerator h_enum = kv.second.hessian_vals->get_enumerator();
    bool has_next = h_enum.has_next();
    while (has_next) {
      has_next = h_enum.get_next(t[0], t[1], w);
      x[0] = indep_index_map[t[0]] - 1;
      x[1] = indep_index_map[t[1]] - 1;
      tensor.put_value(dep, 2, l, x, w);
      l++;
    }
  }
}

template <typename Base>
void BaseReverseHessian<Base>::process_single_deriv(locint local_dep,
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

} // namespace ReverseAD

template class ReverseAD::BaseReverseHessian<double>;
template class ReverseAD::BaseReverseHessian<ReverseAD::SingleForward>;
