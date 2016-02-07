/*==========================================================
 * An interface of ReverseAD with MATLAB
 * This routine evaluates the Hessian of the function
 * implemented in obj_func().
 * hessian.cpp
 *
 * Usage :
 *
 *     [y, H] = hessian(x); 
 *
 * Inputs :
 *
 *     x : independent variables
 *
 * Outputs :
 *
 *     y : dependent variables
 *
 *     H : the Hessian
 *
 * Example :
 *     [y, H] = hessian([2 3 4]);
 *      y = [24]
 *      H = [0 4 3; 4 0 2; 3 2 0]
 *
 *========================================================*/

#include "mex.h"
#include "reversead/reversead.hpp"

using namespace ReverseAD;

template <typename T>
T obj_func(T* x, mwSize x_num) {
/***

  Fill in the implement of the objective function here

***/
  T y = 1;
  for (int i = 0; i < x_num; i++) {
    y *= x[i];
  }
  return y;
}


/***
  YOU DO NOT NEED TO CHANGE ANYTHING BELOW 
***/

void hessian(double* x, mwSize x_num, double *y, double* H)
{
    mwSize i, j;
    adouble* xad = new adouble[x_num];
    trace_on<double>();
    for (i = 0; i < x_num; i++) {
      xad[i] <<= x[i]; 
    }
    adouble yad = obj_func<adouble>(xad, x_num);
    yad >>= y[0];
    std::shared_ptr<TrivialTrace<double>> trace = trace_off<double>();
    BaseReverseHessian<double> hessian(trace);
    std::shared_ptr<DerivativeTensor<int, double>> tensor =
      hessian.compute(x_num, 1).get_tensor();
    hessian.clear();
    int size;
    int** tind;
    double* values;
    tensor->get_internal_coordinate_list(0, 2, &size, &tind, &values);
    for (i = 0; i < size; i++) {
      if (tind[i][0] != tind[i][1]) {
        H[tind[i][0] * x_num + tind[i][1]] = values[i];
        H[tind[i][1] * x_num + tind[i][0]] = values[i];
      } else {
        H[tind[i][0] * x_num + tind[i][1]] = values[i];
      }
    }

    delete[] xad;
}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    /* check for proper number of arguments */
    if(nrhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:RADHessian:nrhs","One inputs required.");
    }
    if(nlhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:RADHessian:nlhs","Two output required.");
    }
    
    if( !mxIsDouble(prhs[0]) || 
         mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("MyToolbox:RADHessian:notDouble",
                          "First input values must be type double.");
    }
    if(mxGetM(prhs[0])!=1 && mxGetN(prhs[0])!=1) {
        mexErrMsgIdAndTxt("MyToolbox:RADHessian:notVector",
                          "First input values must be a vector.");
    }

    
    /* get the value of the scalar input  */
    double* x_values = mxGetPr(prhs[0]);
    size_t x_num = mxGetM(prhs[0]);
    if (x_num == 1) {x_num = mxGetN(prhs[0]);}

    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    plhs[1] = mxCreateDoubleMatrix((mwSize)x_num,(mwSize)x_num,mxREAL);

    /* get a pointer to the real data in the output matrix */
    double* y_values = mxGetPr(plhs[0]);
    double* H = mxGetPr(plhs[1]);

    /* call the computational routine */
    hessian(x_values, (mwSize)x_num, y_values, H);
}
