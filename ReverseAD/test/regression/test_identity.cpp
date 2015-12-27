#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;
using ReverseAD::TrivialTrace;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseThird;

double myEps = 1.E-5;

void check_answer(std::shared_ptr<TrivialTrace<double>> trace,
                  double vx,
                  bool& done) {
      double vy;
      std::shared_ptr<TrivialTrace<double>> new_trace =
          BaseFunctionReplay::replay_ind<double>(trace, &vy, 1, &vx, 1);
      if (fabs(vy - vx) > myEps) {
        done = true;
      }
      BaseReverseThird<double> base_derivative(new_trace);
      base_derivative.compute(1,1);
      double** adjoints;
      base_derivative.retrieve_adjoint(&adjoints);
      if (fabs(adjoints[0][0]-1.0) > myEps) {
        done = true;
      }
      int *size;
      locint **rind;
      locint **cind;
      double** values;
      base_derivative.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
      if (size[0] > 1) {
        done = true;
      } else if (size[0] == 1) {
        if (fabs(values[0][0]-0.0) > myEps) {
          done = true;
        }
      }
      locint ***tind;
      double** tvalues;
      base_derivative.retrieve_third_sparse_format(&size, &tind, &tvalues);
      if (size[0] > 1) {
        done = true;
      } else if (size[0] == 1) {
        if (fabs(tvalues[0][0] - 0.0) > myEps) {
          done = true;
        }
      }
      if (done) {
        std::cout << "vy = " << vy << std::endl;
        std::cout << "A[0] = " << adjoints[0][0] << std::endl;
        std::cout << "H[0] = " << values[0][0] << std::endl;
        std::cout << "T[0] = " << tvalues[0][0] << std::endl;
      }
}
int main() {
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
    case 22:
      y = atanh(tanh(x));
      testLine = "y=atanh(tanh(x))";
      break;
    case 23:
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
    if (!done) {
      std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
      check_answer(trace, 2.0, done);
      check_answer(trace, 4.0, done);
      if (done) {
        std::cout << "test " << testLine << " fail!" << std::endl;
        exit(-1);
      }
      std::cout << "test " << testLine  << " ok." << std::endl;
    }
    testCase++;
  }
}
