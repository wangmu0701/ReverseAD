#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::locint;
using ReverseAD::TrivialTrace;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseGeneric;

double myEps = 1.E-10;


void check_value(int t_order,
                 BaseReverseGeneric<double>& generic,
                 double true_answer,
                 bool& done) {
  int* size;
  locint*** tind;
  double** values;
  int dep_size = generic.retrieve_generic_values(t_order, &size, &tind, &values);
  if (dep_size != 1) {
    std::cout << "dep_size = " << dep_size << std::endl;
    done = true;
    return;
  }
  if (size[0] > 1) {
    std::cout << "size = " << size[0] << std::endl;
    done = true;
  } else if (size[0] == 1) {
    if (fabs(values[0][0] - true_answer) > myEps) {
      std::cout << values[0][0] << " != " << true_answer << std::endl;
      done = true;
    }
  } else {
    if (true_answer != 0.0) {
      std::cout << "None != " << true_answer << std::endl;
      done = true;
    }
  }
}

//check answer up to order 6
void check_answer(TrivialTrace<double>* trace,
                  bool& done,
                  double vx) {
      double vy;
      TrivialTrace<double>* new_trace =
          BaseFunctionReplay::replay_ind(trace, &vy,1, &vx, 1);
      if (fabs(vy - vx*vx*vx*vx*vx) > myEps) {
        done = true;
      }
      BaseReverseGeneric<double> generic_derivative(new_trace, 6);
      generic_derivative.compute(1, 1);
      check_value(1, generic_derivative, 5*vx*vx*vx*vx, done);
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
      y = x*x*x*x*x;
      testLine = "y=x*x*x*x*x";
      break;
    case 1:
      y = x*x*x;
      y *= y;
      y /= x;
      testLine = "y=x*x*x;y*=y;y/=x";
      break;
    default:
      done = true;
      break;
    }
    double vy;
    y >>= vy;
    if (!done) {
      ReverseAD::TrivialTrace<double>* trace = ReverseAD::trace_off<double>();
      check_answer(trace, done, 1.0);
      check_answer(trace, done, 2.0);
      check_answer(trace, done, 3.0);
      if (done) {
        std::cout << "test " << testLine << " fail!" << std::endl;
        exit(-1);
      }
      std::cout << "test " << testLine  << " ok." << std::endl;
    }
    testCase++;
  }
}
