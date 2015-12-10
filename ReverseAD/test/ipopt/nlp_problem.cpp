#include <cassert>

#include "nlp_problem.hpp"

using namespace Ipopt;
using namespace ReverseAD;

//#define SHOW_DEBUG_INFO

#define N_SIZE 2

/* Constructor. */
NlpProblem::NlpProblem()
{}

NlpProblem::~NlpProblem()
{}

bool NlpProblem::get_nlp_info(Index& n, Index& m, Index& nnz_jac_g,
                         Index& nnz_h_lag, IndexStyleEnum& index_style)
{
  n = N_SIZE * 6;

  m = N_SIZE * 5;

  generate_tapes(n, m, nnz_jac_g, nnz_h_lag);

  // use the C style indexing (0-based)
  index_style = C_STYLE;

  return true;
}

bool NlpProblem::get_bounds_info(Index n, Number* x_l, Number* x_u,
                            Index m, Number* g_l, Number* g_u)
{
  // none of the variables have bounds
  for (Index i=0; i<n; i++) {
    if (i < N_SIZE * 2) {  // C, T
      x_l[i] = 0;
      x_u[i] = 1;
    } else if (i < N_SIZE * 3){ // U
      x_l[i] = 0;
      x_u[i] = 500;
    } else { // W, cb, tb
      x_l[i] = -1e20;
      x_u[i] = 1e20;
    }
  }

  // Set the bounds for the constraints
  for (Index i=0; i<m; i++) {
    g_l[i] = 0;
    g_u[i] = 0;
  }

  return true;
}

bool NlpProblem::get_starting_point(Index n, bool init_x, Number* x,
                               bool init_z, Number* z_L, Number* z_U,
                               Index m, bool init_lambda,
                               Number* lambda)
{
  // Here, we assume we only have starting values for x, if you code
  // your own NLP, you can provide starting values for the others if
  // you wish.
  assert(init_x == true);
  assert(init_z == false);
  assert(init_lambda == false);

  // set the starting point
  for (Index i=0; i<n; i++) {
    if (i < N_SIZE) { // C
      x[i] = 0.1367+((0.0944-0.1367)*i)/N_SIZE;
    } else if (i<N_SIZE*2) { // T
      x[i] = 0.7293+((0.7766-0.7293)*(i-N_SIZE))/N_SIZE;
    } else if (i<N_SIZE*3) { // U
      x[i] = 250;
    } else { // W, cb, tb
      x[i] = 1;
    }
  }

  return true;
}

template<class T> bool  NlpProblem::eval_obj(Index n, const T *x, T& obj_value)
{
  const T* c = x;
  const T* t = &x[N_SIZE];
  const T* u = &x[N_SIZE*2];
  obj_value = 0;
  for (Index i = 0; i<N_SIZE; i++) {
    obj_value = obj_value + 1000000*(0.0944-c[i])*(0.0944-c[i]);
    obj_value = obj_value + 2000*(0.7766-t[i])*(0.7766-t[i]);
    obj_value = obj_value + 0.001*(340 - u[i])*(340 - u[i]);
  }
  obj_value = obj_value / N_SIZE; 
  return true;
}

template<class T> bool  NlpProblem::eval_constraints(Index n, const T *x, Index m, T* g)
{
  const T* c = x;
  const T* t = &x[N_SIZE];
  const T* u = &x[N_SIZE*2];
  const T* w = &x[N_SIZE*3];
  const T* cb = &x[N_SIZE*4];
  const T* tb = &x[N_SIZE*5];

  for (Index i = 0; i<N_SIZE-i; i++) {
    g[i*2] = c[i+1]-c[i]-10*cb[i]/N_SIZE;
    g[i*2+1] = t[i+1]-t[i]-10*tb[i]/N_SIZE;
  }
  for (Index i = 0; i<N_SIZE; i++) {
    g[N_SIZE*2-2+i*3] = cb[i] - ((1-c[i])/20 - 300*exp(w[i])*c[i]);
    g[N_SIZE*2-2+i*3+1] = tb[i]-((0.3947-t[i])/20+300*exp(w[i])*c[i]-0.000195*u[i]*(t[i] - 0.3816)); 
    g[N_SIZE*2-2+i*3+2] = w[i]*t[i]+1;
  }
  g[N_SIZE*5-2] = c[0] - 0.1367;
  g[N_SIZE*5-1] = t[0] - 0.7293;
  return true;
}

//*************************************************************************
//
//
//         Nothing has to be changed below this point !!
//
//
//*************************************************************************


bool NlpProblem::eval_f(Index n, const Number* x, bool new_x, Number& obj_value)
{
  eval_obj(n,x,obj_value);

  return true;
}

