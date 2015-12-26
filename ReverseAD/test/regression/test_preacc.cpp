#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;

double myEps = 1.E-10;

void check_answer(ReverseAD::TrivialTrace<double>* trace,
                  double vx,
                  double vp,
                  bool& done) {
      double vy;
      ReverseAD::TrivialTrace<double>* new_trace = 
        ReverseAD::BaseFunctionReplay::replay(trace, &vy, 1, &vx, 1, &vp, 1);
      ReverseAD::BaseReverseHessian<double> hessian(new_trace);
      hessian.enable_preacc();
      if (fabs(vy - vx*vx*vp) > myEps ) {
        std::cout << "1" << std::endl;
        done = true;
      }
      hessian.compute(1,1);
      double** adjoints;
      hessian.retrieve_adjoint(&adjoints);
      if (fabs(adjoints[0][0]-2*vx*vp) > myEps) {
        std::cout << "2" << std::endl;
        done = true;
      }
      int *size;
      locint **rind;
      locint **cind;
      double** values;
      hessian.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
      if (size[0] > 1) {
        std::cout << "3" << std::endl;
        done = true;
      } else if (size[0] == 1) {
        if (fabs(values[0][0]-2*vp) > myEps) {
          std::cout << "4" << std::endl;
          done = true;
        }
      }
      if (done) {
        std::cout << "vy = " << vy << std::endl;
        std::cout << "A[0] = " << adjoints[0][0] << std::endl;
        std::cout << "H[0] = " << values[0][0] << std::endl;
      }
}
int main() {
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
      ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
      check_answer(trace, vx, vp, done);
      check_answer(trace, 3.0, 4.0, done);
      if (done) {
        std::cout << "test " << testLine << " fail!" << std::endl;
        exit(-1);
      }
      std::cout << "test " << testLine  << " ok." << std::endl;
    }
    testCase++;
  }
}
