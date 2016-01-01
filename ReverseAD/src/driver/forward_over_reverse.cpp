#include <memory>

#include "reversead/trace/trivial_trace.hpp"
#include "reversead/algorithm/base_function_replay.hpp"
#include "reversead/algorithm/base_reverse_adjoint.hpp"
#include "reversead/algorithm/derivative_tensor.hpp"
#include "reversead/forwardtype/single_forward.hpp"

namespace ReverseAD {

void forward_over_reverse(std::shared_ptr<TrivialTrace<double>> trace,
                          int ind_num,
                          int dep_num,
                          double* ind_init_value,
                          double* adjoint_init_value,
                          double** hessian_vector) {
  SingleForward* x = new SingleForward[ind_num];
  for(int i=0; i<ind_num; i++) {
    x[i] = SingleForward(ind_init_value[i], adjoint_init_value[i]);
  }
  std::shared_ptr<TrivialTrace<SingleForward>> new_trace =
    BaseFunctionReplay::replay_forward<double, SingleForward>(
        trace, x, ind_num);
  BaseReverseAdjoint<SingleForward> adjoint(new_trace);
  DerivativeTensor<locint, SingleForward> tensor = adjoint.compute(ind_num, dep_num);

  if (tensor.get_dep_size() != dep_num) {
    // some error here.
  }

  int size;
  locint** tind;
  SingleForward* values;
  for (int i=0; i<dep_num; i++) {
    tensor.get_internal_coordinate_list(i, 1, &size, &tind, &values);
    std::cout << "size = " << size << std::endl;
    if (size != ind_num) {
      // some error here.
    }
    for (int j = 0; j<ind_num; j++) {
      hessian_vector[i][j] = values[j].getDer();
    }
  } 
}

} // namespace ReverseAD
