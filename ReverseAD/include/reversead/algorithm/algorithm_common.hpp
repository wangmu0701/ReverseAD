#ifndef ALGORITHM_COMMON_H_
#define ALGORITHM_COMMON_H_

#include <iostream>
#include "reversead/common/reversead_base.hpp"

namespace ReverseAD {

template <typename LocType, typename Base>
class DerivativeInfo {
 public:
  DerivativeInfo() {
    clear();
  }

  void clear() {
    r = NULL_LOC; x = NULL_LOC; y = NULL_LOC;
    dx = 0.0; dy = 0.0;
    pxx = 0.0; pxy = 0.0; pyy = 0.0;
  }
  void debug() const {
    std::cout << "opcode = " << (int)opcode << " r = " << r
              << " x = " << x << " y = " << y << std::endl;
    std::cout << "dx = " << dx << " dy = " << dy 
              << " pxx = " << pxx << " pxy = " << pxy
              << " pyy = " << pyy << std::endl;
  }
  opbyte opcode;
  LocType r, x, y;
  Base dx, dy;
  Base pxx, pxy, pyy;
};

} // namespace ReverseAD

#endif // ALGORITHM_COMMON_H_
