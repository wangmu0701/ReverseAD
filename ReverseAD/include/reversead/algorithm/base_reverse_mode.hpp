#ifndef BASE_REVERSE_MODE_H_
#define BASE_REVERSE_MODE_H_

#include <math.h>

#include <set>
#include <vector>
#include <map>
#include <iostream>

#include "reversead/common/reversead_base.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/single_derivative.hpp"
#include "reversead/algorithm/derivative_tensor.hpp"

#define ENABLE_REVERSE_THIRD

#define COMBINE_D_1 info.dx += info.dy; info.dy = 0;
#define COMBINE_D_2 info.pxx += 2.0 * info.pxy + info.pyy;\
                    info.pxy = 0.0; info.pyy = 0.0;\
                    COMBINE_D_1

#ifdef ENABLE_REVERSE_THIRD
#define COMBINE_D_3 info.pxxx += 3.0*info.pxxy+3.0*info.pxyy+info.pyyy;\
                    info.pxxy = 0.0; info.pxyy = 0.0; info.pyyy = 0.0;\
                    COMBINE_D_2

#define PSEUDO_BINARY if (info.x == info.y) {info.y = NULL_LOC; COMBINE_D_3}
#else

#define PSEUDO_BINARY if (info.x == info.y) {info.y = NULL_LOC; COMBINE_D_2}
#endif // ENABLE_REVERSE_THIRD

namespace ReverseAD {

template <typename Base>
class BaseReverseMode {
 public:
  typedef typename SingleDerivative<Base>::type_adjoint type_adjoint;
  typedef typename SingleDerivative<Base>::type_hessian type_hessian;
  typedef typename SingleDerivative<Base>::type_third type_third;
  typedef SingleDerivative<Base> SingleDeriv;

  BaseReverseMode(const std::shared_ptr<TrivialTrace<Base>>& trace) {
    this->trace = trace;
  }

  virtual DerivativeTensor<locint, Base> compute(int ind_num, int dep_num) {
    double time = get_timing();
    reverse_local_computation(ind_num, dep_num);
    time = get_timing();
    logger.info << "reverse local compute timing : " << time << std::endl;
    for (auto& kv : dep_deriv) {
      logger.info << "Dep : " << kv.first << std::endl;
      kv.second.debug(logger.info);
    }
    return transcript_result(); 
  }

 protected:
  BaseReverseMode() {}

  void reverse_local_computation(int, int);

  void compute_adjoint_sac(const DerivativeInfo<locint, Base>& info,
                           type_adjoint& adjoint_vals,
                           const Base& w);

  void compute_hessian_sac(const DerivativeInfo<locint, Base>& info,
                           type_hessian& hessian_vals,
                           const Base& w,
                           const type_adjoint& r);

  void compute_third_sac(const DerivativeInfo<locint, Base>& info,
                         type_third& third_vals,
                         const Base& w,
                         const type_adjoint& r,
                         const type_hessian& e);

  void compute_adjoint_deriv(const type_adjoint& local_adjoint,
                             type_adjoint& global_adjoint,
                             const Base& w);

  void compute_hessian_deriv(locint local_dep,
                             const type_adjoint& local_adjoint,
                             const type_hessian& local_hessian,
                             type_hessian& global_hessian,
                             const Base& w,
                             const type_adjoint& r);

  void compute_third_deriv(locint local_dep,
                           const type_adjoint& local_adjoint,
                           const type_hessian& local_hessian,
                           const type_third& local_third,
                           type_third& global_third,
                           const Base& w,
                           const type_adjoint& r,
                           const type_hessian& e);

  
  virtual void process_sac(const DerivativeInfo<locint, Base>& info) = 0;

  virtual void init_dep_deriv(SingleDeriv& deriv, locint dep) = 0;

  virtual DerivativeTensor<locint, Base> transcript_result() = 0;

