#ifndef ALGORITHM_COMMON_H_
#define ALGORITHM_COMMON_H_

#include "reversead/reversead_base.hpp"

namespace ReverseAD {

template <typename T>
inline void T_SWAP(T& a, T& b) {
  T c = std::move(a);
  a = std::move(b);
  b = std::move(c);
}

template <typename LocType>
inline MAX_SWAP(LocType& a, LocType& b) {
  if (a < b) { T_SWAP(a,b);}
}

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

  opbyte opcode;
  LocType r, x, y;
  Base dx, dy;
  Base pxx, pxy, pyy;
};

} // namespace ReverseAD

#endif // ALGORITHM_COMMON_H_
