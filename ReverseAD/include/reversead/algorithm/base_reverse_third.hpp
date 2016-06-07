#ifndef REVERSEAD_BASE_REVERSE_THIRD_H_
#define REVERSEAD_BASE_REVERSE_THIRD_H_

#include <set>
#include <map>
#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_hessian.hpp"
#include "reversead/algorithm/derivative_info.hpp"
#include "reversead/algorithm/trivial_deriv.hpp"

namespace ReverseAD {

template <typename Base>
class BaseReverseThird : public virtual BaseReverseHessian<Base> {
 public:
  typedef typename TrivialDeriv<Base>::type_adjoint type_adjoint;
  typedef typename TrivialDeriv<Base>::type_hessian type_hessian;
  typedef typename TrivialDeriv<Base>::type_third type_third;
  typedef TrivialDeriv<Base> SingleDeriv;

  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::dep_index_map;
  using BaseReverseMode<Base>::indep_index_map;

  // in template, name resolve will not look in base class
  using BaseReverseAdjoint<Base>::accumulate_adjoint_sac;
  using BaseReverseAdjoint<Base>::accumulate_adjoint_deriv;
  using BaseReverseHessian<Base>::accumulate_hessian_sac;
  using BaseReverseHessian<Base>::accumulate_hessian_deriv;

  BaseReverseThird(const std::shared_ptr<TrivialTrace<Base>>& trace)
      : BaseReverseAdjoint<Base>(trace) {}

  ~BaseReverseThird() = default;

  std::shared_ptr<DerivativeTensor<size_t, Base>> get_tensor() const override;

 protected:
  BaseReverseThird() = default;

  void accumulate_sac(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) override;

  void accumulate_deriv(locint local_dep,
                        SingleDeriv& local_deriv,
                        SingleDeriv& deriv) override;
    
  void transcript_third(std::shared_ptr<DerivativeTensor<size_t, Base>> tensor) const;

  void accumulate_third_sac(const DerivativeInfo<locint, Base>& info,
                         type_third& third_vals,
                         const Base& w,
                         const type_adjoint& r,
                         const type_hessian& e);

