#ifndef REVERSEAD_TENSOR_DERIVATIVE_INFO_H_
#define REVERSEAD_TENSOR_DERIVATIVE_INFO_H_

#include <iostream>

namespace ReverseAD {

template <typename LocType, typename Base>
class TensorDerivativeInfo {
 public:
  TensorDerivativeInfo() {
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

#endif // REVERSEAD_TENSOR_DERIVATIVE_INFO_H_
