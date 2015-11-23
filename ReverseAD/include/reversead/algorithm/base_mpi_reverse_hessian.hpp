#ifndef BASE_MPI_REVERSE_HESSIAN_H_
#define BASE_MPI_REVERSE_HESSIAN_H_

#include "reversead/common/reversead_config.h"

#ifdef ENABLE_REVERSEAD_MPI

#include "mpi.h"
#include "reversead/algorithm/base_reverse_hessian.hpp"

namespace ReverseAD {

extern int num_dummy_ind;
extern int num_dummy_dep;

template <typename Base>
class BaseMpiReverseHessian : public BaseReverseHessian<Base> {
 public:
  typedef typename BaseReverseHessian<Base>::type_adjoint type_adjoint;
  typedef typename BaseReverseHessian<Base>::type_hessian type_hessian;
  typedef typename BaseReverseHessian<Base>::SingleDeriv SingleDeriv;

  using BaseReverseHessian<Base>::dep_deriv;
  using BaseReverseHessian<Base>::reverse_live;
  using BaseReverseHessian<Base>::trace;

  BaseMpiReverseHessian(AbstractTrace* trace)
    : BaseReverseHessian<Base>(trace) {
  }

  void compute_mpi() {
    // here we should pass the correct num for ind and dep
    double time = get_timing();
    this->reverse_local_computation(trace->get_num_ind(), trace->get_num_dep());
    time = get_timing();
    log.warning << "reverse  local hessian timing : " << time << std::endl;

    for (auto& kv : dep_deriv) {
      log.info << "Dep : " << kv.first << std::endl;
      kv.second.adjoint_vals->debug(log.info);
      kv.second.hessian_vals->debug(log.info);
    }

    forward_global_hessian();
    time = get_timing();
    log.warning << "forward global hessian timing : " << time << std::endl;
    for (auto& kv : dep_deriv) {
      log.info << "Dep : " << kv.first << std::endl;
      kv.second.adjoint_vals->debug(log.info);
      kv.second.hessian_vals->debug(log.info);
    }
  }
 protected:
  void forward_global_hessian() {
    std::vector<locint> temp_loc_vec;
    trace->init_comm_forward();
    while(trace->has_next_sr_info_f()) {
      SendRecvInfo sr_info = trace->get_next_sr_info_f();
      //log.info << sr_info;
      if (sr_info.comm_op == COMM_RMPI_SEND) {
        int total_buf_size = 0;
        locint dummy_ind;
        for (int i = 0; i < sr_info.count; i++) {
          dummy_ind = trace->get_next_comm_loc_f();
          temp_loc_vec.push_back(dummy_ind);
          total_buf_size += dep_deriv[dummy_ind].byte_size();
        }
        char* buf = new char[total_buf_size];
        total_buf_size = 0;
        for (int i = 0; i < sr_info.count; i++) {
          dummy_ind = temp_loc_vec[i];
          dep_deriv[dummy_ind].write_to_byte(&buf[total_buf_size]);
          total_buf_size += dep_deriv[dummy_ind].byte_size();
          dep_deriv.erase(dummy_ind);
        }
        temp_loc_vec.clear();
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
          total_buf_size += local_deriv.byte_size();
          //local_deriv.debug(log.info);
          // we only remove things from reverse_live_set during forward
          locint dummy_ind = trace->get_next_comm_loc_f();
          //log.info << "dummy_ind = " << dummy_ind << std::endl;
          std::set<locint> dep_set = std::move(reverse_live[dummy_ind]);
          reverse_live.erase(dummy_ind);
          for (const locint& dep : dep_set) {
            //log.info << "processing : " << dummy_ind << std::endl;
            //dep_deriv[dep].debug(log.info);
            process_single_deriv(dummy_ind, local_deriv, dep_deriv[dep]);
            //dep_deriv[dep].debug(log.info);
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

  // protected members
  AbstractTape<SendRecvInfo>* comm_tape;
};

} // namespace ReverseAD

#endif // ENABLE_REVERSEAD_MPI

#endif // BASE_REVERSE_HESSIAN_H_
