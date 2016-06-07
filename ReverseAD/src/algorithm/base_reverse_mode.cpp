#include "reversead/algorithm/base_reverse_mode.hpp"
#include "reversead/forwardtype/single_forward.hpp"

template class ReverseAD::BaseReverseMode<double>;
template class ReverseAD::BaseReverseMode<ReverseAD::SingleForward>;
