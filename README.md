Road map towards release:
1) fill in more operators. (must have but can wait)

2) Define a clear interface for the trace (computation and communication). They are independent so they deserve to be treated separately.

3) The memory assign for storing loc indices should be managed more properly. Probably move it to communication trace?

4) Refactor the code so that computing first order, second order, (or even higher) and mpi with the same derivative table and interface.

4.1) It makes more sence to let the adjoint/hessian structure to decide if symmetry is respected. So an increase(loc, loc, Base) function call is needed.

5) Think what do we need to support forward-over-reverse mode?

```c++
template<typename Base> void foo(Base x);
void foo(double x);

foo(5.0) // will call foo(double);
foo<double>(5.0) // will call foo<double>(5.0)
```
Which basically the intermediate values are of type Base, and the const values are of type double.

Plans:
(2) -> (3) -> (4.1) -> (4) -> (5) -> (1)

(4) is not trivial.
(5) is the hard part.
Good luck.