bool NlpProblem::eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f)
{

//  gradient(tag_f,n,x,grad_f);
 
  for (int i=0; i<n; i++) {
    tmp_x[i] = x[i];
#ifdef SHOW_DEBUG_INFO
    std::cout << "x["<<i<<"] = " << x[i] << std::endl;
#endif
  }
  TrivialTrace<double>* new_trace =
    BaseFunctionReplay::replay_ind<double>(trace_f, tmp_x, n);
  BaseReverseAdjoint<double> adjoint(new_trace);
  adjoint.compute(n, 1);
  adjoint.retrieve_adjoint(&grad_f_val);
  for(int i=0; i<n; i++) {
    grad_f[i] = grad_f_val[0][i];
#ifdef SHOW_DEBUG_INFO
    std::cout << "G["<<i<<"] = "<< grad_f[i] << std::endl;
#endif
  }
  delete[] grad_f_val[0];
  delete[] grad_f_val;
  return true;
}

bool NlpProblem::eval_g(Index n, const Number* x, bool new_x, Index m, Number* g)
{

  eval_constraints(n,x,m,g);

  return true;
}

bool NlpProblem::eval_jac_g(Index n, const Number* x, bool new_x,
                       Index m, Index nele_jac, Index* iRow, Index *jCol,
                       Number* values)
{

  if (values == NULL) {
    // return the structure of the jacobian

    for(Index idx=0; idx<nnz_jac; idx++)
      {
	iRow[idx] = rind_g[idx];
	jCol[idx] = cind_g[idx];
#ifdef SHOW_DEBUG_INFO
        std::cout << "A["<<rind_g[idx]<<","<<cind_g[idx]<<"]" << std::endl;
#endif
      }
  }
  else {
    // return the values of the jacobian of the constraints
    delete[] rind_g;
    delete[] cind_g;
    delete[] jacval;
    for(int i=0; i<n; i++) {
      tmp_x[i] = x[i];
#ifdef SHOW_DEBUG_INFO
      std::cout << "x["<<i<<"] = "<<x[i] << std::endl;
#endif
    }
    TrivialTrace<double>* new_trace = 
      BaseFunctionReplay::replay_ind<double>(trace_g, tmp_x, n);
    BaseReverseAdjoint<Number> adjoint(new_trace);
    adjoint.compute(n, m);
    adjoint.retrieve_adjoint_sparse_format(&nnz_jac, &rind_g, &cind_g, &jacval); 
    for(Index idx=0; idx<nnz_jac; idx++)
      {
	values[idx] = jacval[idx];
#ifdef SHOW_DEBUG_INFO
        std::cout << "A["<<rind_g[idx]<<","<<cind_g[idx]<<"] = " << jacval[idx] << std::endl;
#endif
      }
  }

  return true;

}

bool NlpProblem::eval_h(Index n, const Number* x, bool new_x,
                   Number obj_factor, Index m, const Number* lambda,
                   bool new_lambda, Index nele_hess, Index* iRow,
                   Index* jCol, Number* values)
{

  if (values == NULL) {
    // return the structure. This is a symmetric matrix, fill the lower left
    // triangle only.

/*
    for(Index idx=0; idx<nnz_L[0]; idx++)
      {
	iRow[idx] = cind_L[0][idx];
	jCol[idx] = rind_L[0][idx];
      }
*/
    Index idx = 0;
    for(Index i = 0; i<n; i++) {
      for (Index j=0; j<=i; j++) {
        iRow[idx] = i;
        jCol[idx] = j;
        idx++;
      }
    }
  }
  else {
    // return the values. This is a symmetric matrix, fill the lower left
    // triangle only

    delete[] nnz_L;
    delete[] cind_L[0];
    delete[] cind_L;
    delete[] rind_L[0];
    delete[] rind_L;
    delete[] hessval[0];
    delete[] hessval;

#ifdef SHOW_DEBUG_INFO
    std::cout << "obj_factor = " << obj_factor << std::endl;
#endif
    obj_lam[0] = obj_factor;
    for(Index idx = 0; idx<m ; idx++) {
      obj_lam[1+idx] = lambda[idx];
#ifdef SHOW_DEBUG_INFO
      std::cout << "lambda["<<idx<<"] = " << lambda[idx] << std::endl; 
#endif
    }
    for(Index idx = 0; idx<n; idx++) {
      tmp_x[idx] = x[idx];
#ifdef SHOW_DEBUG_INFO
      std::cout << "x["<<idx<<"] = "<<tmp_x[idx]<< std::endl;
#endif
    }

    TrivialTrace<double>* new_trace = 
      BaseFunctionReplay::replay<double>(trace_L, 
        tmp_x, n, obj_lam, m+1);
    BaseReverseHessian<double> hessian(new_trace);
    hessian.compute(n, 1);
    hessian.retrieve_hessian_sparse_format(&nnz_L, &cind_L, &rind_L, &hessval);

    Index l = 0;
    for(Index i = 0; i < (n*(n+1))/2; i++) {
      values[i] = 0;
    }
    for(Index i = 0; i <nnz_L[0] ; i++)
      {
          l = (cind_L[0][i]*cind_L[0][i]+1)/2 + rind_L[0][i];
          values[l] = hessval[0][i];
#ifdef SHOW_DEBUG_INFO
        std::cout << "H["<<cind_L[0][i]<<","<<rind_L[0][i]<<"] = " << hessval[0][i] << std::endl;
#endif
      }
  }
  return true;

}

