#ifndef REVERSEAD_ALGORITHM_COMMON_H_
#define REVERSEAD_ALGORITHM_COMMON_H_

#include <iostream>
#include "reversead/common/reversead_core.hpp"
#include "reversead/forwardtype/single_forward.hpp"
#include "reversead/forwardtype/multi_forward.hpp"

#define REVERSEAD_MAX_GENERIC_ORDER 10
#define REVERSEAD_MAX_TENSOR_ORDER 6

namespace ReverseAD {

template <typename T>
inline bool IsZero(const T& val) {
  return val == 0.0;
}

inline bool IsZero(const SingleForward& val) {
  return val.getVal() == 0.0 && val.getDer() == 0.0;
}

template <size_t DIM>
inline bool IsZero(const MultiForward<DIM>& val) {
  if (val.getVal() != 0.0) {return false;}
  for (size_t i = 0; i < DIM; i++) {
    if (val.getDer(i) != 0.0) {return false;}
  }
  return true;
}

} // namespace ReverseAD

#endif // REVERSEAD_ALGORITHM_COMMON_H_
