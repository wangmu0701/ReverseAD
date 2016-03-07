#ifndef REVERSEAD_TENSOR_DERIV_H_
#define REVERSEAD_TENSOR_DERIV_H_

#include <vector>
#include <map>

#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/symmetry_tensor.hpp"

namespace ReverseAD {

template <typename LocType, typename Base>
class TensorDeriv {
 public:
  TensorDeriv(): _order(0) {initial_template_tensor();};
  TensorDeriv(int order) : _order(order) {initial_template_tensor();};
  void initial_template_tensor() {
  }
  void increase(TensorIndex<LocType>& index, Base v) {
    if (IsZero(v)) {
      return;
    }
//    printf("increase <%d> : [%d, %d, %d] += %.5lf\n",
//           index.size(), index._data[0], index._data[1], index._data[2], v);
    switch (index.size()) {
      case 1:
        tensor1.increase(index.get_array(), v);
        break;
      case 2:
        tensor2.increase(index.get_array(), v);
        break;
      case 3:
        tensor3.increase(index.get_array(), v);
        break;
    }
  }
  void get_and_erase(LocType x, TensorDeriv<LocType, Base>& td) {
    td.tensor0 = this->tensor1.get_and_erase(x);
    td.tensor1 = this->tensor2.get_and_erase(x);
    td.tensor2 = this->tensor3.get_and_erase(x);
  }
  void debug() {
    std::cout << "=====" << std::endl;
    tensor1.dump();
    tensor2.dump();
    tensor3.dump();
  }
  int _order;
  Base tensor0;
  SymmetryTensor<LocType, Base, 1> tensor1;
  SymmetryTensor<LocType, Base, 2> tensor2;
  SymmetryTensor<LocType, Base, 3> tensor3;
};

} // namespace ReverseAD

#endif // REVERSEAD_GENERIC_DERIV_H_
