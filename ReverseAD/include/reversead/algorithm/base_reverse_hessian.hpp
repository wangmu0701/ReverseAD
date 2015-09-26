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
#include "reversead/algorithm/trivial_adjoint.hpp"
#include "reversead/algorithm/trivial_hessian.hpp"

#define COMBINE_D_1 info.dx += info.dy;
#define COMBINE_D_2 info.pxx += 2.0 * info.pxy + info.pyy;\
                    info.pxy = 0.0; info.pyy = 0.0;\
                    COMBINE_D_1

#define PSEUDO_BINARY if (info.x == info.y) {info.y = NULL_LOC; COMBINE_D_2}

namespace ReverseAD {

template <typename Base>
class BaseReverseHessian {
 public:
  typedef TrivialAdjoint<locint, Base> type_adjoint;
  typedef TrivialHessian<locint, Base> type_hessian;

  class SingleDeriv {
   public:
    SingleDeriv() {
      adjoint_vals = new type_adjoint();
      hessian_vals = new type_hessian();
    }
    SingleDeriv(char* buf) {
      adjoint_vals = new type_adjoint(buf);
      hessian_vals = new type_hessian(&buf[adjoint_vals->byte_size()]);
    }
    int byte_size() {
      return adjoint_vals->byte_size() + hessian_vals->byte_size();
    }
    void write_to_byte(char* buf) {
      adjoint_vals->write_to_byte(buf);
      hessian_vals->write_to_byte(&buf[adjoint_vals->byte_size()]);
    }
    void debug(Logger& logger) {
      adjoint_vals->debug(logger);
      hessian_vals->debug(logger);
    }
    type_adjoint* adjoint_vals;
    type_hessian* hessian_vals;
  };

