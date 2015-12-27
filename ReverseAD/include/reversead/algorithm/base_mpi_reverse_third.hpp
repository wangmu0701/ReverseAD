#ifndef REVERSEAD_BASE_MPI_REVERSE_THIRD_H_
#define REVERSEAD_BASE_MPI_REVERSE_THIRD_H_

#include "reversead/common/reversead_config.h"

#ifdef ENABLE_REVERSEAD_MPI

#include "mpi.h"
#include "reversead/algorithm/base_reverse_third.hpp"
#include "reversead/algorithm/base_mpi_reverse_adjoint.hpp"

namespace ReverseAD {

template <typename Base>
class BaseMpiReverseThird : public BaseReverseThird<Base>,
                            public BaseMpiReverseAdjoint<Base> {
 public:
  typedef typename BaseReverseMode<Base>::type_adjoint type_adjoint;
  typedef typename BaseReverseMode<Base>::type_hessian type_hessian;
  typedef typename BaseReverseMode<Base>::type_third type_third;
  typedef typename BaseReverseMode<Base>::SingleDeriv SingleDeriv;

  using BaseReverseMode<Base>::dep_deriv;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::trace;

  using BaseMpiReverseAdjoint<Base>::forward_global_phase;

  BaseMpiReverseThird(const std::shared_ptr<TrivialTrace<Base>>& trace)
    : BaseReverseAdjoint<Base>(trace),
      BaseReverseThird<Base>(),
      BaseMpiReverseAdjoint<Base>() {
  }

  void compute_mpi() {
    // here we should pass the correct num for ind and dep
    double time = get_timing();
    this->reverse_local_computation(trace->get_num_ind(), trace->get_num_dep());
    time = get_timing();
    logger.warning << "reverse  local third order timing : " << time << std::endl;

    for (auto& kv : dep_deriv) {
      logger.info << "Dep : " << kv.first << std::endl;
      kv.second.adjoint_vals->debug(logger.info);
      kv.second.hessian_vals->debug(logger.info);
      kv.second.third_vals->debug(logger.info);
    }

    forward_global_phase();
    time = get_timing();
    logger.warning << "forward global third order timing : " << time << std::endl;
    for (auto& kv : dep_deriv) {
      logger.info << "Dep : " << kv.first << std::endl;
      kv.second.adjoint_vals->debug(logger.info);
      kv.second.hessian_vals->debug(logger.info);
      kv.second.third_vals->debug(logger.info);
    }
  }
};

} // namespace ReverseAD

#endif // ENABLE_REVERSEAD_MPI

#endif // REVERSEAD_BASE_MPI_REVERSE_THIRD_H_