  std::shared_ptr<TrivialTrace<Base>> trace;
  std::map<locint, std::set<locint> > reverse_live;
  std::map<locint, SingleDeriv> dep_deriv;
  std::map<locint, locint> indep_index_map;
  std::map<locint, locint> dep_index_map;
};

template <typename Base>
void BaseReverseMode<Base>::reverse_local_computation(int ind_num, int dep_num) {
    DerivativeInfo<locint, Base> info;
 
    if (ind_num != trace->get_num_ind()) {
      logger.warning << "The given number of independent variables (" << ind_num << ")"
                  << " does not match the record on the trace (" << trace->get_num_ind()
                  << "). Will proceed with the trace. " << std::endl;
    }
    if (dep_num != trace->get_num_dep()) {
      logger.warning << "The given number of dependent variables (" << ind_num << ")"
                  << " does not match the record on the trace (" << trace->get_num_dep()
                  << "). Will proceed with the trace. " << std::endl;
    }
    int ind_count = trace->get_num_ind();
    int dep_count = trace->get_num_dep();

    locint res;
    double coval;
    trace->init_reverse();
    opbyte op = trace->get_next_op_r();

    while (op != start_of_tape) {
      info.clear();
      info.opcode = op;
      switch (op) {
        case start_of_tape:
        case end_of_tape:
          break;
        case assign_ind:
          res = trace->get_next_loc_r();;
          trace->get_next_val_r();
          indep_index_map[res] = ind_count;
          ind_count--;
          break;
        case assign_dep:
          res = trace->get_next_loc_r();
          trace->get_next_val_r();
          init_dep_deriv(dep_deriv[res], res);
          reverse_live[res].insert(res);
          dep_index_map[res] = dep_count;
          dep_count--; 
          break;
        case assign_param:
          info.r = trace->get_next_loc_r();
          trace->get_next_param_r();
          break;
        case assign_d:
          info.r = trace->get_next_loc_r();
          trace->get_next_coval_r();
          break;
        case assign_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = 1.0;
          break;
        case comp_eq:
        case comp_lt:
          trace->get_next_loc_r();
          trace->get_next_loc_r();
          trace->get_next_coval_r();
          break;
        case eq_plus_a:
        case plus_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = 1.0;
          info.dy = 1.0;
          PSEUDO_BINARY
          break;
        case eq_plus_d:
        case plus_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          trace->get_next_coval_r();
          info.dx = 1.0;
          break;
        case eq_minus_a:
        case minus_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = 1.0;
          info.dy = -1.0;
          PSEUDO_BINARY
          break;
        case minus_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          trace->get_next_coval_r();
          info.dx = -1.0;
          break;
        case eq_mult_a:
        case mult_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vy = trace->get_next_val_r();
          info.vx = trace->get_next_val_r();
          info.dx = info.vy;
          info.dy = info.vx;
          info.pxy = 1.0;
          PSEUDO_BINARY
          break;
        case eq_mult_d:
        case mult_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = trace->get_next_coval_r();
          break;
        case eq_div_a:
        case div_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vy = trace->get_next_val_r();
          info.vx = trace->get_next_val_r();
          info.dx = 1.0 / info.vy;
          info.dy = -info.vx / (info.vy*info.vy);
          info.pxy = -1.0 / (info.vy*info.vy);
          info.pyy = 2.0 * info.vx / (info.vy*info.vy*info.vy);
#ifdef ENABLE_REVERSE_THIRD
          info.pxyy = 2.0 / (info.vy * info.vy * info.vy);
          info.pyyy = -6.0 * info.vx / (info.vy*info.vy*info.vy*info.vy);
#endif
          PSEUDO_BINARY
          break;
        case div_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          coval = trace->get_next_coval_r();
          info.dx = -coval / (info.vx*info.vx);
          info.pxx = 2.0 * coval / (info.vx*info.vx*info.vx);
#ifdef ENABLE_REVERSE_THIRD
          info.pxxx = -6.0 * coval / (info.vx*info.vx*info.vx*info.vx);
#endif
          break;
        case sin_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          info.dx = cos(info.vx);
          info.pxx = -sin(info.vx);
#ifdef ENABLE_REVERSE_THIRD
          info.pxxx = -cos(info.vx);
#endif
          break;
        case cos_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          info.dx = -sin(info.vx);
          info.pxx = -cos(info.vx);
#ifdef ENABLE_REVERSE_THIRD
          info.pxxx = sin(info.vx);
#endif
          break;
/*
        case tan_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          {
            Base t = cos(info.vx);
            info.dx = 1.0 / (t * t);
            info.pxx = 2.0 * tan(info.vx) / (t * t);
#ifdef ENABLE_REVERSE_THIRD
            info.pxxx = -2 * (cos(2*info.vx)-2) / (t*t*t*t);
#endif
          }
          break;
*/
        case asin_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          {
            Base t = sqrt(1.0 - info.vx * info.vx);
            info.dx = 1.0 / t;
            info.pxx = info.vx / (t * t * t);
#ifdef ENABLE_REVERSE_THIRD
            info.pxxx = (2.0*info.vx*info.vx+1.0) / (t*t*t*t*t);
#endif
          }
          break;
        case acos_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          {
            Base t = -sqrt(1.0 - info.vx * info.vx);
            info.dx = 1.0 / t;
            info.pxx = info.vx / (t * t * t);
#ifdef ENABLE_REVERSE_THIRD
            info.pxxx = (2.0*info.vx*info.vx+1.0) / (t*t*t*t*t);
#endif
          }
          break;
        case atan_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          {
            Base t = 1.0 + info.vx * info.vx;
            info.dx = 1.0 / t;
            info.pxx = -2.0 * info.vx / (t * t);
#ifdef ENABLE_REVERSE_THIRD
            info.pxxx = (6.0*info.vx*info.vx-2.0)/(t*t*t);
#endif
          }
          break;
        case sqrt_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          if (info.vx != 0.0) {
            info.dx = 0.5/sqrt(info.vx);
            info.pxx = -0.5 * info.dx / info.vx;
#ifdef ENABLE_REVERSE_THIRD
            info.pxxx = -1.5 * info.pxx / info.vx;
#endif
          }
          break;
        case exp_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          info.dx = exp(info.vx);
          info.pxx = info.dx;
#ifdef ENABLE_REVERSE_THIRD
          info.pxxx = info.dx;
#endif
          break;
        case log_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          info.dx = 1.0 / info.vx;
          info.pxx = - info.dx * info.dx;
#ifdef ENABLE_REVERSE_THIRD
          info.pxxx = -2.0 * info.pxx / info.vx;
#endif
          break;
        case pow_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vy = trace->get_next_val_r();
          info.vx = trace->get_next_val_r();
          {
            Base t = pow(info.vx, info.vy);
            info.dx = info.vy * t / info.vx;
            info.pxx = (info.vy - 1) * info.dx / info.vx;
            info.dy = log(info.vx) * t;
            info.pyy = log(info.vx) * info.dy;
            info.pxy = (info.vy * log(info.vx) + 1) * t / info.vx;
#ifdef ENABLE_REVERSE_THIRD
            info.pxxx = (info.vy - 2) * info.pxx / info.vx;
            info.pxxy = (info.vy-1)*info.pxy/info.vx + info.vy*t/(info.vx*info.vx);
            info.pxyy = info.dx*log(info.vx)*log(info.vx) + 2*log(info.vx)*t/info.vx;
            info.pyyy = log(info.vx) * info.pyy;
#endif
          }
          PSEUDO_BINARY
          break;
        case pow_a_d:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          coval = trace->get_next_coval_r();
          info.coval = coval;
          {
            Base t = pow(info.vx, coval);
            info.dx = coval * t / info.vx;
            info.pxx = (coval - 1) * info.dx / info.vx;
#ifdef ENABLE_REVERSE_THIRD
            info.pxxx = (coval - 2) * info.pxx / info.vx;
#endif
          }
          break;
        case pow_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          coval = trace->get_next_coval_r();
          info.coval = coval;
          {
            Base t = pow(coval, info.vx);
            info.dx = log(coval) * t;
            info.pxx = log(coval) * info.dx;
#ifdef ENABLE_REVERSE_THIRD
            info.pxxx = log(coval) * info.pxx;
#endif
          }
          break;
        case fabs_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.vx = trace->get_next_val_r();
          if (info.vx > 0) {
            info.dx = 1.0;
          } else if (info.vx < 0) {
            info.dx = -1.0;
          } else {
            // TODO(muwang) : warning message
          }
          break;
        case rmpi_send:
        case rmpi_recv:
          break;
        default:
          logger.warning << "Unrecongized opcode : " << (int)op << std::endl; 
      }
      // call to inherited virtual functions
      process_sac(info);

      op = trace->get_next_op_r();
    }
    // this is only for preaccumulation
    info.clear();
    info.opcode = op;
    process_sac(info);
    return;
  }

template <typename Base>
void BaseReverseMode<Base>::compute_adjoint_sac(
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
void BaseReverseMode<Base>::compute_hessian_sac(
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
    if (pw != 0.0) {
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

  if (w != 0.0) {
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

template<typename Base>
void BaseReverseMode<Base>::compute_third_sac(
    const DerivativeInfo<locint, Base>& info,
    type_third& third_vals,
    const Base& w,
    const type_adjoint& r,
    const type_hessian& e) {
  locint p,q;
  double pw;
  double coeff, xcoeff, ycoeff;

  typename type_hessian::enumerator e_enum = e.get_enumerator();
  while(e_enum.has_next()) {
    e_enum.get_next(p, q, pw);
    if (p != info.r && q != info.r) { // p!=r && q!=r
      if (info.x != NULL_LOC && info.dx != 0.0) {
        xcoeff = 1.0;
        if (info.x == p) {xcoeff += 1.0;}
        if (info.x == q) {xcoeff += 1.0;}
        third_vals.increase(info.x, p, q, xcoeff * pw * info.dx);
      }
      if (info.y != NULL_LOC && info.dy != 0.0) {
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
        if (info.y != NULL_LOC && info.dy != 0.0) {
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
  
  if (w != 0.0) {
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

template <typename Base>
void BaseReverseMode<Base>::compute_adjoint_deriv(
    const type_adjoint& local_adjoint,
    type_adjoint& global_adjoint,
    const Base& w) {

  if (w != 0.0) {
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

template <typename Base>
void BaseReverseMode<Base>::compute_hessian_deriv(
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
  if (w != 0.0) {
    typename type_hessian::enumerator h_enum = local_hessian.get_enumerator();
    bool h_has_next = h_enum.has_next();
    while(h_has_next) {
      h_has_next = h_enum.get_next(p, v, pw);
      global_hessian.increase(p, v, w * pw);
    }
  }
}

template<typename Base>
void BaseReverseMode<Base>::compute_third_deriv(
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

  if (w != 0.0) {
    typename type_third::enumerator lt_enum =
        local_third.get_enumerator();
    while (lt_enum.has_next()) {
      lt_enum.get_next(x, y, z, ww);
      global_third.increase(x, y, z, w * ww);
    }
  }
}

} // namespace ReverseAD

#endif // BASE_REVERSE_MODE_H_
