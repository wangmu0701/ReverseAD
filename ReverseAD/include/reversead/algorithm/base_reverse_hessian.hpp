#ifndef BASE_REVERSE_HESSIAN_H_
#define BASE_REVERSE_HESSIAN_H_

#include <set>
#include <vector>
#include <map>
#include <iostream>

#include "reversead/reversead_base.hpp"
#include "reversead/opcodes.hpp"
#include "reversead/trace/abstract_trace.hpp"
#include "reversead/tape/abstract_tape.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "single_derivative.hpp"

#define COMBINE_D_1 info.dx += info.dy;
#define COMBINE_D_2 info.pxx += 2.0 * info.pxy + info.pyy;\
                    info.pxy = 0.0; info.pyy = 0.0;\
                    COMBINE_D_1

#define PSEUDO_BINARY if (info.x == info.y) {info.y = NULL_LOC; COMBINE_D_2}

namespace ReverseAD {

template <typename Base>
class BaseReverseHessian {
 public:
  typedef typename SingleDerivative<Base>::type_adjoint type_adjoint;
  typedef typename SingleDerivative<Base>::type_hessian type_hessian;
  typedef SingleDerivative<Base> SingleDeriv;

  BaseReverseHessian(AbstractTrace* trace) {
    this->trace = trace;
  }

  void compute(int ind_num, int dep_num,
          locint** rind, locint** cind, Base** values) {
    if (dep_num != 1) {
      log.warning<< "Must be of a scalar functioni : dep_num = 1" << std::endl; 
      //return;
    }
    double time = get_timing();
    reverse_local_hessian(ind_num, dep_num);
    time = get_timing();
    log.warning << "reverse local hessian timing : " << time << std::endl;
    for (auto& kv : dep_hess) {
      log.info << "Dep : " << kv.first << std::endl;
      kv.second.debug(log.info);
    }
    //retrieve_sparse_format(rind, cind, values);
  }

 //protected:
  void reverse_local_hessian(int, int);

  void process_sac(DerivativeInfo<locint, Base>& info, SingleDeriv& deriv) {
    Base w = deriv.adjoint_vals->get_and_erase(info.r);
    type_adjoint r = deriv.hessian_vals->get_and_erase(info.r);
    compute_adjoint_sac(info, *(deriv.adjoint_vals), w);
    compute_hessian_sac(info, *(deriv.adjoint_vals),*(deriv.hessian_vals),w,r);
  }

  /*
  void retrieve_sparse_format(locint** rind, locint** cind, Base** values) {
    int size = hessian_vals.get_size();
    (*rind) = new locint[size];
    (*cind) = new locint[size];
    (*values) = new Base[size];
    //hessian_vals.debug();
    typename type_hessian::enumerator h_enum = hessian_vals.get_enumerator();
    bool has_next = h_enum.has_next();
    locint x,y;
    Base w;
    int l =0;
    while(has_next) {
      has_next = h_enum.get_next(x, y, (*values)[l]);
      (*rind)[l] = indep_index_map[x];
      (*cind)[l] = indep_index_map[y];
      l++;
    }
    for(int i=0; i<size;i++) {
      std::cout << "H["<<(*rind)[i]<<","<<(*cind)[i]<<"] = "
                << (*values)[i] << std::endl;
    }
  }
  */

  void compute_adjoint_sac(DerivativeInfo<locint, Base>& info,
                           type_adjoint& adjoint_vals,
                           Base& w) {
    if (info.x != NULL_LOC) {
      adjoint_vals[info.x] += w * info.dx;
    }
    if (info.y != NULL_LOC) {
      adjoint_vals[info.y] += w * info.dy;
    }
  }
  void compute_hessian_sac(DerivativeInfo<locint, Base>& info,
                           type_adjoint& adjoint_vals,
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

  // private members
  AbstractTrace* trace;
  std::map<locint, std::set<locint> > reverse_live;
  std::map<locint, SingleDeriv> dep_hess;
  std::map<locint, locint> indep_index_map;

};

template <typename Base>
void BaseReverseHessian<Base>::reverse_local_hessian(int ind_num, int dep_num) {
    DerivativeInfo<locint, Base> info;
 
    int ind_count = ind_num - 1;
    int dep_count = 0;

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
          if (ind_count < 0) {
            //log.warning << "more independents found on tape than : " << ind_num << std::endl;
            //return;
          }
          res = trace->get_next_loc_r();;
          coval = trace->get_next_val_r();
          indep_index_map[res] = ind_count;
          ind_count--;
          break;
        case assign_dep:
          if (dep_count >= dep_num) {
            //log.warning << "more dependents found on tape than : " << ind_num << std::endl;
            //return;
          }
          res = trace->get_next_loc_r();
          coval = trace->get_next_val_r();
          (*(dep_hess[res].adjoint_vals))[res] = 1.0;
          reverse_live[res].insert(res);
          //adjoint_vals[res] = 1.0;
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
          coval = trace->get_next_val_r();
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
          PSEUDO_BINARY
          break;
        case mult_d_a:
          info.r = trace->get_next_loc_r();
          info.x = trace->get_next_loc_r();
          info.dx = trace->get_next_val_r();
          break;
        case rmpi_send:
        case rmpi_recv:
          break;
        default:
          log.warning << "Unrecongized opcode : " << (int)op << std::endl; 
      }
      if (info.r != NULL_LOC) {
        //info.debug();
        std::set<locint> dep_set = std::move(reverse_live[info.r]);
        reverse_live.erase(info.r);
        for (const locint& dep : dep_set) {
          process_sac(info, dep_hess[dep]);
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

#endif // BASE_REVERSE_HESSIAN_H_
