#ifndef BASE_REVERSE_HESSIAN_H_
#define BASE_REVERSE_HESSIAN_H_

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

#define COMBINE_D_1 info.dx += info.dy;
#define COMBINE_D_2 info.pxx += 2.0 * info.pxy + info.pyy;\
                    info.pxy = 0.0; info.pyy = 0.0;\
                    COMBINE_D_1

#define PSEUDO_BINARY if (info.x == info.y) {info.y = NULL_LOC; COMBINE_D_2}

namespace ReverseAD {

template <typename Base>
class BaseReverseHessian : public BaseReverseMode<Base> {
 public:
  typedef typename SingleDerivative<Base>::type_adjoint type_adjoint;
  typedef typename SingleDerivative<Base>::type_hessian type_hessian;
  typedef SingleDerivative<Base> SingleDeriv;

  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::dep_index_map;
  using BaseReverseMode<Base>::indep_index_map;

  BaseReverseHessian(AbstractTrace* trace) : BaseReverseMode<Base>(trace) {}

  void init_dep_deriv(SingleDeriv& deriv, locint dep) {
    (*deriv.adjoint_vals)[dep] = 1.0;
  }

  void process_sac(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) {
    Base w = deriv.adjoint_vals->get_and_erase(info.r);
    type_adjoint r = deriv.hessian_vals->get_and_erase(info.r);
    compute_adjoint_sac(info, *(deriv.adjoint_vals), w);
    compute_hessian_sac(info, *(deriv.hessian_vals),w,r);
  }

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

  void compute_hessian_sac(const DerivativeInfo<locint, Base>& info,
                           type_hessian& hessian_vals,
                           Base& w,
                           type_adjoint& r) {
    typename type_adjoint::enumerator r_enum =
      r.get_enumerator();
    bool has_next = r_enum.has_next();
    locint p;
    Base pw;
    while (has_next) {
      has_next = r_enum.get_next(p, pw);
      //log.info << "p = " << p << "pw = " << pw << std::endl;
      if (pw != 0.0) {
        if (info.y != NULL_LOC) {
          if (p != info.r) {
            if (p == info.x) {
              hessian_vals[p][p] += 2 * info.dx * pw;
              //hessian_vals.increase(p, p, 2 * info.dx * pw);
            } else {
              if (info.x > p) {
                hessian_vals[info.x][p] += info.dx * pw;
              } else {
                hessian_vals[p][info.x] += info.dx * pw;
              }
              //hessian_vals.increase(info.x, p, info.dx * pw);
            }
            if (p == info.y) {
              hessian_vals[p][p] += 2 * info.dy * pw;
              //hessian_vals.increase(p, p, 2 * info.dy * pw);
            } else {
              if (info.y > p) {
                hessian_vals[info.y][p] += info.dy * pw;
              } else {
                hessian_vals[p][info.y] += info.dy * pw;
              }
              //hessian_vals.increase(info.y, p, info.dy * pw);
            }
          } else { // p == info.r
            hessian_vals[info.x][info.x] += info.dx * info.dx * pw;
            //hessian_vals.increase(info.x, info.x, info.dx*info.dx*pw);
            if (info.x > info.y) {
              hessian_vals[info.x][info.y] += info.dx * info.dx * pw;
            } else {
              hessian_vals[info.y][info.x] += info.dx * info.dy * pw;
            }
            //hessian_vals.increase(info.x, info.y, info.dx*info.dy*pw);
            hessian_vals[info.y][info.y] += info.dy * info.dy * pw;
            //hessian_vals.increase(info.y, info.y, info.dy*info.dy*pw);
          } 
        } else { // info.y == NULL_LOC
          if (p != info.r) {
            if (p == info.x) {
              hessian_vals[p][p] += 2 * info.dx * pw;
              //hessian_vals.increase(p, p, 2 * info.dx * pw);
            } else {
              if (info.x > p) {
                hessian_vals[info.x][p] += info.dx * pw;
              } else {
                hessian_vals[p][info.x] += info.dx * pw;
              }
              //hessian_vals.increase(info.dx, p, info.dx * pw);
            }
          } else {
            hessian_vals[info.x][info.x] += info.dx * info.dx * pw;
            //hessian_vals.increase(info.x, info.x, info.dx * info.dx * pw);
          }
        }
      } // pw != 0.0
    } // while (has_next)
    if (w != 0.0) {
      if (info.pxx != 0.0) {
        hessian_vals[info.x][info.x] += info.pxx * w;
        //hessian_vals.increase(info.x, info.x, info.pxx * w);
      }
      if (info.pyy != 0.0) {
        hessian_vals[info.y][info.y] += info.pyy * w;
        //hessian_vals.increase(info.y, info.y, info.pyy * w);
      }
      if (info.pxy != 0.0) {
        // already eliminate pseudo binary functions, menas info.x != info.y
        if (info.x > info.y) {
          hessian_vals[info.x][info.y] += info.pxy * w;
        } else {
          hessian_vals[info.y][info.x] += info.pxy * w;
        }
        //hessian_vals.increase(info.x, info.y, w * info.pxy);
      }
    }
  }
};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_HESSIAN_H_
