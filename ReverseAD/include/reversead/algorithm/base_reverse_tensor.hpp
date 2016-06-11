#ifndef REVERSEAD_BASE_REVERSE_TENSOR_H_
#define REVERSEAD_BASE_REVERSE_TENSOR_H_

#include "reversead/common/reversead_type.hpp"
#include "reversead/algorithm/base_reverse_mode.hpp"
#include "reversead/algorithm/tensor_deriv.hpp"
#include "reversead/algorithm/tensor_derivative_info.hpp"
#include "reversead/algorithm/tensor_index.hpp"
#include "reversead/util/temp_memory_allocator.hpp"

namespace ReverseAD {

template <typename Base>
class BaseReverseTensor : public BaseReverseMode<Base> {
 public:
  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::indep_index_map;
  using BaseReverseMode<Base>::dep_index_map;

  BaseReverseTensor(const std::shared_ptr<TrivialTrace<Base>>& trace, size_t order);

  void clear() override final;

 protected:
  std::shared_ptr<DerivativeTensor<size_t, Base>> get_tensor() const override;

  void init_dep_deriv(locint dep) override final;
  void process_sac(const DerivativeInfo<locint, Base>& info) override final;

  void accumulate_deriv(TensorDeriv<locint, Base>& global_deriv);

 private:
  void fill_in_ginfo(const DerivativeInfo<locint, Base>& dinfo);
  
  size_t order;
  TensorDerivativeInfo<locint, Base> ginfo;
  std::map<locint, TensorDeriv<locint, Base>> dep_deriv;

  // helper coefficient series for derivatives of asin/acos/atan/
  double c_atan[REVERSEAD_MAX_TENSOR_ORDER + 1]
      [REVERSEAD_MAX_TENSOR_ORDER + 1][REVERSEAD_MAX_TENSOR_ORDER + 1];
  double c_asin[REVERSEAD_MAX_TENSOR_ORDER + 1]
      [REVERSEAD_MAX_TENSOR_ORDER + 1][REVERSEAD_MAX_TENSOR_ORDER + 1];
  void special_derivative_coeff();

  // make these private for some efficiency
  mutable TempMemoryAllocator temp_memory;
  size_t r_count;
  size_t x_count;
  size_t y_count;
  double w;
  mutable size_t size;
  mutable locint** tind; 
  mutable double* values;
  mutable char* temp;
  size_t case_code;
  void assign_pointers(size_t s_order) const;
  void binary_generator(size_t s_order, TensorDeriv<locint, Base>&);
  void unary_generator(size_t s_order, TensorDeriv<locint, Base>&);
};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_TENSOR_H_
