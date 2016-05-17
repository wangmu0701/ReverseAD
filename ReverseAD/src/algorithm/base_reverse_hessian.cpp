#include <memory>

#include "reversead/algorithm/algorithm_common.hpp"
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
std::shared_ptr<DerivativeTensor<int, Base>>
    BaseReverseHessian<Base>::get_tensor() const {
  int dep_size = dep_deriv.size();
  int ind_size = indep_index_map.size();
  std::shared_ptr<DerivativeTensor<int, Base>> ret =
      std::make_shared<DerivativeTensor<int, Base>>(dep_size, ind_size, 2);
  BaseReverseMode<Base>::transcript_dep_value(ret);
  BaseReverseAdjoint<Base>::transcript_adjoint(ret);
  transcript_hessian(ret);
 
  return std::move(ret);
}

template <typename Base>
void BaseReverseHessian<Base>::transcript_hessian(
    std::shared_ptr<DerivativeTensor<int, Base>> tensor) const {
  for (auto& kv : dep_deriv) {
    locint dep = dep_index_map.find(kv.first)->second - 1;
    int size = kv.second.hessian_vals->get_size();
    tensor->init_single_tensor(dep, 2, size);
    locint t[2];
    int x[2];
    Base w;
    int l = 0;
    typename type_hessian::enumerator h_enum = kv.second.hessian_vals->get_enumerator();
    bool has_next = h_enum.has_next();
    while (has_next) {
      has_next = h_enum.get_next(t[0], t[1], w);
      x[0] = indep_index_map.find(t[0])->second - 1;
      x[1] = indep_index_map.find(t[1])->second - 1;
      tensor->put_value(dep, 2, l, x, w);
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

template <typename Base>
void BaseReverseHessian<Base>::compute_hessian_sac(
    const DerivativeInfo<locint, Base>& info,
    type_hessian& hessian_vals,
    const Base& w,
    const type_adjoint& r) {
    
  typename type_adjoint::enumerator r_enum =
  r.get_enumerator();
  bool has_next = r_enum.has_next();
  locint p;
  Base pw;
  while (has_next) {
    has_next = r_enum.get_next(p, pw);
    //logger.info << "p = " << p << "pw = " << pw << std::endl;
    if (!IsZero(pw)) {
      if (info.y != NULL_LOC) {
        if (p != info.r) {
          if (p == info.x) {
            hessian_vals.increase(p, p, 2 * info.dx * pw);
          } else {
            hessian_vals.increase(info.x, p, info.dx * pw);
          }
          if (p == info.y) {
            hessian_vals.increase(p, p, 2 * info.dy * pw);
          } else {
            hessian_vals.increase(info.y, p, info.dy * pw);
          }
        } else { // p == info.r
          hessian_vals.increase(info.x, info.x, info.dx*info.dx*pw);
          hessian_vals.increase(info.x, info.y, info.dx*info.dy*pw);
          hessian_vals.increase(info.y, info.y, info.dy*info.dy*pw);
        }
      } else if (info.x != NULL_LOC){
        if (p != info.r) {
          if (p == info.x) {
            hessian_vals.increase(p, p, 2 * info.dx * pw);
          } else {
            hessian_vals.increase(info.x, p, info.dx * pw);
          }
        } else {
          hessian_vals.increase(info.x, info.x, info.dx * info.dx * pw);
        }
      }
    } // pw != 0.0
  } // while (has_next)
    
  if (!IsZero(w)) {
    if (info.pxx != 0.0) {
      hessian_vals.increase(info.x, info.x, info.pxx * w);
    }
    if (info.pyy != 0.0) {
      hessian_vals.increase(info.y, info.y, info.pyy * w);
    }
    if (info.pxy != 0.0) {
      // already eliminate pseudo binary functions, menas info.x != info.y
      hessian_vals.increase(info.x, info.y, w * info.pxy);
    }
  }
}


template <typename Base>
void BaseReverseHessian<Base>::compute_hessian_deriv(
    locint local_dep,
    const type_adjoint& local_adjoint,
    const type_hessian& local_hessian,
    type_hessian& global_hessian,
    const Base& w,
    const type_adjoint& r) {
    
  locint p, v, u;
  Base pw, vw, uw;
    
  typename type_adjoint::enumerator r_enum = r.get_enumerator();
  bool r_has_next = r_enum.has_next();
  while(r_has_next) {
    r_has_next = r_enum.get_next(p, pw);
    if (p == local_dep) {
      typename type_adjoint::enumerator a_enum = local_adjoint.get_enumerator();
      bool a_has_next = a_enum.has_next();
      while(a_has_next) {
        typename type_adjoint::enumerator a2_enum = a_enum;
        a_has_next = a_enum.get_next(v, vw);
        bool a2_has_next = true;
        while(a2_has_next) {
          a2_has_next = a2_enum.get_next(u, uw);
          global_hessian.increase(v, u, pw * vw * uw);
        }
      }
    } else {
      typename type_adjoint::enumerator a_enum = local_adjoint.get_enumerator();
      bool a_has_next = a_enum.has_next();
      while(a_has_next) {
        a_has_next = a_enum.get_next(v, vw);
        if (p != v) {
          global_hessian.increase(p, v, pw * vw);
        } else {
          global_hessian.increase(p, v, 2.0 * pw * vw);
        }
      }
    }
  }
  if (!IsZero(w)) {
    typename type_hessian::enumerator h_enum = local_hessian.get_enumerator();
    bool h_has_next = h_enum.has_next();
    while(h_has_next) {
      h_has_next = h_enum.get_next(p, v, pw);
      global_hessian.increase(p, v, w * pw);
    }
  }
}


} // namespace ReverseAD

template class ReverseAD::BaseReverseHessian<double>;
template class ReverseAD::BaseReverseHessian<ReverseAD::SingleForward>;
