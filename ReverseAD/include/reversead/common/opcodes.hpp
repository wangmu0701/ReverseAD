#ifndef OPCODES_H_
#define OPCODES_H_

namespace ReverseAD {

enum OPCODES {
  start_of_tape,
  end_of_tape,
  assign_ind,
  assign_dep,
  assign_param,
  assign_a,
  assign_d,
  eq_plus_a,
  eq_plus_d,
  plus_a_a,
  plus_d_a,
  eq_minus_a,
  minus_a_a,
  minus_d_a,
  eq_mult_a,
  eq_mult_d,
  mult_a_a,
  mult_d_a,
  eq_div_a,
  div_a_a,
  div_d_a,
  sin_a,
  cos_a,
  tan_a,
  asin_a,
  acos_a,
  atan_a,
  pow_a_a,
  pow_a_d,
  pow_d_a,
  sqrt_a,
  exp_a,
  log_a,
  comp_eq,
  comp_lt,
  rmpi_send,
  rmpi_recv
};

} // namespace ReverseAD

#endif // OPCODES_H_
