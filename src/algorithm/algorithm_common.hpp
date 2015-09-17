#ifndef ALGORITHM_COMMON_H_
#define ALGORITHM_COMMON_H_

namespace ReverseAD {

template <typename T>
inline void T_SWAP(T& a, T& b) {
  T c = std::move(a);
  a = std::move(b);
  b = std::move(c);
}

template <typename T>
inline MAX_SWAP(T& a, T& b) {
  if (a < b) { T_SWAP(a,b);}
}

template <typename LocType>
class DerivativeInfo {
 public:
  DerivativeInfo() {
    clear();
  }
  ~DerivativeInfo() {}

  void clear() {
    r = 0; x = 0; y = 0;
    dx = 0.0; dy = 0.0;
  }

  opbyte opcode;
  LocType r, x, y;
  double dx, dy;
} // namespace ReverseAD

#endif // ALGORITHM_COMMON_H_
