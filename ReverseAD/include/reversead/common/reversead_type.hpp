#ifndef REVERSEAD_TYPE_H_
#define REVERSEAD_TYPE_H_

#include <cstdint>
#include <iostream>

#include "reversead/common/reversead_config.h"

#define MAX_LOC 0xfffffffffffffffful
#define BASE_LOC 0x0000800000000000ul

#define NULL_LOC 0

namespace ReverseAD {

  typedef uint8_t opbyte;
  typedef uint64_t locint;

}; // namespace ReverseAD

#endif // REVERSEAD_TYPE_H_

