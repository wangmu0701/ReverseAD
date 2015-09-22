#ifndef BASE_REVERSE_HESSIAN_H_
#define BASE_REVERSE_HESSIAN_H_

#include <vector>
#include <map>
#include <iostream>

#include "reversead/reversead_base.hpp"
#include "reversead/opcodes.hpp"
#include "reversead/trace/abstract_trace.hpp"
#include "reversead/tape/abstract_tape.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/trivial_adjoint.hpp"
#include "reversead/algorithm/trivial_hessian.hpp"


namespace ReverseAD {

template <typename Base>
class BaseReverseHessian {
 public:

  BaseReverseHessian(AbstractTrace* trace) {
    this->trace = trace;
  }
  void compute(int ind_num, int dep_num,
          locint** rind, locint** cind, Base** values) {
    if (dep_num != 1) {
      std::cout << "Must be of a scalar functioni : dep_num = 1" << std:endl; 
      return;
    }
    TrivialHessian<locint, Base> hessian_vals;
    TrivialAdjiont<Locint, Base> adjoint_vals;
    std::map<locint, locint> indep_index_map;
    DerivativeInfo<locint, Base> info;
 
    int ind_count = ind_num - 1;
    int dep_count = 0;

    locint res;
    locint arg1;
    locint arg2;
    double coval;
    Base arg1_val;
    Base arg2_val;

    trace->init_reverse();
    opbyte op = trace->get_next_op_r();

    while (op != start_of_tape) {
      info.clear();
      switch (op) {
        case start_of_tape:
        case end_of_tape:
          break;
        case assign_ind:
          if (ind_count < 0) {
            std::cerr << "more independents found on tape than : " << ind_num << std::endl;
            return;
          }
          res = trace->get_next_loc_r();;
          coval = trace->get_next_val_r();
          indep_index_map[res] = ind_count;
          ind_count--;
          break;
        case assign_dep:
          if (dep_count >= dep_num) {
            std::cerr << "more dependents found on tape than : " << ind_num << std::endl;
            return;
          }
          res = trace->get_next_loc_r();
          coval = trace->get_next_val_r();
          adjoint_vals[res] = 1.0;
          std::cout << "this is where everything begins" << std::endl;
          dep_count++; 
          break;
        case assign_d:
          info.r = trace->get_next_loc_r();
          coval = trace->get_next_val_r();
          break;
        case assign_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = 1.0;
          std::cout << "assign_a_a : " << info.r << " = " << info.x << std::endl; 
          break;
        case plus_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = 1.0;
          info.dy = 1.0;
          std::cout << "plus_a_a : " << info.r << " = "
              << info.x << " + " << info.y << std::endl;
          break;
        case plus_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          coval = trace->get_next_val_r();
          info.dx = 1.0;
          break;
        case minus_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = 1.0;
          info.dy = -1.0;
          break;
        case minus_a_d:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          coval = trace->get_next_val_r();
          info.dx = 1.0;
          break;
        case minus_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          coval = trace->get_next_val_r();
          info.dx = -1.0;
          break;
        case mult_a_a:
          info.r = trace->get_next_loc_r();
          info.y = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = trace->get_next_val_r();
          info.dy = trace->get_next_val_r();
          info.pxy = 1.0;
          break;
        case mult_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = trace->get_next_val_r();
          break;
        default:
          std::cerr << "Unrecongized opcode : " << (int)op << std::endl; 
      }
      if (info.r != NULL_LOC) {
        Base w = adjoint_vals.get_and_erase(info.r);
        TrivialAdjoint<locint, Base> r = hessian_vals.get_and_erase(info.r);
        compute_adjoint(info, adjoint_vals, w);
        compute_hessian(info, adjoint_vals, hessian_vals, w, r);
      } 
      op = trace->get_next_op_r();
    }
    return adjoint_ind;
  }
  
 private:
  AbstractTrace* trace;
  void compute_adjoint(DerivativeInfo<locint, Base>& info,
                       TrivialAdjiont<locint, Base>& adjoint_vals,
                       Base& w) {
    if (info.x != NULL_LOC) {
      adjoint_vals[info.x] += w * info.dx;
    }
    if (info.y != NULL_LOC) {
      adjoint_vals[info.y] += w * info.dy;
    }
  }
  void compute_hessian(DerivativeInfo<locint, Base>& info,
                       TrivialAdjiont<locint, Base>& adjoint_vals,
                       TrivialHessian<locint, Base>& hessian_vals,
                       Base& w,
                       TrivialAdjiont<locint, Base>& r) {
    typename TrivialAdjoint<locint, Base>::enumerator r_enum =
      r.get_enumerator();
    bool has_next = r_enum.has_next();
    locint p;
    Base pw;
    while (has_next) {
      has_next = r_enum.get_next(p, pw);
      if (pw != 0.0) {
        if (info.y != NULL_LOC) {
          if (p != info.r) {
            if (p == info.x) {
              hessian_vals.increase(p, p, 2 * info.dx * w);
            } else {
              hessian_vals.increase(info.x, p, info.dx * w);
            }
            if (p == info.y) {
              hessian_vals.increase(p, p, 2 * info.dy * w);
            } else {
              hessian_vals.increase(info.y, p, info.dy * w);
            }
          } else { // p == info.r
            hessian_vals.increase(info.x, info.x, info.dx*info.dx*w);
            hessian_vals.increase(info.x, info.y, info.dx*info.dy*w);
            hessian_vals.increase(info.y, info.y, info.dy*info.dy*w);
          } 
        } else { // info.y == NULL_LOC
          if (p != info.r) {
            if (p == info.x) {
              hessian_vals.increase(p, p, 2 * info.dx * w);
            } else {
              hessian_vals.increase(info.dx, p, info.dx * w);
            }
          } else {
            hessian_vals.increase(info.x, info.x, info.dx * info.dx * w);
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
        if (info.x != info.y) {
          hessian_vals.increase(info.x, info.y, w * info.pxy);
        } else {
          hessian_vals.increase(info.x, info.y, 2.0 * w * info.pxy);
        }
      }
    }
  }

};

} // namespace ReverseAD

#endif // BASE_REVERSE_HESSIAN_H_
