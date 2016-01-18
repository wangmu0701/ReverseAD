# ReverseAD
## Download and Install
ReverseAD uses GNU automake toolchain. So you should simply be able to compile and install the package following:
```
autoreconf -fi
./configure --prefix=$ReverseADHOME
make; make install
```
To enable MPI wrapper, add `--enable-mpi` in `./configure`.
## One Minute Example
### Source code and sample result
Let's begin with the following code `reversead_one_minute.cpp`
```c++
#include <memory>
#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::TrivialTrace;
using ReverseAD::BaseReverseHessian;
using ReverseAD::DerivativeTensor;
using ReverseAD::trace_on;
using ReverseAD::trace_off;

template <typename T>
T foo(T x1, T x2) {
  return pow(x1+1, 2) + pow(x1*x1 - x2, 2);
}

int main() {
  adouble x1, x2;
  adouble y;
  double vy;
  trace_on<double>(); // begin tracing
  x1 <<= 2.0; // independent variable
  x2 <<= 3.0;
  y = foo<adouble>(x1, x2); // function evaluation
  y >>= vy; // dependent variable
  std::shared_ptr<TrivialTrace<double>> trace =
      trace_off<double>(); // end tracing
  std::cout << "y = " << vy << std::endl;

  BaseReverseHessian<double> hessian(trace);
  DerivativeTensor<int, double> tensor = hessian.compute(2, 1);
    
  // retrieve results
  int size;
  int** tind;
  double* values;
  // adjoints
  tensor.get_internal_coordinate_list(0, 1, &size, &tind, &values);
  std::cout << "size of adjoints = " << size << std::endl;
  for (int i = 0; i < size; i++) {
    std::cout << "A["<< tind[i][0] << "] = " << values[i] << std::endl;
  }
  // hessian  
  tensor.get_internal_coordinate_list(0, 2, &size, &tind, &values);
  std::cout << "size of hessian = " << size << std::endl;
  for (int i = 0; i < size; i++) {
    std::cout << "H["<< tind[i][0] << ", " << tind[i][1]
              << "] = " << values[i] << std::endl;
  }
}
```
A simple `Makefile` can be :
```
ReverseadHome = $(HOME)/packages/reversead
CXX=/usr/local/bin/g++

all : reversead_one_minute

reversead_one_minute : reversead_one_minute.cpp
        $(CXX) -std=c++11 -I$(ReverseadHome)/include $^ -o $@ -L$(ReverseadHome)/lib -lreversead
```
The results of running previous code is :
```
y = 10
size of adjoints = 2
A[0] = 14
A[1] = -2
size of hessian = 3
H[0, 0] = 38
H[1, 0] = -8
H[1, 1] = 2
```
