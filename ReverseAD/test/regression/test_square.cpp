#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
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
  if (fabs(vy - vx * vx) > myEps) {
    std::cout << vy << " != " << vx * vx << std::endl;
    done = true;
  }

  ReverseAD::BaseReverseThird<double> third_derivative(new_trace);
  DerivativeTensor<int, double> tensor = third_derivative.compute(1, 1);
  check_value(1, tensor, 2 * vx, done);
  check_value(2, tensor, 2, done);
  check_value(3, tensor, 0, done);

  ReverseAD::BaseReverseGeneric<double> generic_derivative(new_trace, 6);
  tensor = generic_derivative.compute(1, 1);
  check_value(1, tensor, 2 * vx, done);
  check_value(2, tensor, 2, done);
  check_value(3, tensor, 0, done);
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
      y = x*x;
      testLine = "y=x*x";
      break;
    case 1:
      y = (x*x*x)/x;
      testLine = "y=(x*x*x)/x";
      break;
    case 2:
      y = (x+2)*(x-2)+4;
      testLine = "(x+2)*(x-2)+4";
      break;
    case 3:
      y = sqrt(x*x)*x;
      testLine = "y=sqrt(x*x)*x";
      break;
    case 4:
      y = (2*x) / (2/x);
      testLine = "y=(2*x)/(2/x)";
      break;
    case 5:
      y = tan(atan(x*x/20))*20;
      testLine = "y=tan(atan(x*x/20))*20";
      break;
    case 6:
      y = exp(2*log(x));
      testLine = "y=exp(2*log(x))";
      break;
    case 7:
      y = sqrt(log(exp(x*x*x*x)));
      testLine = "y=sqrt(log(exp(x*x*x*x)))";
      break;
    case 8:
      y = pow(sqrt(x), 4);
      testLine = "y=pow(sqrt(x), 4)";
      break;
    case 9:
      y = pow(1,x)*x*sqrt(pow(x,2));
      testLine = "y=pow(1,x)*x*sqrt(pow(x,2))";
      break;
    case 10:
      y = 0;
      x += 2;
      y += x*x;
      y -=4;
      y -= 4*x;
      y += 8;
      testLine = "y=0;x+=2;y+=x*x;y-=4;y-=4*x;y+=8;";
      break;
    case 11:
      y = x;
      y *= x*x;
      y *= 2;
      y /= x;
      y /= 2;
      testLine = "y=x;y*=x*x;y*=2;y/=x;y/=2";
      break;
    default:
      done = true;
      break;
    }
    double vy;
    y >>= vy;
    std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
    if (!done) {

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
