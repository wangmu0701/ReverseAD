#ifndef ALGORITHM_COMMON_H_
#define ALGORITHM_COMMON_H_

#include <iostream>
#include "reversead/common/reversead_base.hpp"
#include "reversead/forwardtype/single_forward.hpp"

namespace ReverseAD {

template <typename T>
inline bool IsZero(const T& val) {
  return val == 0.0;
}

template <>
inline bool IsZero<double>(const double& val) {
  return val == 0.0;
}
template <>
inline bool IsZero<SingleForward>(const SingleForward& val) {
  std::cout <<"Spec : " << val << std::endl; 
  return (val.getVal() == 0.0 && val.getDer() == 0.0);
}

template <typename LocType, typename Base>
class DerivativeInfo {
 public:
  DerivativeInfo() {
    clear();
  }

  void clear() {
    r = NULL_LOC; x = NULL_LOC; y = NULL_LOC;
    vx = 0.0; vy = 0.0;
    dx = 0.0; dy = 0.0;
    pxx = 0.0; pxy = 0.0; pyy = 0.0;
    pxxx = 0.0; pxxy = 0.0; pxyy = 0.0; pyyy = 0.0;
  }
  void debug() const {
    std::cout << "opcode = " << (int)opcode << " r = " << r
              << " x = " << x << " y = " << y << std::endl;
    std::cout << "dx = " << dx << " dy = " << dy 
              << " pxx = " << pxx << " pxy = " << pxy
              << " pyy = " << pyy << std::endl;
    std::cout << " pxxx = " << pxxx << " pxxy = " << pxxy
              << " pxyy = " << pxyy << " pyyy = " << pyyy << std::endl;
  }
  opbyte opcode;
  LocType r, x, y;
  mutable double coval; // only used by pow_d_a and pow_a_d
  Base vx, vy;
  Base dx, dy;
  Base pxx, pxy, pyy;
  Base pxxx, pxxy, pxyy, pyyy;
};

} // namespace ReverseAD

#endif // ALGORITHM_COMMON_H_
