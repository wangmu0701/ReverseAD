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
      if (fabs(vy - vx * vp) > myEps ) {
        done = true;
      }
      hessian.compute(1,1);
      double** adjoints;
      hessian.retrieve_adjoint(&adjoints);
      if (fabs(adjoints[0][0]-vp) > myEps) {
        done = true;
      }
      int *size;
      locint **rind;
      locint **cind;
      double** values;
      hessian.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
      if (size[0] > 1) {
        done = true;
      } else if (size[0] == 1) {
        if (fabs(values[0][0]-0.0) > myEps) {
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
    if (!done) {
      ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
      check_answer(trace, vx, vp, done);
      check_answer(trace, 4.0, 3.0, done);
      if (done) {
        std::cout << "test " << testLine << " fail!" << std::endl;
        exit(-1);
      }
      std::cout << "test " << testLine  << " ok." << std::endl;
    }
    testCase++;
  }
}
