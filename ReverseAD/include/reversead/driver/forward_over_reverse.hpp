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
/*
void forward_over_second(std::shared_ptr<TrivialTrace<double>> trace,
                         int ind_num,
                         int dep_num,
                         double* ind_init_value,
                         double* adjoint_init_value,
                         double** third_vector);

void forward_over_third(std::shared_ptr<TrivialTrace<double>> trace,
                         int ind_num,
                         int dep_num,
                         double* ind_init_value,
                         double* adjoint_init_value,
                         double** forth_vector);
*/
/*
void forward_over_generic(std::shared_ptr<TrivialTrace<double>> trace,
                          int ind_num,
                          int dep_num,
                          double* ind_init_value,
                          double* adjoint_init_value,
                          int t_order,
                          locint*** tind,
                          double** values);
*/
} // namespace ReverseAD

#endif // REVERSEAD_FORWARD_OVER_REVERSE_H_
