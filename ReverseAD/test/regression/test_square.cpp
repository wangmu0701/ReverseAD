#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;


int main() {
  bool done = false;
  int testCase = 0;
  double myEps = 1.E-10;
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
    default:
      done = true;
      break;
    }
    double vy;
    y >>= vy;
    if (!done) {
      ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
      ReverseAD::BaseReverseHessian<double> hessian(trace);
      hessian.compute(1,1);
      double** adjoints;
      hessian.retrieve_adjoint(&adjoints);
      if (fabs(adjoints[0][0]-4.0) > myEps) {
        done = true;
      }
      int *size;
      locint **rind;
      locint **cind;
      double** values;
      hessian.retrieve_hessian_sparse_format(&size, &rind, &cind, &values);
      if (size[0] == 1) {
        if (fabs(values[0][0]-2.0) > myEps) {
          done = true;
        }
      } else {
        done = true;
      }
      if (done) {
        std::cout << "A[0] = " << adjoints[0][0] << std::endl;
        std::cout << "H[0] = " << values[0][0] << std::endl;
        std::cout << "test " << testLine << " fail!" << std::endl;
        exit(-1);
      }
      std::cout << "test " << testLine  << " ok." << std::endl;
    }
    testCase++;
  }
}
