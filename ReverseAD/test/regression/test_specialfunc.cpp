/* 
  This function tests some special cmath elementray functions.
  For those the inverse is hard to compute.
*/

#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::TrivialTrace;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseThird;
using ReverseAD::BaseReverseGeneric;
using ReverseAD::DerivativeTensor;

extern double myEps;

void check_value(size_t, std::shared_ptr<DerivativeTensor<size_t, double>>, double, bool&);

void check_answer(std::shared_ptr<TrivialTrace<double>> trace,
                  double vx,
                  std::vector<double>& derivatives,
                  bool& done) {
  double vy;
  std::shared_ptr<TrivialTrace<double>> new_trace =
      BaseFunctionReplay::replay_ind(trace, &vy,1, &vx, 1);
  if (fabs(vy - derivatives[0]) > myEps) {
    std::cout << vy << " != " << derivatives[0] << std::endl;
    done = true;
  }

  ReverseAD::BaseReverseThird<double> third_derivative(new_trace);
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor =
      third_derivative.compute(1, 1);
  for (size_t i = 1; i <= 3; i++) {
    check_value(i, tensor, derivatives[i], done);
  }

  ReverseAD::BaseReverseGeneric<double> generic_derivative(new_trace, 7);
  tensor = generic_derivative.compute(1, 1);
  for (size_t i = 1; i <= 7; i++) {
    check_value(i, tensor, derivatives[i], done);
  }

  ReverseAD::BaseReverseTensor<double> tensor_derivative(new_trace, 6);
  tensor = tensor_derivative.compute(1, 1);
  for (size_t i = 1; i <= 6; i++) {
    check_value(i, tensor, derivatives[i], done);
  }
}

int run_function() {
  bool done = false;
  myEps = 1.e-7;
  double default_x_value = 1.0;
  int testCase = 0;
  std::vector<double> derivatives;
  const char* testLine;
  while(!done) {
    adouble x, y;
    ReverseAD::trace_on<double>();
    x <<= default_x_value;
    // y = pow(x, 7.0);
    switch(testCase) {
    case 0:
      y = erf(x);
      testLine = "erf(x)";
      derivatives = std::vector<double>(
                    {0.8427007929, 0.4151074974, -0.8302149948, 0.8302149948,
                     1.6604299897, -8.3021499484, 3.3208599794, 76.3797795254}); 
      break;
    default:
      done = true;
      break;
    }
    double vy;
    y >>= vy;
    std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
    if (!done) {
      check_answer(trace, default_x_value, derivatives, done);
      if (done) {
        std::cout << "test " << testLine << " fail!" << std::endl;
        return -1;
      }
      std::cout << "test " << testLine  << " ok." << std::endl;
    }
    testCase++;
  }
  return 0;
}
