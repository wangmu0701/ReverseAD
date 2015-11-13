#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include "src/tape/abstract_tape.hpp"
#include "src/tape/trivial_tape.hpp"

#define N 10000000

#define TEST_FAIL std::cout<<"TEST FAIL"<<std::endl;return 1;


int doTheWorkPointer(ReverseAD::AbstractTape<int>* vtape) {
  int i = 0;
  for(i = 0; i < N; i++) {
    vtape->put(i);
  }
  i = 0;
  vtape->init_forward();
  while(vtape->has_next_f()) {
    if (vtape->get_next_f() != i) {TEST_FAIL}
//    std::cout << "forward: " << i << std::endl;
    i++;
    vtape->rewrite_curr_f(i);
  }
  vtape->end_forward();
  i = N;
  vtape->init_reverse();
  while(vtape->has_next_r()) {
    if (vtape->get_next_r() != i) {TEST_FAIL}
//    std::cout << "reverse: " << i << std::endl;
    i--;
  }
}

int doTheWorkReference() {
  ReverseAD::TrivialTape<int> tape;
  int i = 0;
  for(i = 0; i < N; i++) {
    tape.put(i);
  }
  i = 0;
  tape.init_forward();
  while(tape.has_next_f()) {
    if (tape.get_next_f() != i) {TEST_FAIL}
//    std::cout << "forward: " << i << std::endl;
    i++;
    tape.rewrite_curr_f(i);
  }
  tape.end_forward();
  i = N;
  tape.init_reverse();
  while(tape.has_next_r()) {
    if (tape.get_next_r() != i) {TEST_FAIL}
//    std::cout << "reverse: " << i << std::endl;
    i--;
  }
}
int main() {
  ReverseAD::AbstractTape<int>* vtape = new ReverseAD::TrivialTape<int>();
  ReverseAD::TrivialTape<int> tape;
  struct timeval tv1, tv2;
  double time_elapsed = 0;

  gettimeofday(&tv1, NULL);
  int i = 0;
  for(i = 0; i < N; i++) {
    tape.put(i);
  }
  i = 0;
  tape.init_forward();
  while(tape.has_next_f()) {
    if (tape.get_next_f() != i) {TEST_FAIL}
//    std::cout << "forward: " << i << std::endl;
    i++;
    tape.rewrite_curr_f(i);
  }
  tape.end_forward();
  i = N;
  tape.init_reverse();
  while(tape.has_next_r()) {
    if (tape.get_next_r() != i) {TEST_FAIL}
//    std::cout << "reverse: " << i << std::endl;
    i--;
  }
  gettimeofday(&tv2, NULL);
  time_elapsed = tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000;
  std::cout << "Virtual function call takes : " << time_elapsed << " Sec." << std::endl;

  gettimeofday(&tv1, NULL);
  doTheWorkPointer(vtape);
  gettimeofday(&tv2, NULL);
  time_elapsed = tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000;
  std::cout << "Virtual function call takes : " << time_elapsed << " Sec." << std::endl;
  delete vtape; vtape = NULL;

  gettimeofday(&tv1, NULL);
  doTheWorkPointer(new ReverseAD::TrivialTape<int>());
  gettimeofday(&tv2, NULL);
  time_elapsed = tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000;
  std::cout << "Virtual function call takes : " << time_elapsed << " Sec." << std::endl;

  gettimeofday(&tv1, NULL);
  doTheWorkReference();
  gettimeofday(&tv2, NULL);
  time_elapsed = tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000;
  std::cout << "Direct function call takes : " << time_elapsed << " Sec." << std::endl;
  std::cout << "TAPE TEST PASS!" << std::endl;
}

