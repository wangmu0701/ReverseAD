#ifndef REVERSEAD_BASE_MPI_REVERSE_ADJOINT_H_
#define REVERSEAD_BASE_MPI_REVERSE_ADJOINT_H_

#include "reversead/common/reversead_config.h"

#ifdef ENABLE_REVERSEAD_MPI

#include "mpi.h"
#include "reversead/algorithm/base_reverse_adjoint.hpp"

namespace ReverseAD {

template <typename Base>
class BaseMpiReverseAdjoint : public virtual BaseReverseAdjoint<Base> {
 public:
  typedef typename BaseReverseMode<Base>::type_adjoint type_adjoint;
  typedef typename BaseReverseMode<Base>::type_hessian type_hessian;
  typedef typename BaseReverseMode<Base>::SingleDeriv SingleDeriv;

  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::trace;

  BaseMpiReverseAdjoint(const std::shared_ptr<TrivialTrace<Base>>& trace)
    : BaseReverseAdjoint<Base>(trace) {
  }

  virtual void compute_mpi() {
    // here we should pass the correct num for ind and dep
    double time = get_timing();
    this->reverse_local_computation(trace->get_num_ind(), trace->get_num_dep());
    time = get_timing();
    logger.warning << "reverse  local adjoint timing : " << time << std::endl;
    for (auto& kv : dep_deriv) {
      logger.info << "Dep : " << kv.first << std::endl;
      kv.second.adjoint_vals->debug(logger.info);
    }
    forward_global_phase();
    time = get_timing();
    logger.warning << "forward global adjoint timing : " << time << std::endl;
    for (auto& kv : dep_deriv) {
      logger.info << "Dep : " << kv.first << std::endl;
      kv.second.adjoint_vals->debug(logger.info);
    }
  }
 protected:
  BaseMpiReverseAdjoint() : BaseReverseAdjoint<Base>() {}

  virtual void forward_global_phase() {
    std::vector<locint> temp_loc_vec;
    trace->init_comm_forward();
    while(trace->has_next_sr_info_f()) {
      SendRecvInfo sr_info = trace->get_next_sr_info_f();
      //logger.info << sr_info;
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
          local_deriv.debug(logger.info);
          // we only remove things from reverse_live_set during forward
          locint dummy_ind = trace->get_next_comm_loc_f();
          logger.info << "dummy_ind = " << dummy_ind << std::endl;
          std::set<locint> dep_set = std::move(reverse_live[dummy_ind]);
          reverse_live.erase(dummy_ind);
          for (const locint& dep : dep_set) {
            logger.info << "processing : " << dummy_ind << std::endl;
            dep_deriv[dep].debug(logger.info);
            this->process_single_deriv(dummy_ind, local_deriv, dep_deriv[dep]);
            dep_deriv[dep].debug(logger.info);
          }
        }
      }
    }
  }
};

} // namespace ReverseAD

#endif // ENABLE_REVERSEAD_MPI

#endif // REVERSEAD_BASE_MPI_REVERSE_ADJOINT_H_
