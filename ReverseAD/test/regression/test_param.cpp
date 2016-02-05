#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::TrivialTrace;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseThird;
using ReverseAD::BaseReverseGeneric;
using ReverseAD::DerivativeTensor;

extern double myEps;

void check_value(int, std::shared_ptr<DerivativeTensor<int, double>>, double, bool&);

void check_answer(std::shared_ptr<TrivialTrace<double>> trace,
                  double vx,
                  double vp,
                  bool& done) {
  double vy;
  std::shared_ptr<TrivialTrace<double>> new_trace = 
      BaseFunctionReplay::replay(trace, &vy, 1, &vx, 1, &vp, 1);

  if (fabs(vy - vx * vp) > myEps) {
    std::cout << vy << " != " << vx * vp << std::endl;
    done = true;
  }

  ReverseAD::BaseReverseThird<double> third_derivative(new_trace);
  std::shared_ptr<DerivativeTensor<int, double>> tensor =
      third_derivative.compute(1, 1).get_tensor();
  check_value(1, tensor, vp, done);
  check_value(2, tensor, 0, done);
  check_value(3, tensor, 0, done);

  ReverseAD::BaseReverseGeneric<double> generic_derivative(new_trace, 6);
  tensor = generic_derivative.compute(1, 1).get_tensor();
  check_value(1, tensor, vp, done);
  check_value(2, tensor, 0, done);
  check_value(3, tensor, 0, done);

}

int run_function() {
  bool done = false;
  int testCase = 0;
  const char* testLine;
  while(!done) {
    double vx = 2.0;
    double vp = 3.0;
    adouble x, y;
    ReverseAD::trace_on<double>();
    x <<= vx;
    adouble p = adouble::markParam(vp);
    switch(testCase) {
    case 0:
      y = x * p;
      testLine = "y=x * p";
      break;
    case 1:
      y = x*p+p-p;
      testLine = "y=x*p+x-x";
      break;
    case 2:
      y = (p+((x+2)-2)*p)-p;
      testLine = "(p+((x+2)-2)*p)-p";
      break;
    case 3:
      y = (p*x*p)/p;
      testLine = "y=(p*x*p)/p";
      break;
    case 4:
      y = (2/x)*p*(x*0.5)*x;
      testLine = "y=(2/x)*p*(x*0.5)*x";
      break;
    case 5:
      {
        adouble t1 = x * 3;
        adouble t2 = p * 2;
        if (t1 == t2) {
          if (x > p) {
            y = x*p+x;
            y -=x;
          } else {
            y = p*x*p;
            y /= p;
          }
        } else {
          y = (2/x)*p*(x*0.5)*x;
        }
      }
      testLine = "Testing conditional branch, ignore the warning.";
      break;
    default:
      done = true;
      break;
    }
    double vy;
    y >>= vy;
    std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
    if (!done) {
      check_answer(trace, vx, vp, done);
      check_answer(trace, 4.0, 3.0, done);
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
