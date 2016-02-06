#include <iostream>

#include "reversead/common/runtime_env.hpp"

namespace ReverseAD {

std::ostream& operator << (std::ostream& os, const RuntimeEnv& runtime_env) {
  os << " rank = " << runtime_env.rank 
     << " curr_loc = " << runtime_env.curr_loc
     << " curr_ind_loc = " << runtime_env.curr_ind_loc
     << " curr_dummy_loc = " << runtime_env.curr_dummy_loc << std::endl;
  return os;
}

} // namespace ReverseAD

