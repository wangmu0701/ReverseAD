#ifndef REVERSEAD_RUNTIME_ENV_
#define REVERSEAD_RUNTIME_ENV_

#include "reversead/common/reversead_config.h"
#include "reversead/common/reversead_type.hpp"
namespace ReverseAD {

// make RuntimeEnv a POD
class RuntimeEnv {
 public:
  RuntimeEnv() = default;
  RuntimeEnv(const RuntimeEnv&) = default;

  void init() {
    rank = 0;
#ifdef ENABLE_REVERSEAD_MPI
    if (MPI::Is_initialized()) {
      rank = MPI::COMM_WORLD.Get_rank();
    }
#endif
    curr_loc = BASE_LOC;
    curr_dummy_loc = BASE_LOC - 1;
    // independent location begins with 1 so that null_loc can be 0
    curr_ind_loc = 1;
  }

  locint get_next_loc() {
    locint ret = curr_loc++;
#ifdef ENABLE_REVERSEAD_MPI
    ret = (ret << RANK_SHIFT) | (rank & RANK_BASE);
#endif
    return ret; 
  }
  locint get_next_ind_loc() {
    locint ret = curr_ind_loc++;
#ifdef ENABLE_REVERSEAD_MPI
    ret = (ret << RANK_SHIFT) | (rank & RANK_BASE);
#endif
    return ret;

  }
  locint get_next_dummy_loc() {
    locint ret = curr_dummy_loc--;
#ifdef ENABLE_REVERSEAD_MPI
    ret = (ret << RANK_SHIFT) | (rank & RANK_BASE);
#endif
    return ret;
  }

 private:
#ifdef ENABLE_REVERSEAD_MPI
  int rank;
#endif
  locint curr_loc;
  locint curr_ind_loc;
  locint curr_dummy_loc;
};

} // namespace ReverseAD
#endif // REVERSEAD_RUNTIME_ENV_
