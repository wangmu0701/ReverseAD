#include "reversead/common/reversead_type.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/trace/trivial_trace.hpp"

namespace ReverseAD {
  
  void* global_trace;
  bool is_tracing = false;
  locint curr_loc = 0;
  locint curr_ind_loc = 0;
  locint curr_dummy_loc = 0;
  extern Log log;

  int rank = 0;

  locint get_next_loc() {
    locint ret = curr_loc++;
    ret = (ret << RANK_SHIFT) | (rank & RANK_BASE); 
    return ret;
  }

  locint get_next_ind_loc() {
    locint ret = curr_ind_loc++;
    ret = (ret << RANK_SHIFT) | (rank & RANK_BASE);
    std::cout << "ind_loc = " << curr_ind_loc << std::endl;
    return ret;
  }

  locint get_next_dummy_loc() {
    locint ret = curr_dummy_loc--;
    ret = (ret << RANK_SHIFT) | (rank & RANK_BASE);
    return ret;
  }
  
  // turn on some internal logging
  void logging_on() {
    log.reset_info(&(std::cout));   
  }

} // namespace ReverseAD
