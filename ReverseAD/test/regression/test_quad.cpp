#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;
using ReverseAD::TrivialTrace;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseThird;

double myEps = 1.E-10;

void check_answer(TrivialTrace<double>* trace,
                  bool& done,
                  double vx,
                  bool enable_preacc) {
      double vy;
      TrivialTrace<double>* new_trace =
          BaseFunctionReplay::replay_ind(trace, &vy,1, &vx, 1);
      if (fabs(vy - vx*vx*vx*vx) > myEps) {
        done = true;
      }
      BaseReverseThird<double> base_derivative(new_trace);
      if (enable_preacc) {
        base_derivative.enable_preacc();
      }
      base_derivative.compute(1,1);
      double** adjoints;
      base_derivative.retrieve_adjoint(&adjoints);
      if (fabs(adjoints[0][0]-4*vx*vx*vx) > myEps) {
        done = true;
      }
      int *size;
      locint **rind;
      locint **cind;
      double** values;
      base_derivative.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
      if (size[0] == 1) {
        if (fabs(values[0][0]-12.0*vx*vx) > myEps) {
          done = true;
        }
      } else {
        done = true;
      }

      locint ***tind;
      double** tvalues;
      base_derivative.retrieve_third_sparse_format(&size, &tind, &tvalues);
      if (size[0] > 1) {
        done = true;
      } else if (size[0] == 1) {
        if (fabs(tvalues[0][0] - 24.0*vx) > myEps) {
          done = true;
        }
      }
     
      if (done) {
        std::cout << "y = " << vy << std::endl;
        std::cout << "A[0] = " << adjoints[0][0] << std::endl;
        std::cout << "H[0] = " << values[0][0] << std::endl;
        std::cout << "T[0] = " << tvalues[0][0] << std::endl;
      }
}
int main() {
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
      ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
      check_answer(trace, done, 1.0, false);
      check_answer(trace, done, 2.0, true);
      check_answer(trace, done, 3.0, false);
      if (done) {
        std::cout << "test " << testLine << " fail!" << std::endl;
        exit(-1);
      }
      std::cout << "test " << testLine  << " ok." << std::endl;
    }
    testCase++;
  }
}