  BaseReverseHessian(AbstractTrace* trace) {
    this->trace = trace;
    this->comm_tape = nullptr;
  }
  BaseReverseHessian(AbstractTrace* trace,
                     AbstractTape<SendRecvInfo>* comm_tape) {
    this->trace = trace;
    this->comm_tape = comm_tape;
  }
  void compute(int ind_num, int dep_num,
          locint** rind, locint** cind, Base** values) {
    if (dep_num != 1) {
      log.warning<< "Must be of a scalar functioni : dep_num = 1" << std::endl; 
      //return;
    }
    reverse_local_hessian(ind_num, dep_num);
    //retrieve_sparse_format(rind, cind, values);
  }
  void compute_mpi() {
    // here we should pass the correct num for ind and dep
    reverse_local_hessian(0, 0);
    for (auto& kv : dep_hess) {
      log.info << "Dep : " << kv.first << std::endl;
      kv.second.adjoint_vals->debug(log.info);
      kv.second.hessian_vals->debug(log.info);
    }
    forward_global_hessian();
  }
 private:
  void reverse_local_hessian(int ind_num, int dep_num) {
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
            log.warning << "more independents found on tape than : " << ind_num << std::endl;
            //return;
          }
          res = trace->get_next_loc_r();;
          coval = trace->get_next_val_r();
          indep_index_map[res] = ind_count;
          ind_count--;
          break;
        case assign_dep:
          if (dep_count >= dep_num) {
            log.warning << "more dependents found on tape than : " << ind_num << std::endl;
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
  void forward_global_hessian() {
    if (!comm_tape) {return;}
    comm_tape->init_forward();
    while(comm_tape->has_next_f()) {
      SendRecvInfo sr_info = comm_tape->get_next_f();
      log.info << sr_info;
      if (sr_info.comm_op == COMM_RMPI_SEND) {
        int total_buf_size = 0;
        for (int i = 0; i < sr_info.count; i++) {
          total_buf_size += dep_hess[sr_info.locs[i]].byte_size();
        }
        char* buf = new char[total_buf_size];
        total_buf_size = 0;
        for (int i = 0; i < sr_info.count; i++) {
          dep_hess[sr_info.locs[i]].write_to_byte(&buf[total_buf_size]);
          total_buf_size += dep_hess[sr_info.locs[i]].byte_size();
          dep_hess.erase(sr_info.locs[i]);
        }
        MPI_Send(&total_buf_size, 1, MPI_INT, sr_info.peer,
                 sr_info.tag, sr_info.comm);
        MPI_Send((void*)buf, total_buf_size, MPI_CHAR, sr_info.peer,
                 sr_info.tag, sr_info.comm);
        delete buf;
      } else if (sr_info.comm_op == COMM_RMPI_RECV){
        int total_buf_size = 0;
        MPI_Recv(&total_buf_size, 1, MPI_INT, sr_info.peer,
                 sr_info.tag, sr_info.comm, MPI_STATUS_IGNORE);
        char* buf = new char[total_buf_size];
        MPI_Recv((void*)buf, total_buf_size, MPI_CHAR, sr_info.peer,
                 sr_info.tag, sr_info.comm, MPI_STATUS_IGNORE);
        total_buf_size = 0;
        for(int i = 0; i < sr_info.count; i++) {
          SingleDeriv local_deriv(&buf[total_buf_size]);
          local_deriv.debug(log.info);
          // we only remove things from reverse_live_set during forward
          locint dummy_ind = sr_info.locs[i];
          std::set<locint> dep_set = std::move(reverse_live[dummy_ind]);
          reverse_live.erase(dummy_ind);
          for (const locint& dep : dep_set) {
            log.info << "processing : " << dep << std::endl;
            dep_hess[dep].debug(log.info);
            process_single_deriv(dummy_ind, local_deriv, dep_hess[dep]);
            dep_hess[dep].debug(log.info);
          }
        }
      }
    }
  }
  void process_single_deriv(locint local_dep, SingleDeriv& local_deriv, SingleDeriv& deriv) {
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
  void compute_adjoint_deriv(type_adjoint& local_adjoint,
                             type_adjoint& global_adjoint,
                             Base& w) {
    if (w != 0.0) {
      locint v;
      Base vw;
      typename type_adjoint::enumerator l_enum = local_adjoint.get_enumerator();
      bool has_next = l_enum.has_next();
      while(has_next) {
        has_next = l_enum.get_next(v, vw);
        global_adjoint[v] += w * vw;
      }
    }
  }
  void compute_hessian_deriv(locint local_dep,
                             type_adjoint& local_adjoint,
                             type_hessian& local_hessian,
                             type_hessian& global_hessian,
                             Base& w,
                             type_adjoint& r) {
    locint p, v;
    Base pw, vw;
    if (r[local_dep] != 0.0) {
      Base dw = r[local_dep];
      typename type_adjoint::enumerator a_enum = local_adjoint.get_enumerator();
      bool a_has_next = a_enum.has_next();
      while(a_has_next) {
        typename type_adjoint::enumerator a2_enum = a_enum;
        a_has_next = a_enum.get_next(p, pw);
        bool a2_has_next = true;
        while(a2_has_next) {
          a2_has_next = a2_enum.get_next(v, vw);
          if (p >= v) {
            global_hessian[p][v] += dw * pw * vw;
          } else {
            global_hessian[v][p] += dw * pw * vw;
          }
        }
      }
    }
    r.erase(local_dep);
    typename type_adjoint::enumerator r_enum = r.get_enumerator();
    bool r_has_next = r_enum.has_next();
    while(r_has_next) {
      r_has_next = r_enum.get_next(p, pw);
      typename type_adjoint::enumerator a_enum = local_adjoint.get_enumerator();
      bool a_has_next = a_enum.has_next();
      while(a_has_next) {
        a_has_next = a_enum.get_next(v, vw);
        if (p != v) {
          if (p >= v) {
            global_hessian[p][v] += pw * vw;
          } else {
            global_hessian[v][p] += pw * vw;
          }
        } else {
          global_hessian[p][v] += 2.0 * pw * vw;
        }
      }
    }
    if (w != 0.0) {
      typename type_hessian::enumerator h_enum = local_hessian.get_enumerator();
      bool h_has_next = h_enum.has_next();
      while(h_has_next) {
        h_has_next = h_enum.get_next(p, v, pw);
        if (p >= v) {
          global_hessian[p][v] += w * pw;
        } else {
          global_hessian[v][p] += w * pw;
        }
      }
    }
  }
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
      log.info << "p = " << p << "pw = " << pw << std::endl;
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
  AbstractTape<SendRecvInfo>* comm_tape;
  std::map<locint, std::set<locint> > reverse_live;
  std::map<locint, SingleDeriv> dep_hess;
  std::map<locint, locint> indep_index_map;


};

} // namespace ReverseAD

#endif // BASE_REVERSE_HESSIAN_H_
