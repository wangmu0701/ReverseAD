#ifndef REVERSEAD_BASE_REVERSE_GENERATOR_H_
#define REVERSEAD_BASE_REVERSE_GENERATOR_H_

#include "reversead/common/reversead_type.hpp"
#include "reversead/algorithm/base_reverse_generic.hpp"

#define REVERSEAD_MAX_GENERATOR_ORDER 3

namespace ReverseAD {

template <typename Base>
class BaseReverseGenerator : public BaseReverseGeneric<Base> {
 public:
  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::indep_index_map;
  using BaseReverseMode<Base>::dep_index_map;
  using BaseReverseGeneric<Base>::order;
  using BaseReverseGeneric<Base>::dep_deriv;

  BaseReverseGenerator(const std::shared_ptr<TrivialTrace<Base>>& trace, int order);

 protected:
  void process_sac(const DerivativeInfo<locint, Base>& info) override final;

  void accumulate_deriv(const GeneratorInfo<locint, Base>& info,
                        GenericDeriv<locint, Base>& global_deriv);
 private:
  void fill_in_ginfo(const DerivativeInfo<locint, Base>& dinfo,
                     GeneratorInfo<locint, Base>& ginfo); 
};

} // namespace ReverseAD

#endif // REVERSEAD_BASE_REVERSE_GENERATOR_H_
