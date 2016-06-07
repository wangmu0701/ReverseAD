#ifndef REVERSEAD_BASE_REVERSE_MODE_H_
#define REVERSEAD_BASE_REVERSE_MODE_H_

#include <cmath>
#include <set>
#include <map>
#include <memory>

#include "reversead/common/opcodes.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/derivative_info.hpp"
#include "reversead/algorithm/trivial_deriv.hpp"
#include "reversead/algorithm/derivative_tensor.hpp"
#include "reversead/util/error_info.hpp"

#define COMBINE_D_1 info.dx += info.dy; info.dy = 0;

#define COMBINE_D_2 info.pxx += 2.0 * info.pxy + info.pyy;\
                    info.pxy = 0.0; info.pyy = 0.0;\
                    COMBINE_D_1

#define COMBINE_D_3 info.pxxx += 3.0*info.pxxy+3.0*info.pxyy+info.pyyy;\
                    info.pxxy = 0.0; info.pxyy = 0.0; info.pyyy = 0.0;\
                    COMBINE_D_2

#define PSEUDO_BINARY if (info.x == info.y) {info.y = NULL_LOC; COMBINE_D_3}

namespace ReverseAD {

template <typename Base>
class BaseReverseMode {
 public:
  typedef typename TrivialDeriv<Base>::type_adjoint type_adjoint;
  typedef typename TrivialDeriv<Base>::type_hessian type_hessian;
  typedef typename TrivialDeriv<Base>::type_third type_third;
  typedef TrivialDeriv<Base> SingleDeriv;

  BaseReverseMode(const std::shared_ptr<TrivialTrace<Base>>& _trace)
      : trace(_trace) {}

  virtual ~BaseReverseMode() = default;

  BaseReverseMode<Base>& compute(size_t ind_num, size_t dep_num);

  virtual std::shared_ptr<DerivativeTensor<size_t, Base>> get_tensor() const = 0;

  virtual void clear();

 protected:
  BaseReverseMode() = default;

  virtual void init_dep_deriv(locint dep) = 0;

  virtual void process_sac(const DerivativeInfo<locint, Base>& info) = 0;
  
  void reverse_local_computation(size_t, size_t);

  void transcript_dep_value(std::shared_ptr<DerivativeTensor<size_t, Base>> tensor) const;

  std::shared_ptr<TrivialTrace<Base>> trace;
  std::map<locint, std::set<locint> > reverse_live;
  std::map<locint, SingleDeriv> dep_deriv;
  std::map<locint, size_t> indep_index_map;
  std::map<locint, size_t> dep_index_map;
  std::map<locint, Base> dep_value;

