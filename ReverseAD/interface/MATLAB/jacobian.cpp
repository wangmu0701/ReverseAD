/*==========================================================
 * An interface of ReverseAD with MATLAB
 * This routine evaluates the Jacobian of the function
 * implemented in obj_func().
 * jacobian.cpp
 *
 * Usage :
 *
 *     [y, J] = jacobian(x, int32(m)); 
 *
 * Inputs :
 *
 *     x : independent variables
 *
 *     m : number of dependent variables
 *
 * Outputs :
 *
 *     y : dependent variables
 *
 *     J : the Jacobian
 *
 * Example :
 *     [y, J] = jacobian([2 3 4], int32(2));
 *      y = [9; 24]
 *      J = [1 1 1; 12 8 6]
 *
 *========================================================*/

#include "mex.h"
#include "reversead/reversead.hpp"

using namespace ReverseAD;

template <typename T>
void obj_func(T* x, mwSize x_num, T* y, mwSize y_num) {
/***

  Fill in the implement of the objective function here

***/
  y[0] = 0;
  y[1] = 1;
  for (int i = 0; i < x_num; i++) {
    y[0] += x[i];
    y[1] *= x[i];
  }
}



/***
  YOU DO NOT NEED TO CHANGE ANYTHING BELOW 
***/

void jacobian(double* x, mwSize x_num, double *y, mwSize y_num, double* J)
{
    mwSize i, j;
    adouble* xad = new adouble[x_num];
    adouble* yad = new adouble[y_num];
    trace_on<double>();
    for (i = 0; i < x_num; i++) {
      xad[i] <<= x[i]; 
    }
    obj_func<adouble>(xad, x_num, yad, y_num);
    for (i = 0; i < y_num; i++) {
      yad[i] >>= y[i];
    }
    std::shared_ptr<TrivialTrace<double>> trace = trace_off<double>();
    BaseReverseAdjoint<double> adjoint(trace);
    std::shared_ptr<DerivativeTensor<int, double>> tensor =
      adjoint.compute(x_num, y_num).get_tensor();
    adjoint.clear();
    int size;
    int** tind;
    double* values;
    for (i = 0; i < y_num; i++) {
      tensor->get_internal_coordinate_list(i, 1, &size, &tind, &values);
      for (j = 0; j < x_num; j++) {
        J[j * y_num + i] = 0;
      }
      for (j = 0; j < size; j++) {
        J[tind[j][0] * y_num + i] = values[j];
      }
    }

    delete[] xad;
    delete[] yad;
}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    /* check for proper number of arguments */
    if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:RADJacobian:nrhs","Two inputs required.");
    }
    if(nlhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:RADJacobian:nlhs","Two output required.");
    }
    
    if( !mxIsDouble(prhs[0]) || 
         mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("MyToolbox:RADJacobian:notDouble",
                          "First input values must be type double.");
    }
    if(mxGetM(prhs[0])!=1 && mxGetN(prhs[0])!=1) {
        mexErrMsgIdAndTxt("MyToolbox:RADJacobian:notVector",
                          "First input values must be a vector.");
    }
    if(  (!mxIsInt64(prhs[1]) && 
         !mxIsInt32(prhs[1]) &&
         !mxIsInt16(prhs[1])) ||
         mxGetNumberOfElements(prhs[1])!=1 ) {
        mexErrMsgIdAndTxt("MyToolbox:RADJacobian:notScalar",
                          "Second input must be an positive integer scalar.");
    }
    if (mxGetScalar(prhs[1]) <= 0) {
      mexErrMsgIdAndTxt("MyToolbox:RADJacobian:notPositive",
                        "Second input must be an positive integer scalar.");
    }

    
    /* get the value of the scalar input  */
    double* x_values = mxGetPr(prhs[0]);
    size_t x_num = mxGetM(prhs[0]);
    if (x_num == 1) {x_num = mxGetN(prhs[0]);}
    size_t y_num = mxGetScalar(prhs[1]);

    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix((mwSize)y_num, 1, mxREAL);
    plhs[1] = mxCreateDoubleMatrix((mwSize)y_num,(mwSize)x_num,mxREAL);

    /* get a pointer to the real data in the output matrix */
    double* y_values = mxGetPr(plhs[0]);
    double* J = mxGetPr(plhs[1]);

    /* call the computational routine */
    jacobian(x_values, (mwSize)x_num, y_values, (mwSize)y_num, J);
}
