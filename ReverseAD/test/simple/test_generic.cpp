#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;


int main() {
  double x = 2.0;
  double y;
  adouble yad;
  adouble xad;
  ReverseAD::logging_on();
  ReverseAD::trace_on<double>();
  xad <<= x;
  adouble v1 = xad *xad;
  adouble v2 = v1 * v1;
  yad = xad * v2;
  yad >>= y;
  ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
  //trace->dump_trace();
  std::cout << "y = " << y << std::endl;

  ReverseAD::BaseReverseGeneric<double> generic(trace);
  generic.compute(1, 1, 6);
}
