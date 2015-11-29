#ifndef BASE_REVERSE_MODE_H_
#define BASE_REVERSE_MODE_H_

#include <math.h>

#include <set>
#include <vector>
#include <map>
#include <iostream>

#include "reversead/common/reversead_base.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/trace/abstract_trace.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/single_derivative.hpp"

#define COMBINE_D_1 info.dx += info.dy;
#define COMBINE_D_2 info.pxx += 2.0 * info.pxy + info.pyy;\
                    info.pxy = 0.0; info.pyy = 0.0;\
                    COMBINE_D_1

#define PSEUDO_BINARY if (info.x == info.y) {info.y = NULL_LOC; COMBINE_D_2}

namespace ReverseAD {

template <typename Base>
class BaseReverseMode {
 public:
  typedef typename SingleDerivative<Base>::type_adjoint type_adjoint;
  typedef typename SingleDerivative<Base>::type_hessian type_hessian;
  typedef SingleDerivative<Base> SingleDeriv;

  BaseReverseMode(AbstractTrace<Base>* trace) {
    this->trace = trace;
  }

  void compute(int ind_num, int dep_num) {
    double time = get_timing();
    reverse_local_computation(ind_num, dep_num);
    time = get_timing();
    log.info << "reverse local compute timing : " << time << std::endl;
    for (auto& kv : dep_deriv) {
      log.info << "Dep : " << kv.first << std::endl;
      kv.second.debug(log.info);
    }
  }

 protected:  
  void reverse_local_computation(int, int);

  virtual void process_sac(const DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) = 0;
  virtual void init_dep_deriv(SingleDeriv& deriv, locint dep) = 0;

  AbstractTrace<Base>* trace;
  std::map<locint, std::set<locint> > reverse_live;
  std::map<locint, SingleDeriv> dep_deriv;
  std::map<locint, locint> indep_index_map;
  std::map<locint, locint> dep_index_map;

};

template <typename Base>
void BaseReverseMode<Base>::reverse_local_computation(int ind_num, int dep_num) {
    DerivativeInfo<locint, Base> info;
 
    if (ind_num != trace->get_num_ind()) {
      log.warning << "The given number of independent variables (" << ind_num << ")"
                  << " does not match the record on the trace (" << trace->get_num_ind()
                  << "). Will proceed with the trace. " << std::endl;
    }
    if (dep_num != trace->get_num_dep()) {
      log.warning << "The given number of dependent variables (" << ind_num << ")"
                  << " does not match the record on the trace (" << trace->get_num_dep()
                  << "). Will proceed with the trace. " << std::endl;
    }
    int ind_count = trace->get_num_ind();
    int dep_count = trace->get_num_dep();

    locint res;
    Base vx, vy;
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
        case assign_d:
          info.r = trace->get_next_loc_r();
          trace->get_next_coval_r();
          break;
        case assign_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = 1.0;
          break;
        case plus_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = 1.0;
          info.dy = 1.0;
          PSEUDO_BINARY
          break;
        case plus_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          trace->get_next_coval_r();
          info.dx = 1.0;
          break;
        case minus_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = 1.0;
          info.dy = -1.0;
          PSEUDO_BINARY
          break;
        case minus_a_d:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          trace->get_next_coval_r();
          info.dx = 1.0;
          break;
        case minus_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          trace->get_next_coval_r();
          info.dx = -1.0;
          break;
        case mult_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = trace->get_next_val_r();
          info.dy = trace->get_next_val_r();
          info.pxy = 1.0;
          PSEUDO_BINARY
          break;
        case mult_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = trace->get_next_coval_r();
          break;
        case div_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          vy = trace->get_next_val_r();
          vx = trace->get_next_val_r();
          info.dx = 1.0 / vy;
          info.dy = -vx / (vy*vy);
          info.pxy = -1.0 / (vy*vy);
          info.pyy = 2.0 * vx / (vy*vy*vy);
          PSEUDO_BINARY
          break;
        case div_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          vx = trace->get_next_val_r();
          coval = trace->get_next_coval_r();
          info.dx = -coval / (vx*vx);
          info.pxx = 2.0 * coval / (vx*vx*vx);
          break;
        case sin_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          vx = trace->get_next_val_r();
          info.dx = cos(vx);
          info.pxx = -sin(vx);
          break;
        case cos_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          vx = trace->get_next_val_r();
          info.dx = -sin(vx);
          info.pxx = -cos(vx);
          break;
        case sqrt_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          vx = trace->get_next_val_r();
          if (vx != 0.0) {
            info.dx = 0.5/sqrt(vx);
            info.pxx = -0.5 * info.dx / vx;
          } else {
            info.dx = 0.0;
            info.pxx = 0.0;
          }
          break;
        case rmpi_send:
        case rmpi_recv:
          break;
        default:
          log.warning << "Unrecongized opcode : " << (int)op << std::endl; 
      }
      if (info.r != NULL_LOC) {
        std::set<locint> dep_set = std::move(reverse_live[info.r]);
        reverse_live.erase(info.r);
        for (const locint& dep : dep_set) {
          process_sac(info, dep_deriv[dep]);
          if (info.x != NULL_LOC) {
            reverse_live[info.x].insert(dep);
          }
          if (info.y != NULL_LOC) {
            reverse_live[info.y].insert(dep);
          }
        }
      } 
      op = trace->get_next_op_r();
    }
    return;
  }
} // namespace ReverseAD

#endif // BASE_REVERSE_MODE_H_
