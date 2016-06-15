# ReverseAD

*****

1. Background
2. Installation
3. Examples
4. Implementation Detail

## Background

### What is Automatic Differentiation

Automatic differentiation or algorithmetic differentiation is a technique that algorithmetically, thus in macheine precision, computes the derivative of an objective function specified by a computer program. 



### What is ReverseAD

`ReverseAD` is an implementation of high order reverse mode. The description of the algorithm can be found [here](https://www.cs.purdue.edu/homes/wang970/RevBeamer.pdf). 

## Installation

## Examples

### One Minute Example

### High Order Derivatives

### Directional Derivatives

## Implementation Detail

`ReverseAD` is a simple AD tool designed for evaluating high order derivative tensors directly via reverse mode AD.

## Download and Install
ReverseAD uses GNU automake toolchain. So you should simply be able to compile and install the package following:
```
autoreconf -fi
./configure --prefix=$ReverseADHOME
make; make install
```

****
## One (Ten) Minute Example
### Source code and sample result
Let's begin with the following example [`one_minute.cpp`](https://github.com/wangmu0701/ReverseAD/blob/master/ReverseAD/example/oneminute/one_minute.cpp)
```c++
#include <memory>
#include <iostream>

#include "reversead/reversead.hpp"

using ReverseAD::adouble;
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
  x1 <<= 2.0; // independent variable #0
  x2 <<= 3.0; // independent variable #1
  y = foo<adouble>(x1, x2); // function evaluation
  y >>= vy; // dependent variable
  std::shared_ptr<TrivialTrace<double>> trace =
      trace_off<double>(); // end tracing
  std::cout << "y = " << vy << std::endl;

  std::unique_ptr<BaseReverseHessian<double>> hessian(
      new BaseReverseHessian<double>(trace));
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor = hessian->compute(2,1);

  // retrieve results
  size_t size;
  size_t** tind;
  double* values;
  // adjoints : dep[0].order[1]
  tensor->get_internal_coordinate_list(0, 1, &size, &tind, &values);
  std::cout << "size of adjoints = " << size << std::endl;
  for (size_t i = 0; i < size; i++) {
    std::cout << "A["<< tind[i][0] << "] = " << values[i] << std::endl;
  }
  // hessian : dep[0].order[2]
  tensor->get_internal_coordinate_list(0, 2, &size, &tind, &values);
  std::cout << "size of hessian = " << size << std::endl;
  for (size_t i = 0; i < size; i++) {
    std::cout << "H["<< tind[i][0] << ", " << tind[i][1]
              << "] = " << values[i] << std::endl;
  }
}

```
A simple `Makefile` can be :
```
ReverseadHome = $(HOME)/packages/reversead
CXX=/usr/local/bin/g++

all : one_minute

one_minute : one_minute.cpp
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
****
## In depth explanation
### Header files
`reversead.hpp` packs all necessary header files for the package. This could be the only header file you need to include.
```c++
#include "reversead/reversead.hpp"
```
### ReverseAD namespace
Almost all functions, types and classes provided by **ReverseAD** are within namespace `ReverseAD`.  So use using-directives for namespaces or using-declarations for namespace members to resolve references. As in the code :
```c++
using ReverseAD::adouble;
using ReverseAD::TrivialTrace;
using ReverseAD::BaseReverseHessian;
using ReverseAD::DerivativeTensor;
using ReverseAD::trace_on;
using ReverseAD::trace_off;
```

### Active type and active region
1. ~Active Type~ : Variable with active type get involved in derivative evaluation. *ReverseAD* provides type `adouble` as the reverse active type with derivative part of `double` type. `adouble` is **also** within namespace `ReverseAD`.
2. ~Active Region~: An active region defines a objective function. It should contain declaration of `independent variables`, declaration of `dependent variables` and a `function body`. For `adouble`, the active region begins with `trace_on<double>()` and ends with `trace_off<double>()`.
3. ~Trace ~ : A `Trace` returncd by `trace_off<double>()` contains all information one needs to evaluate the derivatives of that `active region`. We use `std::shared_ptr<TrivialTrace<double>>` as the type of trace.

### Derivative evaluation
Once we get a `trace` for an `active region`, we can pass it to a `derivative evaluation class` to evaluate it's derivatives. In the example we uses `BaseReverseHessian` which evaluates the derivatives up to second order.
```c++
  std::unique_ptr<BaseReverseHessian<double>> hessian(new BaseReverseHessian<double>(trace));
```
This code creates an instance of `BaseReverseHessian` namely `hessian`.
```c++
  std::shared_ptr<DerivativeTensor<size_t, double>> tensor = hessian.compute(2, 1);
```
Then we can call the member function `compute(ind_num, dep_num)` to evaluate the derivatives for the `trace` up to second order and the results are returned into a `std::shared_ptr<DerivativeTensor<size_t, double>>`. 

Other `derivative evaluation class` are given in the following table:

| Class              | Order (d) | Constructor                          |
| :----------------- | :-------: | :----------------------------------- |
| BaseReverseAdjoint |     1     | BaseReverseAdjoint<double>(trace)    |
| BaseReverseHessian |     2     | BaseReverseHessian<double>(trace)    |
| BaseReverseThrid   |     3     | BaseReverseThird<double>(trace)      |
| BaseReverseGeneric |   1-10    | BaseReverseGeneric<double>(trace, d) |
| BaseReverseTensor  |    1-6    | BaseReverseTensor<double>(trace, d)  |

### Retrieve derivative tensor
After we call the `compute(ind_num, dep_num)` function of a `derivative evaluation class` the derivatives are stored in to a `DerivativeTensor<size_t, double>`. The derivative tensor of each order for each dependent variable is organized in a `sparse coordinate list format`. The function `get_internal_coordinate_list` will expose pointers to the internal array. For example:
```c++
  tensor.get_internal_coordinate_list(0, 1, &size, &tind, &values);
```
will get the size, coordinate array, value array for the first order derivative (`1`) for the first dependent variable (`0`).
```c++
  tensor.get_internal_coordinate_list(0, 2, &size, &tind, &values);
```
will get the size, coordinate array, value array for the second order derivative (`2`) for the first dependent variable (`0`). For derivative higher than first order, only the lower part of the tensor will be reported.

**Do Not deallocate those pointers since they are maintained internally**
