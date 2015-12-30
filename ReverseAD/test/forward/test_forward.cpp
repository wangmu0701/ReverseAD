#include <memory>
#include <iostream>
#include "reversead/reversead.hpp"
#include "reversead/forwardtype/single_forward.hpp"

using ReverseAD::BaseActive;
using ReverseAD::TrivialTrace;
using ReverseAD::SingleForward;
using ReverseAD::trace_on;
using ReverseAD::trace_off;

typedef BaseActive<SingleForward> fdouble;

int main() {
  SingleForward a(1, 0);
  SingleForward b(2, 1);
  SingleForward y;
  fdouble af;
  fdouble bf;
  fdouble yf;
  ReverseAD::trace_on<SingleForward>();
  af <<= a;
  bf <<= b;
  yf = af * bf;
  yf >>= y;
  std::shared_ptr<ReverseAD::TrivialTrace<SingleForward>> trace =
      ReverseAD::trace_off<SingleForward>();
  trace->dump_trace();
  std::cout << "WTF" << std::endl;
}