 private:
  // This class will only be invoked by InterativeFunc
  void reset_trace(std::shared_ptr<TrivialTrace<Base>> _trace);
  friend class IterativeFunc;
};

template <typename Base>
BaseReverseMode<Base>& BaseReverseMode<Base>::compute(size_t ind_num, size_t dep_num) {
  reverse_local_computation(ind_num, dep_num);
  return *this;
}

template <typename Base>
void BaseReverseMode<Base>::transcript_dep_value(
    std::shared_ptr<DerivativeTensor<size_t, Base>> tensor) const {
  for (auto& kv: dep_deriv) {
    size_t dep = dep_index_map.find(kv.first)->second;
    tensor->put_dep_value(dep, dep_value.find(kv.first)->second);
  }
}

template <typename Base>
void BaseReverseMode<Base>::reset_trace(
    std::shared_ptr<TrivialTrace<Base>> _trace) {
  this->trace = std::move(_trace);
}

template <typename Base>
void BaseReverseMode<Base>::clear() {
  this->reverse_live.clear();
  this->dep_deriv.clear();
  this->indep_index_map.clear();
  this->dep_index_map.clear();
  this->dep_value.clear();
}

template <typename Base>
void BaseReverseMode<Base>::reverse_local_computation(size_t ind_num, size_t dep_num) {
  using std::sin;
  using std::cos;
  using std::sqrt;
  using std::pow;
  using std::log;
  using std::exp;

    DerivativeInfo<locint, Base> info;
    
    if (ind_num != trace->get_num_ind()) {
      warning_NumberInconsistent("independent", ind_num, trace->get_num_ind());
    }
    if (dep_num != trace->get_num_dep()) {
      warning_NumberInconsistent("dependent", dep_num, trace->get_num_dep());
    }
    size_t ind_count = trace->get_num_ind();
    size_t dep_count = trace->get_num_dep();
    
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
                if (ind_count == 0) {
                  // TODO(warning)
                }
                ind_count--;
                indep_index_map[res] = ind_count;
                break;
            case assign_dep:
                res = trace->get_next_loc_r();
                dep_value[res] = trace->get_next_val_r();
                init_dep_deriv(res);
                if (dep_count == 0) {
                  // TODO(warning)
                }
                dep_count--;
                dep_index_map[res] = dep_count;
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
                info.pxyy = 2.0 / (info.vy * info.vy * info.vy);
                info.pyyy = -6.0 * info.vx / (info.vy*info.vy*info.vy*info.vy);
                PSEUDO_BINARY
                break;
            case div_d_a:
                info.r = trace->get_next_loc_r();
                info.x = trace->get_next_loc_r();
                info.vx = trace->get_next_val_r();
                coval = trace->get_next_coval_r();
                info.dx = -coval / (info.vx*info.vx);
                info.pxx = 2.0 * coval / (info.vx*info.vx*info.vx);
                info.pxxx = -6.0 * coval / (info.vx*info.vx*info.vx*info.vx);
                break;
            case sin_a:
                info.r = trace->get_next_loc_r();
                info.x = trace->get_next_loc_r();
                info.vx = trace->get_next_val_r();
                info.dx = cos(info.vx);
                info.pxx = -sin(info.vx);
                info.pxxx = -cos(info.vx);
                break;
            case cos_a:
                info.r = trace->get_next_loc_r();
                info.x = trace->get_next_loc_r();
                info.vx = trace->get_next_val_r();
                info.dx = -sin(info.vx);
                info.pxx = -cos(info.vx);
                info.pxxx = sin(info.vx);
                break;
            case asin_a:
                info.r = trace->get_next_loc_r();
                info.x = trace->get_next_loc_r();
                info.vx = trace->get_next_val_r();
            {
                Base t = sqrt(1.0 - info.vx * info.vx);
                info.dx = 1.0 / t;
                info.pxx = info.vx / (t * t * t);
                info.pxxx = (2.0*info.vx*info.vx+1.0) / (t*t*t*t*t);
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
                info.pxxx = (2.0*info.vx*info.vx+1.0) / (t*t*t*t*t);
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
                    info.pxxx = (6.0*info.vx*info.vx-2.0)/(t*t*t);
                }
                break;
            case sqrt_a:
                info.r = trace->get_next_loc_r();
                info.x = trace->get_next_loc_r();
                info.vx = trace->get_next_val_r();
                if (info.vx != 0.0) {
                    info.dx = 0.5/sqrt(info.vx);
                    info.pxx = -0.5 * info.dx / info.vx;
                    info.pxxx = -1.5 * info.pxx / info.vx;
                }
                break;
            case exp_a:
                info.r = trace->get_next_loc_r();
                info.x = trace->get_next_loc_r();
                info.vx = trace->get_next_val_r();
                info.dx = exp(info.vx);
                info.pxx = info.dx;
                info.pxxx = info.dx;
                break;
            case log_a:
                info.r = trace->get_next_loc_r();
                info.x = trace->get_next_loc_r();
                info.vx = trace->get_next_val_r();
                info.dx = 1.0 / info.vx;
                info.pxx = - info.dx * info.dx;
                info.pxxx = -2.0 * info.pxx / info.vx;
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
                info.pxxx = (info.vy - 2) * info.pxx / info.vx;
                info.pxxy = (info.vy-1)*info.pxy/info.vx + info.vy*t/(info.vx*info.vx);
                info.pxyy = info.dx*log(info.vx)*log(info.vx) + 2*log(info.vx)*t/info.vx;
                info.pyyy = log(info.vx) * info.pyy;
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
                info.pxxx = (coval - 2) * info.pxx / info.vx;
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
                info.pxxx = log(coval) * info.pxx;
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
                warning_UnrecognizedOpcode((int)op);
        }
        // call to inherited virtual functions
        process_sac(info);
        
        op = trace->get_next_op_r();
    }
    // this is only for preaccumulation
    info.clear();
    info.opcode = op;
    process_sac(info);
    trace->end_reverse();
    return;
}

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_MODE_H_
