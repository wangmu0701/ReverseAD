#ifndef BASE_FUNCTION_REPLAY_H_
#define BASE_FUNCTION_REPLAY_H_

#include <map>

#include "reversead/reversead_base.hpp"
#include "reversead/opcodes.hpp"
#include "reversead/trace/abstract_trace.hpp"
#include "reversead/tape/abstract_tape.hpp"

using std::map;

namespace ReverseAD {

template <typename Base>
class BaseFunctionReplay {
 public:
  BaseFunctionReplay(AbstractTrace* trace) {
    this->trace = trace;
  }

  Base* replay(Base* ind_val, int ind_num, int dep_num) {
    Base* dep_val = new Base[dep_num];
    map<locint, Base> val_map;
    trace->init_forward();
    opbyte op = trace->get_next_op_f();
    int ind_count = 0;
    int dep_count = 0;

    locint res;
    locint arg1;
    locint arg2;
    double coval;
    while (op != end_of_tape) {
      switch (op) {
        case start_of_tape:
          break;
        case assign_ind:
          if (ind_count >= ind_num) {
            std::cerr << "more independents found on tape than : " << ind_num << std::endl;
            return NULL;
          }
          res = get_next_res();
          coval = trace->get_next_val_f();
          val_map[res] = ind_val[ind_count++];
          break;
        case assign_dep:
          if (dep_count >= dep_num) {
            std::cerr << "more dependents found on tape than : " << ind_num << std::endl;
            return NULL;
          }
          res = get_next_res();
          coval = trace->get_next_val_f();
          dep_val[dep_count++] = val_map[res];
          break;
        case assign_d:
          res = get_next_res();
          coval = trace->get_next_val_f();
          val_map[res] = coval;
          break;
        case assign_a:
          arg1 = get_next_arg();
          res = get_next_res();
          val_map[res] = val_map[arg1];
          break;
        case plus_a_a:
          arg1 = get_next_arg();
          arg2 = get_next_arg();
          res = get_next_res();
          val_map[res] = val_map[arg1] + val_map[arg2];
          break;
        case plus_d_a:
          arg1 = get_next_arg();
          coval = trace->get_next_val_f();
          res = get_next_res();
          val_map[res] = val_map[arg1] + coval;
          break;
        case minus_a_a:
          arg1 = get_next_arg();
          arg2 = get_next_arg();
          res = get_next_res();
          val_map[res] = val_map[arg1] - val_map[arg2];
          break;
        case minus_a_d:
          arg1 = get_next_arg();
          coval = trace->get_next_val_f();
          res = get_next_res();
          val_map[res] = val_map[arg1] - coval;
          break;
        case minus_d_a:
          arg1 = get_next_arg();
          coval = trace->get_next_val_f();
          res = get_next_res();
          val_map[res] = coval - val_map[arg1];
          break;
        case mult_a_a:
          arg1 = get_next_arg();
          arg2 = get_next_arg();
          res = get_next_res();
          trace->get_next_val_f();
          trace->get_next_val_f();
          // check (val1 == val_map[arg1])
          // check (val2 == val_map[arg2])
          val_map[res] = val_map[arg1] * val_map[arg2];
          break;
        case mult_d_a:
          arg1 = get_next_arg();
          coval = trace->get_next_val_f();
          res = get_next_res();
          val_map[res] = val_map[arg1] * coval;
          break;
        default:
          std::cerr << "Unrecongized opcode : " << (int)op << std::endl; 
      }
      op = trace->get_next_op_f();
    }
    return dep_val;
  }
  
 private:
  inline locint get_next_res() {return trace->get_next_loc_f();}
  inline locint get_next_arg() {return trace->get_next_loc_f();}

  AbstractTrace* trace;  
};

} // namespace ReverseAD

#endif // BASE_FUNCTION_REPLAY_H_
