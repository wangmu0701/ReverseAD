#include <cstdlib>
#include <iostream>
#include "src/tape/abstract_tape.hpp"
#include "src/tape/trivial_tape.hpp"

#define TEST_FAIL std::cout<<"TEST FAIL"<<std::endl;return 1;

int main() {
  ReverseAD::AbstractTape<int>* tape = new ReverseAD::TrivialTape<int>();
  for(int i = 0; i < 10; i++) {
    tape->put(i);
  }
  int i = 0;
  tape->init_forward();
  while(tape->has_next_f()) {
    if (tape->get_next_f() != i) {TEST_FAIL}
    std::cout << "forward: " << i << std::endl;
    i++;
    tape->rewrite_curr_f(i);
  }
  tape->end_forward();
  i = 10;
  tape->init_reverse();
  while(tape->has_next_r()) {
    if (tape->get_next_r() != i) {TEST_FAIL}
    std::cout << "reverse: " << i << std::endl;
    i--;
  }

  std::cout << "TEST PASS!" << std::endl;
}

