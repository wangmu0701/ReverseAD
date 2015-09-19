#include <iostream>

#include "src/core/base_active.hpp"
#include "src/core/reversead.hpp"
#include "src/algorithm/base_function_replay.hpp"
#include "src/algorithm/base_reverse_adjoint.hpp"
#include "src/trace/abstract_trace.hpp"
#include "src/trace/trivial_trace.hpp"
#include "src/tape/trivial_tape.hpp"

//using namespace ReverseAD;
//typedef BaseActive<double> adouble;

int main() {
  ReverseAD::trace_on();
  adouble a, b, c, d;
  a <<= 1;
  b <<= 2;
  c <<= 3;
  d <<= 4;
/*
  d = a+b;
  d = c+d;
  adouble x(a+b+c+d);
  double vx;
  x >>= vx;
  ReverseAD::AbstractTrace* trace = ReverseAD::trace_off();
  std::cout << "x = " << x.getVal() << std::endl;
*/
  d = d + 4;
  d = 4 + d;  // 12
  adouble x(a+b+c+d); // 18
  adouble y = (b * c) + d; // 18
  y = y * 2.0; // 36
  x = 2.0 * x;  // 36
  adouble z = x + y; // 72 z = 2(a+b+c+d) + 2(b*c + d);
  double vz;
  z >>= vz;
  ReverseAD::AbstractTrace* trace = ReverseAD::trace_off();
  std::cout << "z = " << z.getVal() << std::endl;
  ReverseAD::BaseFunctionReplay<double> replayer(trace);
  double ind[4] = {1, 2, 3, 4};
  ReverseAD::TrivialTape<double> tape;
  double* dep = replayer.replay(ind, 4, 1, &tape);
  std::cout << "replay dep = " << dep[0] << std::endl;
  ReverseAD::BaseReverseAdjoint<double> adjoint(trace, &tape);
  double vbar = 1;
  double** res = adjoint.compute(&vbar, 4, 1);
  std::cout << res[0][0] << std::endl;
  std::cout << res[0][1] << std::endl;
  std::cout << res[0][2] << std::endl;
  std::cout << res[0][3] << std::endl;
  tape.dump_tape();
} 