  void accumulate_third_deriv(locint local_dep,
                           const type_adjoint& local_adjoint,
                           const type_hessian& local_hessian,
                           const type_third& local_third,
                           type_third& global_third,
                           const Base& w,
                           const type_adjoint& r,
                           const type_hessian& e);

};

template <typename Base>
void BaseReverseThird<Base>::accumulate_sac(
    const DerivativeInfo<locint, Base>& info,
    SingleDeriv& deriv) {
  Base w = deriv.adjoint_vals->get_and_erase(info.r);
  type_adjoint r = deriv.hessian_vals->get_and_erase(info.r);
  type_hessian e = deriv.third_vals->get_and_erase(info.r);
  accumulate_adjoint_sac(info, *(deriv.adjoint_vals), w);
  accumulate_hessian_sac(info, *(deriv.hessian_vals), w, r);
  accumulate_third_sac(info, *(deriv.third_vals), w, r, e);
}

template <typename Base>
std::shared_ptr<DerivativeTensor<size_t, Base>>
    BaseReverseThird<Base>::get_tensor() const {
  size_t dep_size = dep_deriv.size();
  size_t ind_size = indep_index_map.size();
  std::shared_ptr<DerivativeTensor<size_t, Base>> ret =
      std::make_shared<DerivativeTensor<size_t, Base>>(dep_size, ind_size, 3);
  BaseReverseMode<Base>::transcript_dep_value(ret);
  BaseReverseAdjoint<Base>::transcript_adjoint(ret);
  BaseReverseHessian<Base>::transcript_hessian(ret);
  transcript_third(ret);
  
  return std::move(ret);
}

template <typename Base>
void BaseReverseThird<Base>::transcript_third(
    std::shared_ptr<DerivativeTensor<size_t, Base>> tensor) const {
  for (auto& kv : dep_deriv) {
    locint dep = dep_index_map.find(kv.first)->second;
    size_t size = kv.second.third_vals->get_size();
    tensor->init_single_tensor(dep, 3, size);
    locint t[3];
    size_t x[3];
    Base w;
    size_t l = 0;
    typename type_third::enumerator t_enum = kv.second.third_vals->get_enumerator();
    bool has_next = t_enum.has_next();
    while (has_next) {
      has_next = t_enum.get_next(t[0], t[1], t[2], w);
      x[0] = indep_index_map.find(t[0])->second;
      x[1] = indep_index_map.find(t[1])->second;
      x[2] = indep_index_map.find(t[2])->second;
      tensor->put_value(dep, 3, l, x, w);
      l++;
    }
  }
}

template <typename Base>
void BaseReverseThird<Base>::accumulate_deriv(locint local_dep,
                                                  SingleDeriv& local_deriv,
                                                  SingleDeriv& deriv) {
  Base w = deriv.adjoint_vals->get_and_erase(local_dep);
  type_adjoint r = deriv.hessian_vals->get_and_erase(local_dep);
  type_hessian e = deriv.third_vals->get_and_erase(local_dep);
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
  // compute third
  accumulate_third_deriv(local_dep,
                         *(local_deriv.adjoint_vals),
                         *(local_deriv.hessian_vals),
                         *(local_deriv.third_vals),
                         *(deriv.third_vals),
                         w,
                         r,
                         e);
}


template<typename Base>
void BaseReverseThird<Base>::accumulate_third_sac(
    const DerivativeInfo<locint, Base>& info,
    type_third& third_vals,
    const Base& w,
    const type_adjoint& r,
    const type_hessian& e) {

  locint p,q;
  Base pw;
  double coeff, xcoeff, ycoeff;
    
  typename type_hessian::enumerator e_enum = e.get_enumerator();
  while(e_enum.has_next()) {
    e_enum.get_next(p, q, pw);
    if (p != info.r && q != info.r) { // p!=r && q!=r
      if (info.x != NULL_LOC && !IsZero(info.dx)) {
        xcoeff = 1.0;
        if (info.x == p) {xcoeff += 1.0;}
        if (info.x == q) {xcoeff += 1.0;}
        third_vals.increase(info.x, p, q, xcoeff * pw * info.dx);
      }
      if (info.y != NULL_LOC && !IsZero(info.dy)) {
        ycoeff = 1.0;
        if (info.y == p) {ycoeff += 1.0;}
        if (info.y == q) {ycoeff += 1.0;}
        third_vals.increase(info.y, p, q, ycoeff * pw * info.dy);
      }
    } else if (p !=q) { // p==r || q ==r, p!=q
      if (q == info.r) {std::swap(p, q);}
      if (info.x != NULL_LOC && info.y != NULL_LOC) {
        coeff = 1.0; xcoeff = 1.0; ycoeff = 1.0;
        if (info.x == q) {coeff+=1.0; xcoeff+=2.0;}
        if (info.y == q) {coeff+=1.0; ycoeff+=2.0;}
        third_vals.increase(q, info.x, info.x, xcoeff*pw*info.dx*info.dx);
        third_vals.increase(q, info.x, info.y, coeff*pw*info.dx*info.dy);
        third_vals.increase(q, info.y, info.y, ycoeff*pw*info.dy*info.dy);
      } else if (info.x != NULL_LOC) {
        xcoeff = 1.0;
        if (info.x == q) {xcoeff+=2.0;}
        third_vals.increase(q, info.x, info.x, xcoeff*pw*info.dx*info.dx);
      }
    } else { // p==q==r
      if (info.x != NULL_LOC) {
        third_vals.increase(info.x, info.x, info.x,
                            pw * info.dx * info.dx * info.dx);
        if (info.y != NULL_LOC && !IsZero(info.dy)) {
          third_vals.increase(info.x, info.x, info.y,
                              pw * info.dx * info.dx * info.dy);
          third_vals.increase(info.x, info.y, info.y,
                              pw * info.dx * info.dy * info.dy);
          third_vals.increase(info.y, info.y, info.y,
                              pw * info.dy * info.dy * info.dy);
        }
      }
    } // if
  } // while
    
  typename type_adjoint::enumerator r_enum = r.get_enumerator();
  while (r_enum.has_next()) {
    r_enum.get_next(p, pw);
    if (p != info.r) {
      if (info.x != NULL_LOC && info.y != NULL_LOC) {
        coeff = xcoeff = ycoeff = 1.0;
        if (info.x == p) {coeff+=1.0;xcoeff+=2.0;}
        if (info.y == p) {coeff+=1.0;ycoeff+=2.0;}
        third_vals.increase(p, info.x, info.x, xcoeff*pw*info.pxx);
        third_vals.increase(p, info.x, info.y, coeff*pw*info.pxy);
        third_vals.increase(p, info.y, info.y, ycoeff*pw*info.pyy);
      } else if (info.x != NULL_LOC) {
        xcoeff = 1.0;
        if (info.x == p) {xcoeff +=2.0;}
          third_vals.increase(p, info.x, info.x, xcoeff*pw*info.pxx);
      }
    } else { // p == info.r
      if (info.x != NULL_LOC) {
        third_vals.increase(info.x, info.x, info.x,
                            3.0*pw*info.dx*info.pxx);
        if (info.y != NULL_LOC) {
          third_vals.increase(info.x, info.x, info.y,
                              2.0*pw*info.dx*info.pxy+pw*info.dy*info.pxx);
          third_vals.increase(info.x, info.y, info.y,
                              2.0*pw*info.dy*info.pxy+pw*info.dx*info.pyy);
          third_vals.increase(info.y, info.y, info.y,
                              3.0*pw*info.dy*info.pyy);
        }
      }
    }
  } // while
    
  if (!IsZero(w)) {
    if (info.x != NULL_LOC) {
      third_vals.increase(info.x, info.x, info.x, w*info.pxxx);
      if (info.y != NULL_LOC) {
        third_vals.increase(info.x, info.x, info.y, w*info.pxxy);
        third_vals.increase(info.x, info.y, info.y, w*info.pxyy);
        third_vals.increase(info.y, info.y, info.y, w*info.pyyy);
      }
    }
  }
}


template<typename Base>
void BaseReverseThird<Base>::accumulate_third_deriv(
    locint local_dep,
    const type_adjoint& local_adjoint,
    const type_hessian& local_hessian,
    const type_third& local_third,
    type_third& global_third,
    const Base& w,
    const type_adjoint& r,
    const type_hessian& e) {
    
    locint p, q, x, y, z;
    Base ww, wx, wy, wz;
    double coeff;
    typename type_hessian::enumerator e_enum = e.get_enumerator();
    while(e_enum.has_next()) {
        e_enum.get_next(p, q, ww);
        if (p != local_dep && q != local_dep) { // p != dep && q != dep
            typename type_adjoint::enumerator la_enum = local_adjoint.get_enumerator();
            while(la_enum.has_next()) {
                la_enum.get_next(x, wx);
                coeff = 1.0;
                if (p == x) {coeff += 1.0;}
                if (q == x) {coeff += 1.0;}
                global_third.increase(x, p, q, coeff*ww*wx);
            }
        } else if (p != q) { // p == dep != q
            if (q == local_dep) {std::swap(p, q);}
            typename type_adjoint::enumerator la_enum1 = local_adjoint.get_enumerator();
            while (la_enum1.has_next()) {
                typename type_adjoint::enumerator la_enum2 = la_enum1;
                la_enum1.get_next(x, wx);
                while (la_enum2.has_next()) {
                    la_enum2.get_next(y, wy);
                    coeff = 1.0;
                    if (x == y) {
                        if (q == x) {coeff += 2.0;}
                    } else if (q == x || q == y) {
                        coeff += 1.0;
                    }
                    global_third.increase(q, x, y, coeff*ww*wx*wy);
                }
            }
        } else { // p == q == dep
            typename type_adjoint::enumerator la_enum1 = local_adjoint.get_enumerator();
            while(la_enum1.has_next()) {
                typename type_adjoint::enumerator la_enum2 = la_enum1;
                la_enum1.get_next(x, wx);
                while (la_enum2.has_next()) {
                    typename type_adjoint::enumerator la_enum3 = la_enum2;
                    la_enum2.get_next(y, wy);
                    while (la_enum3.has_next()) {
                        la_enum3.get_next(z, wz);
                        global_third.increase(x, y, z, ww*wx*wy*wz);
                    }
                }
            }
        } 
    } // while
    
    typename type_adjoint::enumerator r_enum = r.get_enumerator();
    while (r_enum.has_next()) {
        r_enum.get_next(p, ww);
        if (p != local_dep) { // p != local_dep
            typename type_hessian::enumerator lh_enum =
            local_hessian.get_enumerator();
            while (lh_enum.has_next()) {
                lh_enum.get_next(x, y, wx);
                coeff = 1.0;
                if (p == x) {coeff += 1.0;}
                if (p == y) {coeff += 1.0;}
                global_third.increase(p, x, y, coeff * ww * wx);
            }
        } else { // p == local_dep
            typename type_hessian::enumerator lh_enum = 
            local_hessian.get_enumerator();
            while (lh_enum.has_next()) {
                lh_enum.get_next(x, y, wx);
                typename type_adjoint::enumerator la_enum = 
                local_adjoint.get_enumerator();
                while (la_enum.has_next()) {
                    la_enum.get_next(z, wz);
                    coeff = 1.0;
                    if (x == z) {coeff += 1.0;}
                    if (y == z) {coeff += 1.0;}
                    global_third.increase(x, y, z, coeff * ww * wx * wz);
                }
            }
        }
    } // while
    
    if (!IsZero(w)) {
        typename type_third::enumerator lt_enum =
        local_third.get_enumerator();
        while (lt_enum.has_next()) {
            lt_enum.get_next(x, y, z, ww);
            global_third.increase(x, y, z, w * ww);
        }
    }
}

} //namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_THIRD_H_
