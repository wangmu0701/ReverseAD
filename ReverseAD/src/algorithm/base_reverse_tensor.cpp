#include "reversead/algorithm/base_reverse_tensor.hpp"
#include "reversead/forwardtype/single_forward.hpp"

template class ReverseAD::BaseReverseTensor<double>;
template class ReverseAD::BaseReverseTensor<ReverseAD::SingleForward>;
