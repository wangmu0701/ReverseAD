#include "reversead/algorithm/base_reverse_hessian.hpp"
#include "reversead/forwardtype/single_forward.hpp"

template class ReverseAD::BaseReverseHessian<double>;
template class ReverseAD::BaseReverseHessian<ReverseAD::SingleForward>;
