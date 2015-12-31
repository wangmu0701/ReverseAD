#ifndef REVERSEAD_FORWARD_OVER_REVERSE_H_
#define REVERSEAD_FORWARD_OVER_REVERSE_H_

#include <memory>

#include "reversead/trace/trivial_trace.hpp"

namespace ReverseAD {

void forward_over_reverse(std::shared_ptr<TrivialTrace<double>> trace,
                          int ind_num,
                          int dep_num,
                          double* ind_init_value,
                          double* adjoint_init_value,
                          double** hessian_vector);

} // namespace ReverseAD

#endif // REVERSEAD_FORWARD_OVER_REVERSE_H_
