#ifndef BASE_FUNCTION_REPLAY_H_
#define BASE_FUNCTION_REPLAY_H_

#include <cmath>
#include <map>
#include <memory>

#include "reversead/common/reversead_base.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/trace/abstract_trace.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/tape/abstract_tape.hpp"
#include "reversead/tape/trivial_tape.hpp"

using std::map;

namespace ReverseAD {


// The old trace is not deleted.
class BaseFunctionReplay {
 public:

  // the same trace will be returned.
  template <typename Base>
  static TrivialTrace<Base>* replay_dep(TrivialTrace<Base>* trace,
                                    Base* dep_val, int dep_num) {
    return replay<Base, Base>(trace,
                  dep_val, dep_num,
                  (Base*)nullptr, trace->get_num_ind(),
                  (Base*)nullptr, trace->get_num_param(),
                  true, // reset_dep,
                  false, // reset_ind,
                  false); // reset_param
  }
  template <typename Base>
  static TrivialTrace<Base>* replay_ind(TrivialTrace<Base>* trace,
                                    Base* ind_val, int ind_num) {
    return replay<Base, Base>(trace,
                  (Base*)nullptr, trace->get_num_dep(),
                  ind_val, ind_num,
                  (Base*)nullptr, trace->get_num_param(),
                  false, // reset_dep,
                  true, // reset_ind,
                  false); // reset_param
  }
  template <typename Base>
  static TrivialTrace<Base>* replay_ind(TrivialTrace<Base>* trace,
                                    Base* dep_val, int dep_num,
                                    Base* ind_val, int ind_num) {
    return replay<Base, Base>(trace,
                  dep_val, dep_num,
                  ind_val, ind_num,
                  (Base*)nullptr, trace->get_num_param(),
                  true, // reset_dep,
                  true, // reset_ind,
                  false); // reset_param
  }

  template <typename Base>
  static TrivialTrace<Base>* replay_param(TrivialTrace<Base>* trace,
                                          Base* param_val, int param_num) {
    return replay<Base, Base>(trace,
                  (Base*)nullptr, trace->get_num_dep(),
                  (Base*)nullptr, trace->get_num_ind(),
                  param_val, param_num,
                  false, // reset_dep,
                  false, // reset_ind,
                  true); // reset_param
  }

  template <typename Base>
  static TrivialTrace<Base>* replay(TrivialTrace<Base>* trace,
                                    Base* ind_val, int ind_num,
                                    Base* param_val, int param_num) {
    return replay<Base, Base>(trace,
                  (Base*)nullptr, trace->get_num_dep(),
                  ind_val, ind_num,
                  param_val, param_num,
                  false, // reset_dep,
                  true, // reset_ind,
                  true); // reset_param
  }

  template <typename Base>
  static TrivialTrace<Base>* replay(TrivialTrace<Base>* trace,
                                    Base* dep_val, int dep_num,
                                    Base* ind_val, int ind_num,
                                    Base* param_val, int param_num) {
    return replay<Base, Base>(trace,
                  dep_val, dep_num,
                  ind_val, ind_num,
                  param_val, param_num,
                  true, // reset_dep,
                  true, // reset_ind,
                  true); // reset_param
  }

