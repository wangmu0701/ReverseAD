#ifndef REVERSE_AD_ERROR_LOG_H_
#define REVERSE_AD_ERROR_LOG_H_

#include <iostream>

namespace ReverseAD {

template <typename Base>
void warning_ParameterOutOfBound(const Base& val, const char* const opname) {
  std::cerr << "Parameter : " << val << " out of bound for " << opname
           << std::endl;
}

template <typename Base>
void warning_BranchInconsistent(const Base& lhs, const char* const opname, const Base& rhs) {
  std::cerr << "Branch condition inconsistent : "
            << lhs << " " << opname << " " << rhs 
            << ". Consider retrace!" << std::endl;
}

void warning_NumberInconsistent(const char* const info, int input_num, int trace_num);

void warning_UnrecognizedOpcode(int opcode);
void warning_NoTraceSet();

double get_timing();

} // namespace ReverseAD

#endif // REVERSE_AD_LOGGER_H_
