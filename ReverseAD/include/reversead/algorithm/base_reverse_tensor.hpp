#ifndef REVERSEAD_BASE_REVERSE_TENSOR_H_
#define REVERSEAD_BASE_REVERSE_TENSOR_H_

#include "reversead/common/reversead_type.hpp"
#include "reversead/algorithm/base_reverse_mode.hpp"
#include "reversead/algorithm/tensor_deriv.hpp"
#include "reversead/algorithm/symmetry_tensor.hpp"
#include "reversead/util/temp_memory_allocator.hpp"

#define REVERSEAD_MAX_TENSOR_ORDER 3

namespace ReverseAD {

template <typename Base>
class BaseReverseTensor : public BaseReverseMode<Base> {
 public:
  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::indep_index_map;
  using BaseReverseMode<Base>::dep_index_map;

  BaseReverseTensor(const std::shared_ptr<TrivialTrace<Base>>& trace, int order);

  std::shared_ptr<DerivativeTensor<int, Base>> get_tensor() const override;

  void clear() override final;

 protected:
  void init_dep_deriv(locint dep, int dep_count) override final;
  void process_sac(const DerivativeInfo<locint, Base>& info) override final;

  void accumulate_deriv(TensorDeriv<locint, Base>& global_deriv);

 private:
  void fill_in_ginfo(const DerivativeInfo<locint, Base>& dinfo);
  
  int order;
  GeneratorInfo<locint, Base> ginfo;
  std::map<locint, TensorDeriv<locint, Base>> dep_deriv;

  // make these private for some efficiency
  TempMemoryAllocator temp_memory;
  int r_count;
  int x_count;
  int y_count;
  int size;
  double w;
  locint** tind; 
  double* values;
  char* temp;
  int case_code;
  void assign_pointers(int s_order);
  void binary_generator(int s_order, TensorDeriv<locint, Base>&);
  void unary_generator(int s_order, TensorDeriv<locint, Base>&);
};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_TENSOR_H_
