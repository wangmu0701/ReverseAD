#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;
using ReverseAD::BaseReverseGeneric;

void retrieve_value(int t_order,
                    BaseReverseGeneric<double>& generic) {
  int* size;
  locint*** tind;
  double** values;
  int dep_size = generic.retrieve_generic_values(t_order, &size, &tind, &values);
  std::cout << "dep_size = " << dep_size << std::endl;  
  for (int i=0;i<size[0]; i++) {
    std::cout << "T[ ";
    for (int j=0;j<t_order; j++) {
      std::cout << tind[0][i][j] << " ";
    }
    std::cout << "] = " << values[0][i] << std::endl;
  }
}

int main() {
  double x = 2.0;
  double y;
  adouble yad;
  adouble xad;
  ReverseAD::logging_on();
  ReverseAD::trace_on<double>();
  xad <<= x;
  //adouble v1 = xad *xad * xad;
  //adouble v2 = v1 * v1;
  //yad = v2 / xad;
  //yad = log(exp(xad));
  //yad = asin(sin(xad/20))*20;
  //yad *= acos(cos(xad/20))*20;
  //yad *= atan(tan(xad/20))*20;
  //yad = asinh(sinh(xad));
  //yad *= acosh(cosh(xad));
  //yad *= atanh(tanh(xad));
  //yad = sqrt(xad*xad);
  //yad = exp(2.0*log(xad));
  yad = pow(sqrt(xad*xad), 2.0);
  yad *= log(pow(2, xad)) / log(2);
  yad >>= y;
  ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
  //trace->dump_trace();
  std::cout << "y = " << y << std::endl;

  ReverseAD::BaseReverseGeneric<double> generic(trace, 4);
  generic.compute(1, 1);
  retrieve_value(1, generic);
  retrieve_value(2, generic);
  retrieve_value(3, generic);
  retrieve_value(4, generic);
  //retrieve_value(5, generic);
  //retrieve_value(6, generic);
}
