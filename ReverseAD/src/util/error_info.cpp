#include <iostream>
#include <sys/time.h>
#include "reversead/util/error_info.hpp"

namespace ReverseAD {

void warning_NumberInconsistent(const char* const info, int input_num, int trace_num) {
  std::cerr << "The given number of " << info << " variables (" << input_num << ")"
            << "  does not match the record on the trace (" << trace_num << ")."
            << " Will proceed with the trace." << std::endl;
}

void warning_UnrecognizedOpcode(int opcode) {
  std::cerr << "Unrecogized opcode (" << opcode << ") on trace (corrupted?)."
            << std::endl;
}


double get_timing() {
  static struct timeval tv1, tv2;
  static bool is_timing = false;

  double time_elapsed = 0;
  if (is_timing) {
    gettimeofday(&tv2, NULL);
    time_elapsed = (tv2.tv_sec - tv1.tv_sec)
                 + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000;
    tv1 = tv2;
  } else {
    gettimeofday(&tv1, NULL);
    is_timing = true;
  }
  return time_elapsed;
}

} // namespace ReverseAD
