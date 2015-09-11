#ifndef TRIVIAL_TAPE_H_
#define TRIVIAL_TAPE_H_

#include "AbstractTapeInterface.hpp"

namespace ReverseAD {

template <typename Type>
class TrivialTape : public AbstractTapeInterface<Type>

} // namespace ReverseAD

#endif // TRIVIAL_TAPE_H_
