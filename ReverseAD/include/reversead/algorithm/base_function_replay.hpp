#ifndef BASE_FUNCTION_REPLAY_H_
#define BASE_FUNCTION_REPLAY_H_

#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/trace/trivial_trace.hpp"

namespace ReverseAD {

class BaseFunctionReplay {
 public:

  template <typename Base>
  static std::shared_ptr<TrivialTrace<Base>> replay_dep(
      const std::shared_ptr<TrivialTrace<Base>>& trace,
      Base* dep_val, int dep_num);

  template <typename OldBase, typename NewBase>
  static std::shared_ptr<TrivialTrace<NewBase>> replay_forward(
      const std::shared_ptr<TrivialTrace<OldBase>>& trace,
      const NewBase* const ind_val, int ind_num);

  template <typename Base>
  static std::shared_ptr<TrivialTrace<Base>> replay_ind(
      const std::shared_ptr<TrivialTrace<Base>>& trace,
      const Base* const ind_val, int ind_num);

  template <typename Base>
  static std::shared_ptr<TrivialTrace<Base>> replay_ind(
      const std::shared_ptr<TrivialTrace<Base>>& trace,
      Base* dep_val, int dep_num,
      const Base* const ind_val, int ind_num);

  template <typename Base>
  static std::shared_ptr<TrivialTrace<Base>> replay_param(
      const std::shared_ptr<TrivialTrace<Base>>& trace,
      const Base* const param_val, int param_num);
  template <typename Base>
  static std::shared_ptr<TrivialTrace<Base>> replay(
      const std::shared_ptr<TrivialTrace<Base>>& trace,
      const Base* const ind_val, int ind_num,
      const Base* const param_val, int param_num);

  template <typename Base>
  static std::shared_ptr<TrivialTrace<Base>> replay(
      const std::shared_ptr<TrivialTrace<Base>>& trace,
      Base* dep_val, int dep_num,
      const Base* const ind_val, int ind_num,
      const Base* const param_val, int param_num);
 private:
  template <typename OldBase, typename NewBase>
  static std::shared_ptr<TrivialTrace<NewBase>> replay(
      const std::shared_ptr<TrivialTrace<OldBase>>& trace,
      NewBase* dep_val, int dep_num,
      const NewBase* const ind_val, int ind_num,
      const NewBase* const param_val, int param_num,
      bool reset_dep, bool reset_ind, bool reset_param);

};

} // namespace ReverseAD

#endif // BASE_FUNCTION_REPLAY_H_
