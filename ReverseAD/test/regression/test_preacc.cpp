#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;
using ReverseAD::TrivialTrace;
using ReverseAD::DerivativeTensor;

extern double myEps;

void check_value(int, DerivativeTensor<locint, double>&, double, bool&);

void check_answer(std::shared_ptr<TrivialTrace<double>> trace,
                  double vx,
                  double vp,
                  bool& done) {
  double vy;
  std::shared_ptr<TrivialTrace<double>> new_trace = 
    ReverseAD::BaseFunctionReplay::replay(trace, &vy, 1, &vx, 1, &vp, 1);
  if (fabs(vy - vx*vx*vp) > myEps) {
    std::cout << vy << " != " << vx*vx*vp << std::endl;
    done = true;
  }

  ReverseAD::BaseReverseThird<double> third_derivative(new_trace);
  third_derivative.enable_preacc();
  DerivativeTensor<locint, double> tensor = third_derivative.compute(1, 1);
  check_value(1, tensor, 2*vx*vp, done);
  check_value(2, tensor, 2*vp, done);
  check_value(3, tensor, 0, done);

}
int run_function() {
  bool done = false;
  int testCase = 0;
  const char* testLine;
  while(!done) {
    double vx = 2.0;
    double vp = 3.0;
    adouble x, y, t;
    ReverseAD::trace_on<double>();
    x <<= vx;
    adouble p = adouble::markParam(vp);
    switch(testCase) {
      case 0:
        y = x*x*p;
        testLine = "y=x*x*p";
        break;
      case 1:
        t = x*p;
        y = t*x;
        testLine = "t=x*p;y=t*x;";
        break;
      case 2:
        t = x*x*p+x*p;
        y = t-x*p;
        testLine = "t=x*x*p+x*p;y=t-x*p";
        break;
      case 3:
        t = x*x*x*p*p;
        y = t/x/p;
        testLine = "t=x*x*x*p*p;y=t/x/p";
        break;
      case 4:
        t = (sin(x)*sin(x) + cos(x)*cos(x))*x;
        y = t*x*p;
        testLine = "t=(sin(x)^2+cos(x)^2)*x;y=t*x*p;";
        break;
      case 5:
        y = 0;
        x += 2;
        y += x*x*p;
        y -=4*p;
        y -= 4*x*p;
        y += 8*p;
        testLine = "y=0;x+=2;y+=x*x*p;y-=4*p;y-=4*x*p;y+=8*p;";
        break;
      case 6:
        y = x;
        y *= x*x*p;
        y *= 2;
        y /= x;
        y /= 2;
        testLine = "y=x;y*=x*x*p;y*=2;y/=x;y/=2";
        break;
      case 7:
        x++;
        y = x*x;
        --y;
        y -= 2*(--x);
        y *= p;
        testLine = "x++;y=x*x;--y;y-=2*(--x);y*=p;";
        break;
      default:
        done = true;
        break;
    }
    double vy;
    y >>= vy;
    if (!done) {
      std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
      check_answer(trace, vx, vp, done);
      check_answer(trace, 3.0, 4.0, done);
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
