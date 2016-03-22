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

template <typename LocType, typename Base>
class TensorInfo {
 public:
  TensorInfo() {
    clear();
  }
  void clear() {
    r = NULL_LOC; x = NULL_LOC; y = NULL_LOC;
    dx = 0.0; dy = 0.0;
    pxx = 0.0; pxy = 0.0; pyy = 0.0;
    pxxx = 0.0; pxxy = 0.0; pxyy = 0.0; pyyy = 0.0;
    pxxxx = 0.0; pxxxy = 0.0; pxxyy = 0.0; pxyyy = 0.0; pyyyy = 0.0;
    pxxxxx = 0.0; pxxxxy = 0.0; pxxxyy = 0.0;
    pxxyyy = 0.0; pxyyyy = 0.0; pyyyyy = 0.0;
    pxxxxxx = 0.0; pxxxxxy = 0.0; pxxxxyy = 0.0; pxxxyyy = 0.0;
    pxxyyyy = 0.0; pxyyyyy = 0.0; pyyyyyy = 0.0;
  }
  opbyte opcode;
  LocType r, x, y;
  Base dx, dy;
  Base pxx, pxy, pyy;
  Base pxxx, pxxy, pxyy, pyyy;
  Base pxxxx, pxxxy, pxxyy, pxyyy, pyyyy;
  Base pxxxxx, pxxxxy, pxxxyy, pxxyyy, pxyyyy, pyyyyy;
  Base pxxxxxx, pxxxxxy, pxxxxyy, pxxxyyy, pxxyyyy, pxyyyyy, pyyyyyy;
};

} // namespace ReverseAD

#endif // ALGORITHM_COMMON_H_
