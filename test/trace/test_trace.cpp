#include <iostream>
#include "src/core/reversead.hpp"
#include "src/trace/abstract_trace.hpp"
#include "src/trace/trivial_trace.hpp"

#define TEST_FAIL std::cout<<"test fail!"<<std::endl;return 1;

using namespace ReverseAD;

int main() {
  AbstractTrace *trace = new TrivialTrace();
  opbyte op = 0;
  locint loc = 0;
  double val = 0.0;
  for (int i=0; i<10; i++) {
    trace->putOp(op++);
    trace->putLoc(loc++);
    trace->putVal(val++);
  }
  trace->init_forward();
  op = 0; loc = 0; val = 0.0;
  for (int i = 0; i < 10; i++) {
    if (op != trace->get_next_op_f()) {TEST_FAIL}
    if (loc != trace->get_next_loc_f()) {TEST_FAIL}
    if (val != trace->get_next_val_f()) {TEST_FAIL}
    op++; loc++; val++;
    trace->rewrite_curr_loc_f(loc);
  }
  trace->end_forward();
  trace->init_reverse();
  for(int i = 9; i>=0; i--) {
    op--; val--;
    if (op != trace->get_next_op_r()) {TEST_FAIL}
    if (loc != trace->get_next_loc_r()) {TEST_FAIL}
    if (val != trace->get_next_val_r()) {TEST_FAIL}
    loc--;
  }
  std::cout << "TRACE TEST PASS!" << std::endl;
  return 0;
}
