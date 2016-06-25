# ReverseAD

*****

1. Background
2. Installation
3. Usage
4. Examples
5. Implementation Detail

## Background

### What is Automatic Differentiation

Automatic differentiation or algorithmetic differentiation is a technique that algorithmetically, thus in macheine precision, computes the derivative of an objective function specified by a computer program.



### What is ReverseAD

`ReverseAD` is an implementation of high order reverse mode using `operator overloading`. The description of the algorithm can be found [here](https://www.cs.purdue.edu/homes/wang970/RevBeamer.pdf). 



`ReverseAD` is free software; you can redistribute it and/or modif it under terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.



`ReverseAD` is distributed in the hope that it will be useful, but **WITHOUT ANY WARRANTY**; without even the implied warranty of **MERCHANTABIKITY** or **FITNESS FOR A PARTICULAR PURPOSE**. See the GNU Lesser General Public License for more details. 



You should have received a copy of the GNU Lesser General Public License along with `ReverseAD`. If not, see [http://www.gnu.org/licenses](http://www.gnu.org/licenses).



## Installation

### System Requirements

You should have GNU automake toolchain available. And a `c++` compiler which supports `c++11`.



### Download and Install

You can find the source code of `ReverseAD` on github [here](https://github.com/wangmu0701/ReverseAD).

You can either clone the repository by :

```sh
git clone https://github.com/wangmu0701/ReverseAD
```

, or download a `zip` ball from the webpage.



`ReverseAD` uses GNU automake toolchain. So you should simply be able to compile and install the package.

```
autoreconf -fi
./configure --prefix=$ReverseADHOME
make; make install
```

## Usage

We'll use the one minute example to show the basic usage of `ReverseAD`. The code can be found [here](https://github.com/wangmu0701/ReverseAD/blob/master/ReverseAD/example/oneminute/one_minute.cpp).

### Header file

[`reversead.hpp`](https://github.com/wangmu0701/ReverseAD/blob/master/ReverseAD/include/reversead/reversead.hpp) packs all necessary header files for the package. This could be the only header file you need to include.

```c++
#include "reversead/reversead.hpp"
```

### Namespace

Almost all functions, types and classes provided by `ReverseAD` are within namespace **ReverseAD**. You can choose either using-directives for namespaces or using-declarations for namespace members to resolve references. For example:

```c++
using namespace ReverseAD;
```

```c++
using ReverseAD::adouble;
```

### Active Type (ReverseAD::adouble)

Since `ReverseAD` is implemented using `operator overloading`, the `active type` defines which variables are *active* (involved) in the derivative evaluation. The `active type` in `ReverseAD` is  `ReverseAD::adouble`. This type should be used on all independent variables, dependent variables, and all intermediate variables. Variables of `active type` are called `active variables`.



### Active Region

In `ReverseAD`, an `active region` is a section in the program defines the objective function. An `active region` often contains three parts: declearations of independent variables, a function body and declearations of dependent variables.

The following function defines a beginning of an `active region`:

```c++
void ReverseAD::trace_on<double>();
```

The following function ends an `active region`:

```c++
std::shared_ptr<TrivialTrace<double>> ReverseAD::trace_off<double>();
```

the return value is a `std::shared_ptr<TrivialTrace<double>>` which contains a pointer to the trace of the `active region`. **The template parameter <double> is used to specifiy the value type of `active variables` (see implementation details for more information)**

### Function Trace

Since `ReverseAD` implements the reverse mode algorithm, it needs a `function trace` so that a reverse sweep is possible. The `function trace` contains information about *every overloaded operations* within the `active region`. 

~~With the `function trace`, you can replay the function evaluation with another set of initial values. Though it may not be as efficient as generating another trace by calling the active region one more time and it may cause errors if the conditional branches are violated due to the different initial values. But it will save memory if for some reason you want to keep both traces.~~



### Declaration of Independent/dependents

The operator`<<=` declares an independent variable for the objective function, for example:

```c++
adouble x1, x2;
x1 <<= 2.0;
x2 <<= 3.0;
```

declares two independent variables `x1` and `x2`, the initial values are `2.0` and `3.0` respectively.

The operator >>= declares an dependent variable for the objective function, for example:

```c++
adouble y;
double vy;
y >>= vy;
```

declares a dependent variable `y` and the value is assigned to a `double` type variable `vy`.

### Function Body

Between the declaration of independent variables and dependent variables, the `active region` contains the computations of how dependent variables depend on independent variables. In the example, it's a template function :

```c++
template <typename T>
T foo(T x1, T x2) {
  return pow(x1+1, 2) + pow(x1*x1 - x2, 2);
}
y = foo<adouble>(x1, x2); // function evaluation
```



### Derivative Evaluation Class

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

### Derivative Tensor

After we call the `compute(ind_num, dep_num)` function of a `derivative evaluation class` the derivatives are stored in to a `DerivativeTensor<size_t, double>`. The derivative tensor of each order for each dependent variable is organized in a `sparse coordinate list format`. The function `get_internal_coordinate_list` will expose pointers to the internal array. For example:

```c++
  tensor.get_internal_coordinate_list(0, 1, &size, &tind, &values);
```

will get the size, coordinate array, value array for the first order derivative (`1`) for the first dependent variable (`0`).

```c++
  tensor.get_internal_coordinate_list(0, 2, &size, &tind, &values);
```

will get the size, coordinate array, value array for the second order derivative (`2`) for the first dependent variable (`0`). For derivative higher than first order, only the lower part of the tensor will be reported.

**Important: Do Not deallocate those pointers. They will be released when the std::shared_ptr<> is destroyed or reset. Convert them into your own data structures.**



## Examples

### One Minute Example

This example shows the basis of `ReverseAD`. The code can be found [here](https://github.com/wangmu0701/ReverseAD/blob/master/ReverseAD/example/oneminute/one_minute.cpp). We've covered every details in this example in previous section.

### High Order Derivatives

### Time Step Functions



## Implementation Detail

### Design Philosiply

#### Active Type

In `ReverseAD`, the active type is implemented as a template `BaseActive`.  The arithematic operators and intrinsic functions are overloaded for `BaseActive` type to generate the `function trace`. 

```c++
template <typename Base>
class BaseActive{
  Base _val;
  locint _loc;
}
```

In [reversead_type.hpp](https://github.com/wangmu0701/ReverseAD/blob/master/ReverseAD/include/reversead/common/reversead_type.hpp), `locint` is defined as:

```c++
  typedef uint32_t locint;
```

so it's simply an unsigned int.

The template parameter `Base` defined the value type of the `active type`. For the most common case, it's `double` type. The `ReverseAD::adouble` is actually a `typedef`.

```c++
namespace ReverseAD{
  typedef BaseActive<double> adouble;
}
```

If we want to apply a forward reverse mode, we can simply use the type `BaseActive<SingleForward>` for all `active variables`. In this case we have to use `SingleFowward` as the template parameter in all of the following.

```c++
trace_on<T>();
std::shared_ptr<TrivialTrace<T>> trace_off<T>();
BaseReverseHessian<T>;
std::shared_ptr<DerivativeTensor<size_t, T>>;
```



#### Indexing Scheme

On the `trace`, each `active variable` is represented by its `index`, (`_loc` in the `BaseActive`). 

#### Trace and Tape

A `Tape` is a sequencial data structure which support `append`, `forward iteration` and `reverse iteration`.

```c++
template <typename T>
class TrivialTape {
 public:
  void append(const T& val);
  ...
  T get_next_f();
  ...
  T get_next_r();
}
```



A `Trace` consists of several `Tape` and it contains every information about the objective function. An example is:

```c++
template <typename Base>
class TrivialTrace{
  std::shared_ptr<VirtualTape<opbyte>> op_tape; // operations
  std::shared_ptr<VirtualTape<locint>> loc_tape; // indexing of active variables
  std::shared_ptr<VirtualTape<Base>> val_tape; // value of active variables
  std::shared_ptr<VirtualTape<double>> coval_tape;  // constants
}
```

The `VirtualTape` can be either a `TrivialTape` which is a trivial wrapper of `std::vector` or a  `DiskTape` which stores data on the disk. The default is `TrivialTape`, you can specify `--enable-disk-tape` when configure `ReverseAD` to enable `DiskTape`.



#### Derivative Evaluation Class

#### Checkpointing

#### Forward Types



