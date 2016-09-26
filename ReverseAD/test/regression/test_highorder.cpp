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
                  bool& done) {
  double vy;
  std::shared_ptr<TrivialTrace<double>> new_trace =
      BaseFunctionReplay::replay_ind(trace, &vy,1, &vx, 1);
  if (fabs(vy - pow(vx, 7)) > myEps) {
    std::cout << vy << " != " << pow(vx, 7) << std::endl;
    done = true;
  }

  ReverseAD::BaseReverseThird<double> third_derivative(new_trace);
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor =
      third_derivative.compute(1, 1);
  check_value(1, tensor, 7*pow(vx, 6), done);
  check_value(2, tensor, 42*pow(vx, 5), done);
  check_value(3, tensor, 210*pow(vx, 4), done);

  ReverseAD::BaseReverseGeneric<double> generic_derivative(new_trace, 8);
  tensor = generic_derivative.compute(1, 1);
  check_value(1, tensor, 7*pow(vx, 6), done);
  check_value(2, tensor, 42*pow(vx, 5), done);
  check_value(3, tensor, 210*pow(vx, 4), done);
  check_value(4, tensor, 840*pow(vx, 3), done);
  check_value(5, tensor, 2520*vx*vx, done);
  check_value(6, tensor, 5040*vx, done);
  check_value(7, tensor, 5040, done);

  ReverseAD::BaseReverseTensor<double> tensor_derivative(new_trace, 6);
  tensor = tensor_derivative.compute(1, 1);
  check_value(1, tensor, 7*pow(vx, 6), done);
  check_value(2, tensor, 42*pow(vx, 5), done);
  check_value(3, tensor, 210*pow(vx, 4), done);
  check_value(4, tensor, 840*pow(vx, 3), done);
  check_value(5, tensor, 2520*vx*vx, done);
  check_value(6, tensor, 5040*vx, done);
}

int run_function() {
  bool done = false;
  myEps = 1.e-6;
  int testCase = 0;
  const char* testLine;
  while(!done) {
    adouble x, y;
    ReverseAD::trace_on<double>();
    x <<= 2.0;
    // y = pow(x, 7.0);
    switch(testCase) {
    case 0:
      y = x*(x+x-x)*(2*x)/2*sqrt(x*x)*exp(3.0*log(x));
      testLine = "y=x*(x+x-x)*(2*x)/2*sqrt(x*x)*exp(3.0*log(x))";
      break;
    case 1:
      y = pow(x, 7.0);
      y *= y;
      y = sqrt(y);
      testLine = "y=pow(x,7.0);y*=y;y=sqrt(y);";
      break;
    case 2:
      y = pow(x+2, 2);
      y -= 4*x;
      y -= 4;
      y *= y;
      y = y / (pow(x, -3.0));
      testLine = "y=pow(x+2,2);y-=4*x;y-=4;y*=y;y=y/pow(x,-3)";
      break;
    case 3:
      y = 400*sqrt(x*x)*x; // x^2
      y *= (x+2)*(x-2)+4; //y*=x^2 -> x^4
      y /= (0.05 / (atan(tan(x/20)))); // y/=((1/20)/(x/20)) -> x^5
      y *= asin(sin(x/20))*acos(cos(x/20)); //y*=x^2/400  -> x^7
      testLine = "y=sqrt(x*x)*x;y*=(x+2)*(x-2)+4;y/=20/atan(tan(x/20));y*=asin(sin(x/20))*acos(cos(x/20))";
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
