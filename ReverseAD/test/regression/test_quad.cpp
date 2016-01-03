#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::TrivialTrace;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseThird;
using ReverseAD::BaseReverseGeneric;
using ReverseAD::DerivativeTensor;


extern double myEps;

void check_value(int, DerivativeTensor<int, double>&, double, bool&);

void check_answer(std::shared_ptr<TrivialTrace<double>> trace,
                  double vx,
                  bool& done) {
  double vy;
  std::shared_ptr<TrivialTrace<double>> new_trace =
      BaseFunctionReplay::replay_ind(trace, &vy,1, &vx, 1);
  if (fabs(vy - vx*vx*vx*vx) > myEps) {
    std::cout << vy << " != " << vx*vx*vx*vx << std::endl;
    done = true;
  }

  ReverseAD::BaseReverseThird<double> third_derivative(new_trace);
  DerivativeTensor<int, double> tensor = third_derivative.compute(1, 1);
  check_value(1, tensor, 4*vx*vx*vx, done);
  check_value(2, tensor, 12*vx*vx, done);
  check_value(3, tensor, 24*vx, done);

  ReverseAD::BaseReverseGeneric<double> generic_derivative(new_trace, 6);
  tensor = generic_derivative.compute(1, 1);
  check_value(1, tensor, 4*vx*vx*vx, done);
  check_value(2, tensor, 12*vx*vx, done);
  check_value(3, tensor, 24*vx, done);
  check_value(4, tensor, 24, done);
  check_value(5, tensor, 0, done);
}

int run_function() {
  bool done = false;
  int testCase = 0;
  const char* testLine;
  while(!done) {
    adouble x, y;
    ReverseAD::trace_on<double>();
    x <<= 2.0;
    switch(testCase) {
    case 0:
      y = x*(x+x-x)*(2*x)/2*sqrt(x*x);
      testLine = "y=x*(x+x-x)*(2*x)/2*sqrt(x*x)";
      break;
    case 1:
      y = exp(log(x));
      y *= pow(x, 3);
      testLine = "y=exp(log(x));y*=pow(x,3)";
      break;
    case 2:
      y = pow(x+2, 2);
      y -= 4*x;
      y -= 4;
      y *= y;
      testLine = "y=pow(x+2,2);y-=4*x;y-=4;y*=y";
      break;
    case 3:
      y = sqrt(x*x)*x;
      y *= (x+2)*(x-2)+4;
      testLine = "y=sqrt(x*x)*x;y*=(x+2)*(x-2)+4";
      break;
    case 4:
      y = 400*x;
      y *= x*x;
      y /= x;
      y *= asin(sin(x/20))*acos(cos(x/20));
      testLine = "y=400*x;y*=x*x;y/=x;y*=asin(sin(x/20))*acos(cos(x/20))";
      break;
    default:
      done = true;
      break;
    }
    double vy;
    y >>= vy;
    if (!done) {
      std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
      check_answer(trace, 1.0, done);
      check_answer(trace, 2.0, done);
      check_answer(trace, 3.0, done);
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