 private:
  template <typename OldBase, typename NewBase>
  static TrivialTrace<NewBase>* replay(TrivialTrace<OldBase>* trace,
                                    NewBase* dep_val, int dep_num,
                                    NewBase* ind_val, int ind_num,
                                    NewBase* param_val, int param_num,
                                    bool reset_dep,
                                    bool reset_ind,
                                    bool reset_param) {
    map<locint, NewBase> val_map;
    trace->init_forward();
    opbyte op = trace->get_next_op_f();
    int ind_count = 0;
    int dep_count = 0;
    int param_count = 0;
    if (reset_param && param_num != trace->get_num_param()) {
      logger.fatal << "Number of parameter (" << param_num << ") does NOT"
                << " match the record on the trace (" << trace->get_num_param()
                << ")." << std::endl;
    }
    if (reset_ind && ind_num != trace->get_num_ind()) {
      logger.fatal << "Number of independents (" << ind_num << ") does NOT"
                << " match the record on the trace (" << trace->get_num_ind()
                << ")." << std::endl;
    }
    if (reset_dep && dep_num != trace->get_num_dep()) {
      logger.fatal << "Number of dependents (" << dep_num << ") does NOT"
                << " match the record on the trace (" << trace->get_num_dep()
                << ")." << std::endl;
    }
    std::shared_ptr<TrivialTape<NewBase>> val_tape =
      std::make_shared<TrivialTape<NewBase>>();
    std::shared_ptr<TrivialTape<NewBase>> param_tape =
      std::make_shared<TrivialTape<NewBase>>();

    locint res;
    locint arg1;
    locint arg2;
    OldBase val, val1, val2;
    double coval;
    while (op != end_of_tape) {
      switch (op) {
        case start_of_tape:
          break;
        case assign_ind:
          if (ind_count >= ind_num) {
            logger.warning << "more independents found on tape than : " << ind_num << std::endl;
            return nullptr;
          }
          res = trace->get_next_loc_f();
          val = trace->get_next_val_f();
          if (reset_ind) {
            // reset: value from function call
            val_map[res] = ind_val[ind_count++];
          } else {
            // no reset: value from trace
            val_map[res] = val;
          }
          val_tape->put(val_map[res]);
          break;
        case assign_dep:
          if (dep_count >= dep_num) {
            logger.warning << "more dependents found on tape than : " << ind_num << std::endl;
            return nullptr;
          }
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          val = val_map[res];
          if (reset_dep) {
            dep_val[dep_count++] = val;
          }
          val_tape->put(val); 
          break;
        case assign_param:
          res = trace->get_next_loc_f();
          val = trace->get_next_param_f();
          if (reset_param) {
            // reset: value from function call
            val_map[res] = param_val[param_count++];
            param_tape->put(val_map[res]);
          } else {
            // no reset: value from trace
            val_map[res] = val;
          }
          break;
        case assign_d:
          res = trace->get_next_loc_f();
          val_map[res] = trace->get_next_coval_f();
          break;
        case assign_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          val_map[res] = val_map[arg1];
          break;
        case comp_eq:
          arg1 = trace->get_next_loc_f();
          arg2 = trace->get_next_loc_f();
          coval = trace->get_next_coval_f();
          {
            bool flag = (val_map[arg1] == val_map[arg2]);
            if ((!flag && coval == 1.0) || (flag && coval != 1.0)) {
              logger.BranchInconsistent<NewBase>(val_map[arg1], "==", val_map[arg2]);
            }
          }
          break;
        case comp_lt:
          arg1 = trace->get_next_loc_f();
          arg2 = trace->get_next_loc_f();
          coval = trace->get_next_coval_f();
          {
            bool flag = (val_map[arg1] < val_map[arg2]);
            if ((!flag && coval == 1.0) || (flag && coval != 1.0)) {
              logger.BranchInconsistent<NewBase>(val_map[arg1], "<", val_map[arg2]);
            }
          }
          break;
        case eq_plus_a:
        case plus_a_a:
          arg1 = trace->get_next_loc_f();
          arg2 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          val_map[res] = val_map[arg1] + val_map[arg2];
          break;
        case eq_plus_d:
        case plus_d_a:
          arg1 = trace->get_next_loc_f();
          coval = trace->get_next_coval_f();
          res = trace->get_next_loc_f();
          val_map[res] = val_map[arg1] + coval;
          break;
        case eq_minus_a:
        case minus_a_a:
          arg1 = trace->get_next_loc_f();
          arg2 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          val_map[res] = val_map[arg1] - val_map[arg2];
          break;
        case minus_d_a:
          arg1 = trace->get_next_loc_f();
          coval = trace->get_next_coval_f();
          res = trace->get_next_loc_f();
          val_map[res] = coval - val_map[arg1];
          break;
        case eq_mult_a:
        case mult_a_a:
          arg1 = trace->get_next_loc_f();
          arg2 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          trace->get_next_val_f();
          val1 = val_map[arg1];
          val2 = val_map[arg2];
          val_map[res] = val1 * val2;
          val_tape->put(val1);
          val_tape->put(val2);
          break;
        case eq_mult_d:
        case mult_d_a:
          arg1 = trace->get_next_loc_f();
          coval = trace->get_next_coval_f();
          res = trace->get_next_loc_f();
          val1 = val_map[arg1];
          val_map[res] = val1 * coval;
          break;
        case eq_div_a:
        case div_a_a:
          arg1 = trace->get_next_loc_f();
          arg2 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          trace->get_next_val_f();
          val1 = val_map[arg1];
          val2 = val_map[arg2];
          val_map[res] = val1 / val2;
          val_tape->put(val1);
          val_tape->put(val2);
          break;
        case div_d_a:
          arg1 = trace->get_next_loc_f();
          trace->get_next_val_f();
          coval = trace->get_next_coval_f();
          res = trace->get_next_loc_f();
          val1 = val_map[arg1];
          val_map[res] = coval / val1;
          val_tape->put(val1);
          break;
        case sin_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          val1 = val_map[arg1];
          val_map[res] = sin(val1);
          val_tape->put(val1);
          break;
        case cos_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          val1 = val_map[arg1];
          val_map[res] = cos(val1);
          val_tape->put(val1);
          break;
        case tan_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          val1 = val_map[arg1];
          val_map[res] = tan(val1);
          val_tape->put(val1);
          break;
        case asin_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          val1 = val_map[arg1];
          if (val1 < -1 || val1 > 1) {
            logger.ParameterOutOfBound<NewBase>(val, "asin");
          }
          val_map[res] = asin(val1);
          val_tape->put(val1);
          break;
        case acos_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          val1 = val_map[arg1];
          if (val1 < -1 || val1 > 1) {
            logger.ParameterOutOfBound<NewBase>(val, "acos");
          }
          val_map[res] = acos(val1);
          val_tape->put(val1);
          break;
        case atan_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          val1 = val_map[arg1];
          val_map[res] = atan(val1);
          val_tape->put(val1);
          break;
        case sqrt_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f(); 
          val1 = val_map[arg1]; 
          val_map[res] = sqrt(val1);
          val_tape->put(val1);
          break;
        case exp_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f(); 
          val1 = val_map[arg1]; 
          val_map[res] = exp(val1);
          val_tape->put(val1);
          break;
        case log_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f(); 
          val1 = val_map[arg1]; 
          if (val1 <= 0) {
            logger.ParameterOutOfBound<NewBase>(val, "logger");
          }
          val_map[res] = log(val1);
          val_tape->put(val1);
          break;
        case pow_a_a:
          arg1 = trace->get_next_loc_f();
          arg2 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          trace->get_next_val_f();
          val1 = val_map[arg1];
          val2 = val_map[arg2];
          val_map[res] = pow(val1, val2);
          val_tape->put(val1);
          val_tape->put(val2);
          break;
        case pow_a_d:
          arg1 = trace->get_next_loc_f();
          trace->get_next_val_f();
          coval = trace->get_next_coval_f();
          res = trace->get_next_loc_f();
          val1 = val_map[arg1];
          val_map[res] = pow(val1, coval);
          val_tape->put(val1);
          break;
        case pow_d_a:
          arg1 = trace->get_next_loc_f();
          trace->get_next_val_f();
          coval = trace->get_next_coval_f();
          res = trace->get_next_loc_f();
          val1 = val_map[arg1];
          val_map[res] = pow(coval, val1);
          val_tape->put(val1);
          break;
        case rmpi_send:
        case rmpi_recv:
          break;
        default:
          logger.warning << "Unrecongized opcode : " << (int)op << std::endl; 
      }
      op = trace->get_next_op_f();
    }
    TrivialTrace<NewBase>* ret = nullptr;
    if (reset_param) {
      // a new set of param values
      ret = new TrivialTrace<NewBase>(trace, val_tape, param_tape);
    } else if (reset_ind) {
      // a new set of ind values
      ret = new TrivialTrace<NewBase>(trace, val_tape);
    } else {
      // just compute values of deps
      ret = trace;
    }
    return ret;
  }

};

} // namespace ReverseAD

#endif // BASE_FUNCTION_REPLAY_H_
