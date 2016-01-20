#include <cmath>

#include "reversead/common/reversead_base.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_mode.hpp"
#include "reversead/forwardtype/single_forward.hpp"

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
DerivativeTensor<int, Base> BaseReverseMode<Base>::compute(
    int ind_num, int dep_num) {
  double time = get_timing();
  reverse_local_computation(ind_num, dep_num);
  time = get_timing();
  logger.info << "reverse local compute timing : " << time << std::endl;
  //for (auto& kv : dep_deriv) {
    //logger.info << "Dep : " << kv.first << std::endl;
    //kv.second.debug(logger.info);
  //}
  return transcript_result();
}

template <typename Base>
DerivativeTensor<int, Base> BaseReverseMode<Base>::compute(
    int ind_num, int dep_num, Base* init_adjoint) {
  this->_use_dep_init_adjoint = true;
  if (dep_num != trace->get_num_dep()) {
    logger.fatal << "dep_num error!" << std::endl;
  }
  for (int i=1; i<=dep_num; i++) {
    dep_init_adjoint[i] = init_adjoint[i-1];
  }
  return compute(ind_num, dep_num);
}

template <typename Base>
void BaseReverseMode<Base>::transcript_dep_value(
    DerivativeTensor<int, Base>& tensor) {
  for (auto& kv: dep_deriv) {
    int dep = dep_index_map[kv.first] - 1;
    tensor.put_dep_value(dep, dep_value[kv.first]);
  }
}

template <typename Base>
void BaseReverseMode<Base>::clear() {
  reverse_live.clear();
  dep_deriv.clear();
  indep_index_map.clear();
  dep_index_map.clear();
  dep_init_adjoint.clear();
  dep_value.clear();
  _use_dep_init_adjoint = false;
}

template <typename Base>
void BaseReverseMode<Base>::reverse_local_computation(int ind_num, int dep_num) {
  using std::sin;
  using std::cos;
  using std::sqrt;
  using std::pow;
  using std::log;
  using std::exp;

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
                dep_value[res] = trace->get_next_val_r();
                init_dep_deriv(res, dep_count);
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

} // namespace ReverseAD

template class ReverseAD::BaseReverseMode<double>;
template class ReverseAD::BaseReverseMode<ReverseAD::SingleForward>;
