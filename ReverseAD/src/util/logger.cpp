#include <iostream>
#include <sys/time.h>
#include "reversead/util/logger.hpp"

namespace ReverseAD {

//Log log(&(std::cout));
Log log(nullptr, &(std::cerr), &(std::cerr));

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
