#include "reversead/algorithm/base_reverse_adjoint.hpp"
#include "reversead/forwardtype/single_forward.hpp"

template class ReverseAD::BaseReverseAdjoint<double>;
template class ReverseAD::BaseReverseAdjoint<ReverseAD::SingleForward>;
