#ifndef REVERSEAD_FORWARD_OVER_REVERSE_H_
#define REVERSEAD_FORWARD_OVER_REVERSE_H_

#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/derivative_tensor.hpp"

namespace ReverseAD {

void forward_over_reverse(std::shared_ptr<TrivialTrace<double>> trace,
                          int ind_num,
                          int dep_num,
                          double* ind_init_value,
                          double* adjoint_init_value,
                          double** hessian_vector);

void forward_over_second(std::shared_ptr<TrivialTrace<double>> trace,
                         int ind_num,
                         int dep_num,
                         double* ind_init_value,
                         double* adjoint_init_value,
                         double*** third_vector);

void forward_over_third(std::shared_ptr<TrivialTrace<double>> trace,
                         int ind_num,
                         int dep_num,
                         double* ind_init_value,
                         double* adjoint_init_value,
                         double**** fourth_vector);

DerivativeTensor<locint, double> directional_reverse(
    std::shared_ptr<TrivialTrace<double>> trace,
    int t_order,
    int ind_num,
    int dep_num,
    double* ind_init_value,
    double* adjoint_init_value);
 
/*
void forward_over_generic(std::shared_ptr<TrivialTrace<double>> trace,
                          int ind_num,
                          int dep_num,
                          double* ind_init_value,
                          double* adjoint_init_value,
                          int t_order,
                          int* size;
                          locint*** tind,
                          double** values);
*/
} // namespace ReverseAD

#endif // REVERSEAD_FORWARD_OVER_REVERSE_H_
