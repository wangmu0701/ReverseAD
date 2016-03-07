#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseThird;

extern double myEps;

void check_value(int, std::shared_ptr<DerivativeTensor<int, double>>, double, bool&);

void check_answer(std::shared_ptr<TrivialTrace<double>> trace,
                  double vx,
                  bool& done) {
  double vy;
  std::shared_ptr<TrivialTrace<double>> new_trace =
      BaseFunctionReplay::replay_ind(trace, &vy,1, &vx, 1);
  if (fabs(vy - vx) > myEps) {
    printf("vy = %.15f, vx = %.15f, eps = %.15f\n", vy, vx, myEps);
    std::cout << vy << " != " << vx << std::endl;
    done = true;
  }

  ReverseAD::BaseReverseThird<double> third_derivative(new_trace);
  third_derivative.compute(1,1);
  std::shared_ptr<DerivativeTensor<int, double>> tensor =
      third_derivative.get_tensor();
  check_value(1, tensor, 1, done);
  check_value(2, tensor, 0, done);
  check_value(3, tensor, 0, done);

  ReverseAD::BaseReverseGeneric<double> generic_derivative(new_trace, 6);
  tensor = generic_derivative.compute(1, 1).get_tensor();
  check_value(1, tensor, 1, done);
  check_value(2, tensor, 0, done);
  check_value(3, tensor, 0, done);
 
  ReverseAD::BaseReverseGenerator<double> generator_derivative(new_trace, 3);
  tensor = generator_derivative.compute(1, 1).get_tensor();
  check_value(1, tensor, 1, done);
  check_value(2, tensor, 0, done);
  check_value(3, tensor, 0, done);

  ReverseAD::BaseReverseTensor<double> tensor_derivative(new_trace, 3);
  tensor = tensor_derivative.compute(1, 1).get_tensor();
  check_value(1, tensor, 1, done);
  check_value(2, tensor, 0, done);
  check_value(3, tensor, 0, done);
}

int run_function() {
  bool done = false;
  int testCase = 0;
  const char* testLine = nullptr;
  while(!done) {
    double vx = 2.0;
    adouble x, y;
    ReverseAD::trace_on<double>();
    x <<= vx;
    switch(testCase) {
    case 0:
      y = x;
      testLine = "y=x";
      break;
    case 1:
      y = x+x-x;
      testLine = "y=x+x-x";
      break;
    case 2:
      y = -2+(2+((x+2)-2));
      testLine = "-2+(2+((x+2)-2))";
      break;
    case 3:
      y = (2*x)/2;
      testLine = "y=(2*x)/2";
      break;
    case 4:
      y = (x*x)/x;
      testLine = "y=(x*x)/x";
      break;
    case 5:
      y = sqrt(x*x);
      testLine = "y=sqrt(x*x)";
      break;
    case 6:
      y = (2/x)*x*(x*0.5);
      testLine = "y=(2/x)*x*(x*0.5)";
      break;
    // tests for trigonometric functions
    case 7:
      y = (sin(x)*sin(x) + cos(x)*cos(x))*x;
      testLine = "y=(sin(x)^2 + cos(x)^2) * x";
      break;
    case 8:
      y = asin(sin(x/10))*10;
      testLine = "y=asin(sin(x/10))*10";
      break;
    case 9:
      y = acos(cos(x/20))*20;
      testLine = "y=acos(cos(x/20))*20";
      break;
    case 10:
      y = tan(atan(x/5))*5;
      testLine = "y=tan(atan(x/5))*5";
      break;
    case 11:
      y = atan(sin(x/10)/cos(x/10))*10;
      testLine = "y=atan(sin(x/10)/cos(x/10))*10";
      break;
    // pow, sqrt, exp, log
    case 12:
      y = exp(log(x));
      testLine = "y=exp(log(x))";
      break;
    case 13:
      y = exp(2*log(sqrt(x)));
      testLine = "y=exp(2*log(sqrt(x)))";
      break;
    case 14:
      y = pow(x, 1);
      testLine = "y=pow(x, 1)";
      break;
    case 15:
      y = pow(sqrt(x), 2);
      testLine = "y=pow(sqrt(x), 2)";
      break;
    case 16:
      y = pow(1, x) * x;
      testLine = "y=pow(1,x)*x";
      break;
    case 17:
      y = 0;
      y += 2.0*x;
      y -= x;
      testLine = "y=0;y+=2*x;y-=x";
      break;
    case 18:
      y = 1;
      y *= x*x;
      y /= x;
      testLine = "y=1;y*=x*x;y/=x";
      break;
    case 19:
      x += 2;
      y = x*x;
      y -= 4;
      x -= 2;
      y -= x*x;
      y /= 2;
      y *= 0.5;
      testLine = "x+=2;y=x*x;y-=4;x-=2;y-=x*x;y/=2;y*=0.5";
      break;
    case 20:
      y = asinh(sinh(x));
      testLine = "y=asinh(sinh(x))";
      break;
    case 21:
      y = acosh(cosh(x));
      testLine = "y=acosh(cosh(x))";
      break;
    case 22: // stable issue?
      myEps = 1.E-5;
      y = atanh(tanh(x));
      testLine = "y=atanh(tanh(x))";
      break;
    case 23:
      myEps = 1.E-10;
      y = fabs(x);
      testLine = "y=fabs(x)";
      break;
    case 24:
      y = fabs(-x);
      testLine = "y=fabs(-x)";
      break;
    default:
      done = true;
      break;
    }
    double vy;
    y >>= vy;
    std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
    if (!done) {
      check_answer(trace, 2.0, done);
      check_answer(trace, 4.0, done);
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
