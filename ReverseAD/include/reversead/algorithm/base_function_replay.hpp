#ifndef BASE_FUNCTION_REPLAY_H_
#define BASE_FUNCTION_REPLAY_H_

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

template <typename Base>
class BaseFunctionReplay {
 public:
  BaseFunctionReplay(TrivialTrace<Base>* trace) {
    this->trace = trace;
  }

  TrivialTrace<Base>* replay(Base* dep_val, Base* ind_val, int ind_num, int dep_num) {
    map<locint, Base> val_map;
    trace->init_forward();
    opbyte op = trace->get_next_op_f();
    int ind_count = 0;
    int dep_count = 0;

    std::shared_ptr<TrivialTape<Base>> val_tape =
      std::make_shared<TrivialTape<Base>>();
 
    locint res;
    locint arg1;
    locint arg2;
    Base val, val1, val2;
    double coval;
    while (op != end_of_tape) {
      switch (op) {
        case start_of_tape:
          break;
        case assign_ind:
          if (ind_count >= ind_num) {
            log.warning << "more independents found on tape than : " << ind_num << std::endl;
            return NULL;
          }
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          val_map[res] = ind_val[ind_count++];
          val_tape->put(val_map[res]);
          break;
        case assign_dep:
          if (dep_count >= dep_num) {
            log.warning << "more dependents found on tape than : " << ind_num << std::endl;
            return NULL;
          }
          res = trace->get_next_loc_f();
          trace->get_next_val_f();
          val = val_map[res];
          dep_val[dep_count++] = val;
          val_tape->put(val); 
          break;
        case assign_d:
          res = trace->get_next_loc_f();
          val_map[res] = trace->get_next_val_f();
          break;
        case assign_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          val_map[res] = val_map[arg1];
          break;
        case plus_a_a:
          arg1 = trace->get_next_loc_f();
          arg2 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          val_map[res] = val_map[arg1] + val_map[arg2];
          break;
        case plus_d_a:
          arg1 = trace->get_next_loc_f();
          coval = trace->get_next_coval_f();
          res = trace->get_next_loc_f();
          val_map[res] = val_map[arg1] + coval;
          break;
        case minus_a_a:
          arg1 = trace->get_next_loc_f();
          arg2 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          val_map[res] = val_map[arg1] - val_map[arg2];
          break;
        case minus_a_d:
          arg1 = trace->get_next_loc_f();
          coval = trace->get_next_coval_f();
          res = trace->get_next_loc_f();
          val_map[res] = val_map[arg1] - coval;
          break;
        case minus_d_a:
          arg1 = trace->get_next_loc_f();
          coval = trace->get_next_coval_f();
          res = trace->get_next_loc_f();
          val_map[res] = coval - val_map[arg1];
          break;
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
        case mult_d_a:
          arg1 = trace->get_next_loc_f();
          coval = trace->get_next_coval_f();
          res = trace->get_next_loc_f();
          val1 = val_map[arg1];
          val_map[res] = val1 * coval;
          val_tape->put(val1);
          break;
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
        case sqrt_a:
          arg1 = trace->get_next_loc_f();
          res = trace->get_next_loc_f();
          trace->get_next_val_f(); 
          val1 = val_map[arg1]; 
          val_map[res] = sqrt(val1);
          val_tape->put(val1);
          break;
        case rmpi_send:
        case rmpi_recv:
          break;
        default:
          log.warning << "Unrecongized opcode : " << (int)op << std::endl; 
      }
      op = trace->get_next_op_f();
    }
    return new TrivialTrace<Base>(trace, val_tape);
  }

  TrivialTrace<Base>* trace;  
};

} // namespace ReverseAD

#endif // BASE_FUNCTION_REPLAY_H_
