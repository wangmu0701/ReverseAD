#ifndef REVERSEAD_BASE_REVERSE_GENERATOR_H_
#define REVERSEAD_BASE_REVERSE_GENERATOR_H_

#include "reversead/common/reversead_type.hpp"
#include "reversead/algorithm/base_reverse_generic.hpp"

#define REVERSEAD_MAX_GENERATOR_ORDER 3

namespace ReverseAD {

template <typename LocType, typename Base>
class GeneratorInfo {
 public:
  GeneratorInfo() {
    clear();
  }
  void clear() {
    r = NULL_LOC; x = NULL_LOC; y = NULL_LOC;
    dx = 0.0; dy = 0.0;
    pxx = 0.0; pxy = 0.0; pyy = 0.0;
    pxxx = 0.0; pxxy = 0.0; pxyy = 0.0; pyyy = 0.0;
    pxxxx = 0.0; pxxxy = 0.0; pxxyy = 0.0; pxyyy = 0.0; pyyyy = 0.0;
  }
  opbyte opcode;
  LocType r, x, y;
  Base dx, dy;
  Base pxx, pxy, pyy;
  Base pxxx, pxxy, pxyy, pyyy;
  Base pxxxx, pxxxy, pxxyy, pxyyy, pyyyy;
};

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
