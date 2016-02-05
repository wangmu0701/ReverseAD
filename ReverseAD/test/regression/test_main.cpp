#include <memory>
#include "reversead/reversead.hpp"

using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;

double myEps = 1.E-10;

int run_function();

void check_value(int t_order,
                 std::shared_ptr<DerivativeTensor<int, double>> tensor,
                 double true_answer,
                 bool& done) {
  int size;
  int** tind;
  double* values;
  tensor->get_internal_coordinate_list(0, t_order, &size, &tind, &values);
  if (size > 1) {
    std::cout << "size = " << size << std::endl;
    done = true;
  } else if (size == 1) {
    if (fabs(values[0] - true_answer) > myEps) {
      std::cout << "order[" << t_order << "] : "
                << values[0] << " != " << true_answer << std::endl;
      done = true;
    }
  } else {
    if (true_answer != 0.0) {
      std::cout << "order[" << t_order << "] : "
                << "None != " << true_answer << std::endl;
      done = true;
    }
  }
}

int main() {
  return run_function();
}
