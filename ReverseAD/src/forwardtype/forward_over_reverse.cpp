#include <memory>

#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/base_function_replay.hpp"
#include "reversead/algorithm/base_reverse_adjoint.hpp"
#include "reversead/algorithm/base_reverse_hessian.hpp"
#include "reversead/algorithm/base_reverse_third.hpp"
#include "reversead/algorithm/base_reverse_generic.hpp"
#include "reversead/algorithm/derivative_tensor.hpp"
#include "reversead/forwardtype/single_forward.hpp"

namespace ReverseAD {

std::shared_ptr<TrivialTrace<SingleForward>> get_forward_trace(
    std::shared_ptr<TrivialTrace<double>> trace,
    size_t ind_size,
    double* ind_init_value,
    double* adjoint_init_value) {
  void* raw_memory = ::operator new[](ind_size * sizeof(SingleForward));
  SingleForward* x = static_cast<SingleForward*>(raw_memory);
  for(size_t i = 0; i < ind_size; i++) {
    new(&x[i]) SingleForward(ind_init_value[i], adjoint_init_value[i]);
  }
  std::shared_ptr<TrivialTrace<SingleForward>> new_trace =
    BaseFunctionReplay::replay_forward<double, SingleForward>(
        trace, x, ind_size);
  ::operator delete[](raw_memory);
  return new_trace;
}

void forward_over_reverse(std::shared_ptr<TrivialTrace<double>> trace,
                          size_t ind_size,
                          size_t dep_size,
                          double* ind_init_value,
                          double* adjoint_init_value,
                          double** hessian_vector) {
  std::shared_ptr<TrivialTrace<SingleForward>> new_trace =
      get_forward_trace(trace, ind_size, ind_init_value, adjoint_init_value);

  BaseReverseAdjoint<SingleForward> adjoint(new_trace);
  std::shared_ptr<DerivativeTensor<size_t, SingleForward>> tensor = adjoint.compute(ind_size, dep_size);

  if (tensor->get_dep_size() != dep_size) {
    // TODO(muwang) some error here.
  }

  size_t size;
  size_t** tind;
  SingleForward* values;
  for (size_t i = 0; i < dep_size; i++) {
    tensor->get_internal_coordinate_list(i, 1, &size, &tind, &values);
    //std::cout << "size = " << size << std::endl;
    if (size != ind_size) {
      // some error here.
    }
    for (size_t j = 0; j < ind_size; j++) {
      hessian_vector[i][j] = 0.0;
    }
    for (size_t j = 0; j < size; j++) {
      //std::cout << "tind[j][0] = " << tind[j][0] << std::endl;
      hessian_vector[i][tind[j][0]] = values[j].getDer();
    }
  } 
}

void forward_over_second(std::shared_ptr<TrivialTrace<double>> trace,
                         size_t ind_size,
                         size_t dep_size,
                         double* ind_init_value,
                         double* adjoint_init_value,
                         double*** third_vector) {
  std::shared_ptr<TrivialTrace<SingleForward>> new_trace =
      get_forward_trace(trace, ind_size, ind_init_value, adjoint_init_value);

  BaseReverseHessian<SingleForward> hessian(new_trace);
  std::shared_ptr<DerivativeTensor<size_t, SingleForward>> tensor =
      hessian.compute(ind_size, dep_size);

  if (tensor->get_dep_size() != dep_size) {
    // TODO(muwang) some error here.
  }
  size_t size;
  size_t** tind;
  SingleForward* values;
  for (size_t i=0; i<dep_size; i++) {
    tensor->get_internal_coordinate_list(i, 2, &size, &tind, &values);
    //std::cout << "size = " << size << std::endl;
    for (size_t j = 0; j < ind_size; j++) {
      for(size_t k = 0; k < ind_size; k++) {
        third_vector[i][j][k] = 0.0;
      }
    }
    for (size_t j = 0; j < size; j++) {
      //std::cout << "tind[j][0] = " << tind[j][0] << std::endl;
      //std::cout << "tind[j][1] = " << tind[j][1] << std::endl; 
      third_vector[i][tind[j][0]][tind[j][1]] = values[j].getDer();
    }
  } 
}

void forward_over_third(std::shared_ptr<TrivialTrace<double>> trace,
                        size_t ind_size,
                        size_t dep_size,
                        double* ind_init_value,
                        double* adjoint_init_value,
                        double**** fourth_vector) {
  std::shared_ptr<TrivialTrace<SingleForward>> new_trace =
      get_forward_trace(trace, ind_size, ind_init_value, adjoint_init_value);

  BaseReverseThird<SingleForward> third(new_trace);
  std::shared_ptr<DerivativeTensor<size_t, SingleForward>> tensor =
      third.compute(ind_size, dep_size);

  if (tensor->get_dep_size() != dep_size) {
    // TODO(muwang) some error here.
  }
  size_t size;
  size_t** tind;
  SingleForward* values;
  for (size_t i=0; i<dep_size; i++) {
    tensor->get_internal_coordinate_list(i, 3, &size, &tind, &values);
    //std::cout << "size = " << size << std::endl;
    if (size != ind_size) {
      // some error here.
    }
    for (size_t j = 0; j < ind_size; j++) {
      for(size_t k = 0; k < ind_size; k++) {
        for (size_t l = 0; l<ind_size; l++) {
          fourth_vector[i][j][k][l] = 0.0;
        }
      }
    }
    for (size_t j = 0; j < size; j++) {
      //std::cout << "tind[j][0] = " << tind[j][0] << std::endl;
      //std::cout << "tind[j][1] = " << tind[j][1] << std::endl; 
      //std::cout << "tind[j][2] = " << tind[j][2] << std::endl; 
      fourth_vector[i][tind[j][0]][tind[j][1]][tind[j][2]] = values[j].getDer();
    }
  } 
}

std::shared_ptr<DerivativeTensor<size_t, double>> strip_derivative(
    const std::shared_ptr<DerivativeTensor<size_t, SingleForward>> tensor,
    size_t t_order,
    size_t ind_size,
    size_t dep_size) {
  std::shared_ptr<DerivativeTensor<size_t, double>> ret =
      std::make_shared<DerivativeTensor<size_t, double>>(dep_size, ind_size, t_order);
  size_t size;
  size_t** tind;
  SingleForward* value;
  for (size_t i = 0; i < dep_size; i++) {
    ret->put_dep_value(i, tensor->get_dep_value(i).getDer());
    for (size_t j = 1; j <= t_order; j++) {
      tensor->get_internal_coordinate_list(i, j, &size, &tind, &value);
      ret->init_single_tensor(i, j, size);
      for (size_t k = 0; k < size; k++) {
        ret->put_value(i, j, k, tind[k], value[k].getDer());
      }
    }
  }
  return ret;
}

std::shared_ptr<DerivativeTensor<size_t, double>> directional_reverse(
    std::shared_ptr<TrivialTrace<double>> trace,
    size_t t_order,
    size_t ind_size,
    size_t dep_size,
    double* ind_init_value,
    double* adjoint_init_value) {
  std::shared_ptr<TrivialTrace<SingleForward>> new_trace =
      get_forward_trace(trace, ind_size, ind_init_value, adjoint_init_value);

  std::shared_ptr<DerivativeTensor<size_t, SingleForward>> tensor;
  if (t_order == 1) {
    BaseReverseAdjoint<SingleForward> adjoint(new_trace);
    tensor = adjoint.compute(ind_size, dep_size);
  } else if (t_order == 2) {
    BaseReverseHessian<SingleForward> hessian(new_trace);
    tensor = hessian.compute(ind_size, dep_size);
  } else if (t_order == 3) {
    BaseReverseAdjoint<SingleForward> third(new_trace);
    tensor = third.compute(ind_size, dep_size);
  } else {
    BaseReverseGeneric<SingleForward> generic(new_trace, t_order);
    tensor = generic.compute(ind_size, dep_size);
  }
  return strip_derivative(tensor, t_order, ind_size, dep_size);
}

} // namespace ReverseAD
