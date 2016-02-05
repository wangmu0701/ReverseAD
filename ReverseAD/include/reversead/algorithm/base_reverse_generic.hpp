#ifndef REVERSEAD_BASE_REVERSE_GENERIC_H_
#define REVERSEAD_BASE_REVERSE_GENERIC_H_

#include <map>
#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/algorithm/base_reverse_mode.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/reversead_multiset.hpp"
#include "reversead/algorithm/single_derivative.hpp"
#include "reversead/algorithm/generic_deriv.hpp"

#define REVERSEAD_MAX_GENERIC_ORDER 10

namespace ReverseAD {

template <typename Base>
class BaseReverseGeneric : public BaseReverseMode<Base> {
 public:
  typedef SingleDerivative<Base> SingleDeriv;

  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::indep_index_map;
  using BaseReverseMode<Base>::dep_index_map;

  BaseReverseGeneric(const std::shared_ptr<TrivialTrace<Base>>& trace, int order);

  std::shared_ptr<DerivativeTensor<int, Base>> get_tensor() const override;

  void clear() override final;

 protected:
  void init_dep_deriv(locint dep, int dep_count) override final;

  void process_sac(const DerivativeInfo<locint, Base>& info) override final;

  void accumulate_deriv(const DerivativeInfo<locint, Base>& info,
                        const GenericDeriv<locint, Base>& local_deriv,
                        GenericDeriv<locint, Base>& global_deriv);

 private:
  int order;

  // this will shadow the same name in BaseReverseMode because it's a template
  mutable std::map<locint, GenericDeriv<locint, Base> > dep_deriv;

  // some private temps used when accumulating, avoid pointers on stack
  int dx[100];
  int dy[100];
  Base ssw[100];
  int max_level;
  int max_order;
  int cx;
  int cy;
  locint temp_x;
  locint temp_y;
  
  // helper coefficient series for derivatives of asin/atan/asinh/atanh
  double c_atan[REVERSEAD_MAX_GENERIC_ORDER + 1]
      [REVERSEAD_MAX_GENERIC_ORDER + 1][REVERSEAD_MAX_GENERIC_ORDER + 1];
  double c_asin[REVERSEAD_MAX_GENERIC_ORDER + 1]
      [REVERSEAD_MAX_GENERIC_ORDER + 1][REVERSEAD_MAX_GENERIC_ORDER + 1];

  void special_derivative_coeff();

  void clear_private_temps();

  void generate_binary_tuples(int curr_level, int curr_order, Base pw,
    typename GenericDeriv<locint, Base>::enumerator curr_enum);

  void generate_unary_tuples(int curr_level, int curr_order, Base pw,
    typename GenericDeriv<locint, Base>::enumerator curr_enum);

  double binary_sym_coeff();

  double unary_sym_coeff();

  void check_and_increase(const ReverseADMultiSet<locint>& term,
                        const Base& value,
                        GenericDeriv<locint, Base>& local_deriv);

  // fill in a generic derivative table for SACs
  void fill_in_local_deriv(const DerivativeInfo<locint, Base>& info,
                           GenericDeriv<locint, Base>& local_deriv);
};

} // namespace ReverseAD

#endif
