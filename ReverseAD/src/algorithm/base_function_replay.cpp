#include "reversead/algorithm/base_function_replay.hpp"
#include "reversead/forwardtype/single_forward.hpp"

template std::shared_ptr<ReverseAD::TrivialTrace<double>>
    ReverseAD::BaseFunctionReplay::replay_dep<double>(
      const std::shared_ptr<ReverseAD::TrivialTrace<double>>& trace,
      double* dep_val, int dep_num);

template std::shared_ptr<ReverseAD::TrivialTrace<ReverseAD::SingleForward>>
    ReverseAD::BaseFunctionReplay::replay_forward<double, ReverseAD::SingleForward>(
      const std::shared_ptr<ReverseAD::TrivialTrace<double>>& trace,
      const ReverseAD::SingleForward* const ind_val, int ind_num);

template std::shared_ptr<ReverseAD::TrivialTrace<double>> 
    ReverseAD::BaseFunctionReplay::replay_ind<double>(
      const std::shared_ptr<ReverseAD::TrivialTrace<double>>& trace,
      const double* const ind_val, int ind_num);

template std::shared_ptr<ReverseAD::TrivialTrace<double>>
    ReverseAD::BaseFunctionReplay::replay_ind<double>(
      const std::shared_ptr<ReverseAD::TrivialTrace<double>>& trace,
      double* dep_val, int dep_num,
      const double* const ind_val, int ind_num);

template std::shared_ptr<ReverseAD::TrivialTrace<double>>
    ReverseAD::BaseFunctionReplay::replay_param(
      const std::shared_ptr<ReverseAD::TrivialTrace<double>>& trace,
      const double* const param_val, int param_num);
template std::shared_ptr<ReverseAD::TrivialTrace<double>>
    ReverseAD::BaseFunctionReplay::replay<double>(
      const std::shared_ptr<ReverseAD::TrivialTrace<double>>& trace,
      const double* const ind_val, int ind_num,
      const double* const param_val, int param_num);

template std::shared_ptr<ReverseAD::TrivialTrace<double>>
    ReverseAD::BaseFunctionReplay::replay<double>(
      const std::shared_ptr<ReverseAD::TrivialTrace<double>>& trace,
      double* dep_val, int dep_num,
      const double* const ind_val, int ind_num,
      const double* const param_val, int param_num);

template std::shared_ptr<ReverseAD::TrivialTrace<double>>
    ReverseAD::BaseFunctionReplay::replay<double, double>(
      const std::shared_ptr<ReverseAD::TrivialTrace<double>>& trace,
      double* dep_val, int dep_num,
      const double* const ind_val, int ind_num,
      const double* const param_val, int param_num,
      bool reset_dep, bool reset_ind, bool reset_param);

template std::shared_ptr<ReverseAD::TrivialTrace<ReverseAD::SingleForward>>
    ReverseAD::BaseFunctionReplay::replay<double, ReverseAD::SingleForward>(
      const std::shared_ptr<ReverseAD::TrivialTrace<double>>& trace,
      ReverseAD::SingleForward* dep_val, int dep_num,
      const ReverseAD::SingleForward* const ind_val, int ind_num,
      const ReverseAD::SingleForward* const param_val, int param_num,
      bool reset_dep, bool reset_ind, bool reset_param);
