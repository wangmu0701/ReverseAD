#ifndef REVERSEAD_BASE_REVERSE_HESSIAN_H_
#define REVERSEAD_BASE_REVERSE_HESSIAN_H_

#include <set>
#include <map>
#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_adjoint.hpp"
#include "reversead/algorithm/derivative_info.hpp"
#include "reversead/algorithm/trivial_deriv.hpp"

namespace ReverseAD {

template <typename Base>
class BaseReverseHessian : public virtual BaseReverseAdjoint<Base> {
 public:
  typedef typename TrivialDeriv<Base>::type_adjoint type_adjoint;
  typedef typename TrivialDeriv<Base>::type_hessian type_hessian;
  typedef TrivialDeriv<Base> SingleDeriv;

  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::dep_index_map;
  using BaseReverseMode<Base>::indep_index_map;

  // in template, name resolve will not look in base class
  using BaseReverseAdjoint<Base>::accumulate_adjoint_sac;
  using BaseReverseAdjoint<Base>::accumulate_adjoint_deriv;

  BaseReverseHessian() = default;
  BaseReverseHessian(const std::shared_ptr<TrivialTrace<Base>>& trace)
      : BaseReverseAdjoint<Base>(trace) {}

  ~BaseReverseHessian() = default;
  
 protected:
  std::shared_ptr<DerivativeTensor<size_t, Base>> get_tensor() const override;

  void accumulate_sac(
      const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) override;

  void accumulate_deriv(locint local_dep,
                        SingleDeriv& local_deriv,
                        SingleDeriv& deriv) override;

  void transcript_hessian(
      std::shared_ptr<DerivativeTensor<size_t, Base>> tensor) const;

  void accumulate_hessian_sac(const DerivativeInfo<locint, Base>& info,
                           type_hessian& hessian_vals,
                           const Base& w,
                           const type_adjoint& r);

  void accumulate_hessian_deriv(locint local_dep,
                             const type_adjoint& local_adjoint,
                             const type_hessian& local_hessian,
                             type_hessian& global_hessian,
                             const Base& w,
                             const type_adjoint& r);

};

template <typename Base>
void BaseReverseHessian<Base>::accumulate_sac(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) {
  Base w = deriv.adjoint_vals->get_and_erase(info.r);
  type_adjoint r = deriv.hessian_vals->get_and_erase(info.r);
  
  accumulate_adjoint_sac(info, *(deriv.adjoint_vals), w);
  accumulate_hessian_sac(info, *(deriv.hessian_vals), w, r);
}

template <typename Base>
std::shared_ptr<DerivativeTensor<size_t, Base>>
    BaseReverseHessian<Base>::get_tensor() const {
  size_t dep_size = dep_deriv.size();
  size_t ind_size = indep_index_map.size();
  std::shared_ptr<DerivativeTensor<size_t, Base>> ret =
      std::make_shared<DerivativeTensor<size_t, Base>>(dep_size, ind_size, 2);
  BaseReverseMode<Base>::transcript_dep_value(ret);
  BaseReverseAdjoint<Base>::transcript_adjoint(ret);
  transcript_hessian(ret);
 
  return std::move(ret);
}

template <typename Base>
void BaseReverseHessian<Base>::transcript_hessian(
    std::shared_ptr<DerivativeTensor<size_t, Base>> tensor) const {
  for (auto& kv : dep_deriv) {
    locint dep = dep_index_map.find(kv.first)->second;
    size_t size = kv.second.hessian_vals->get_size();
    tensor->init_single_tensor(dep, 2, size);
    locint t[2];
    size_t x[2];
    Base w;
    size_t l = 0;
    typename type_hessian::enumerator h_enum = kv.second.hessian_vals->get_enumerator();
    bool has_next = h_enum.has_next();
    while (has_next) {
      has_next = h_enum.get_next(t[0], t[1], w);
      x[0] = indep_index_map.find(t[0])->second;
      x[1] = indep_index_map.find(t[1])->second;
      tensor->put_value(dep, 2, l, x, w);
      l++;
    }
  }
}

template <typename Base>
void BaseReverseHessian<Base>::accumulate_deriv(locint local_dep,
                                                SingleDeriv& local_deriv,
                                                SingleDeriv& deriv) {
  Base w = deriv.adjoint_vals->get_and_erase(local_dep);
  type_adjoint r = deriv.hessian_vals->get_and_erase(local_dep);
  // compute adjoint;
  accumulate_adjoint_deriv(*(local_deriv.adjoint_vals),
                           *(deriv.adjoint_vals),
                           w);
  // compute hessian;
  accumulate_hessian_deriv(local_dep,
                           *(local_deriv.adjoint_vals),
                           *(local_deriv.hessian_vals),
                           *(deriv.hessian_vals),
                           w,
                           r);
}

template <typename Base>
void BaseReverseHessian<Base>::accumulate_hessian_sac(
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
    if (!IsZero(info.pxx)) {
      hessian_vals.increase(info.x, info.x, info.pxx * w);
    }
    if (!IsZero(info.pyy)) {
      hessian_vals.increase(info.y, info.y, info.pyy * w);
    }
    if (!IsZero(info.pxy)) {
      // already eliminate pseudo binary functions, menas info.x != info.y
      hessian_vals.increase(info.x, info.y, w * info.pxy);
    }
  }
}


template <typename Base>
void BaseReverseHessian<Base>::accumulate_hessian_deriv(
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

#endif // REVERSEAD_BASE_REVERSE_HESSIAN_H_
