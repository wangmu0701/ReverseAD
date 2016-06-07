#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::BaseReverseGeneric;
using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;

void retrieve_value(size_t t_order,
                    std::shared_ptr<DerivativeTensor<size_t, double>> tensor) {
  size_t size;
  size_t** tind;
  double* values;
  tensor->get_internal_coordinate_list(0, t_order, &size, &tind, &values);
  for (size_t i=0;i<size; i++) {
    std::cout << "T[ ";
    for (size_t j=0;j<t_order; j++) {
      std::cout << tind[i][j] << " ";
    }
    std::cout << "] = " << values[i] << std::endl;
  }
}

int main() {
  double x = 2.0;
  double y;
  adouble yad;
  adouble xad;
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
  //yad = pow(sqrt(xad*xad), 2.0);
  //yad *= log(pow(2, xad)) / log(2);
  yad = atanh(tanh(xad));
  yad >>= y;
  std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
  //trace->dump_trace();
  std::cout << "y = " << y << std::endl;

  ReverseAD::BaseReverseGeneric<double> generic(trace, 4);
  generic.compute(1,1);
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor = generic.get_tensor();
  generic.clear();
  retrieve_value(1, tensor);
  retrieve_value(2, tensor);
  retrieve_value(3, tensor);
  //retrieve_value(4, tensor);
  //retrieve_value(5, tensor);
  //retrieve_value(6, tensor);
}