void NlpProblem::finalize_solution(SolverReturn status,
                              Index n, const Number* x, const Number* z_L, const Number* z_U,
                              Index m, const Number* g, const Number* lambda,
                              Number obj_value,
			      const IpoptData* ip_data,
			      IpoptCalculatedQuantities* ip_cq)
{

  for(int i = 0; i < n; i++) {
    printf("x[%d] = %.5f\n", i, x[i]);
  }
  printf("\n\nObjective value\n");
  printf("f(x*) = %e\n", obj_value);

// memory deallocation of ADOL-C variables

  delete[] obj_lam;

  delete[] rind_g;
  delete[] cind_g;
  delete[] jacval;

  delete[] nnz_L;
  delete[] cind_L[0];
  delete[] cind_L;
  delete[] rind_L[0];
  delete[] rind_L;
  delete[] hessval[0];
  delete[] hessval;

}


//***************    ADOL-C part ***********************************

void NlpProblem::generate_tapes(Index n, Index m, Index& nnz_jac_g, Index& nnz_h_lag)
{
  Number *xp    = new double[n];
  Number *lamp  = new double[m];
  Number *zl    = new double[m];
  Number *zu    = new double[m];

  adouble *xa   = new adouble[n];
  adouble *g    = new adouble[m];
  double *lam   = new double[m];
  double sig;
  adouble obj_value;
  
  double dummy;

  int i,j,k,l,ii;
  tmp_x = new double[n];
  obj_lam   = new double[m+1];

  get_starting_point(n, 1, xp, 0, zl, zu, m, 0, lamp);

  trace_on<double>();
    
    for(Index idx=0;idx<n;idx++)
      xa[idx] <<= xp[idx];

    eval_obj(n,xa,obj_value);

    obj_value >>= dummy;

  trace_f = trace_off<double>();
  
  trace_on<double>();
    
    for(Index idx=0;idx<n;idx++)
      xa[idx] <<= xp[idx];

    eval_constraints(n,xa,m,g);


    for(Index idx=0;idx<m;idx++)
      g[idx] >>= dummy;

  trace_g = trace_off<double>();

  trace_on<double>();
    
    for(Index idx=0;idx<n;idx++)
      xa[idx] <<= xp[idx];
    for(Index idx=0;idx<m;idx++)
      lam[idx] = 1.0;
    sig = 1.0;

    eval_obj(n,xa,obj_value);

    obj_value = obj_value * adouble::markParam(sig);
    eval_constraints(n,xa,m,g);
 
    for(Index idx=0;idx<m;idx++)
      obj_value = obj_value + g[idx]*adouble::markParam(lam[idx]);

    obj_value >>= dummy;

  trace_L = trace_off<double>();

  rind_g = NULL; 
  cind_g = NULL;
  rind_L = NULL;
  cind_L = NULL;
  jacval = NULL;
  hessval = NULL;

  BaseReverseAdjoint<double> adjoint(trace_g);
  adjoint.compute(n, m);
  adjoint.retrieve_adjoint_sparse_format(&nnz_jac, &rind_g, &cind_g, &jacval);

  nnz_jac_g = nnz_jac;
#ifdef SHOW_DEBUG_INFO
  for (int i = 0; i < nnz_jac; i++) {
    std::cout << "A[" << rind_g[i] << "," << cind_g[i] << " ] = "
              << jacval[i] << std::endl;
  }
#endif  
  BaseReverseHessian<double> hessian(trace_L);
  hessian.compute(n, 1);
  hessian.retrieve_hessian_sparse_format(&nnz_L, &rind_L, &cind_L, &hessval);

#ifdef SHOW_DEBUG_INFO
  for (int i = 0; i < nnz_L[0]; i++) {
    std::cout << "H[" << rind_L[0][i] << "," << cind_L[0][i] << " ] = "
              << hessval[0][i] << std::endl;
  }
#endif

  nnz_h_lag = (n*(n+1)) / 2;
  
  delete[] lam;
  delete[] g;
  delete[] xa;
  delete[] zu;
  delete[] zl;
  delete[] lamp;
  delete[] xp;
}
