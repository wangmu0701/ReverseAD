#include "reversead/algorithm/base_reverse_generic.hpp"
#include "reversead/forwardtype/single_forward.hpp"

template class ReverseAD::BaseReverseGeneric<double>;
template class ReverseAD::BaseReverseGeneric<ReverseAD::SingleForward>;
