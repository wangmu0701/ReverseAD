#include <memory>
#include <iostream>
#include "reversead/reversead.hpp"
#include "reversead/forwardtype/single_forward.hpp"
#include "reversead/driver/forward_over_reverse.hpp"

using ReverseAD::adouble;
using ReverseAD::BaseActive;
using ReverseAD::TrivialTrace;
using ReverseAD::SingleForward;
using ReverseAD::trace_on;
using ReverseAD::trace_off;
using ReverseAD::BaseFunctionReplay;
using ReverseAD::BaseReverseAdjoint;
using ReverseAD::BaseReverseHessian;
using ReverseAD::BaseReverseThird;
using ReverseAD::DerivativeTensor;

double myEps = 1.E-10;
void symmetric_third_vector(int n, int t_size, int** t_ind, double* t_value,
    double* v, double** tv) {
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      tv[i][j] = 0;
    }
  }
  for (int i=0;i<t_size;i++) {
    // we have orders t_ind[i][0] >=t_ind[i][1] >=t_ind[i][2];
    if (t_ind[i][0] != t_ind[i][1]) {
      if (t_ind[i][1] != t_ind[i][2]) { // [0]!=[1]!=[2]
        tv[t_ind[i][0]][t_ind[i][1]] += t_value[i] * v[t_ind[i][2]];
        tv[t_ind[i][0]][t_ind[i][2]] += t_value[i] * v[t_ind[i][1]];
        tv[t_ind[i][1]][t_ind[i][2]] += t_value[i] * v[t_ind[i][0]];
      } else { // [0]!=[1]=[2]
        tv[t_ind[i][0]][t_ind[i][1]] += t_value[i] * v[t_ind[i][2]];
        tv[t_ind[i][1]][t_ind[i][2]] += t_value[i] * v[t_ind[i][0]];
      }
    } else {
      if (t_ind[i][1] != t_ind[i][2]) { // [0]=[1]!=[2]
        tv[t_ind[i][0]][t_ind[i][1]] += t_value[i] * v[t_ind[i][2]];
        tv[t_ind[i][0]][t_ind[i][2]] += t_value[i] * v[t_ind[i][1]];
      } else { // [0]=[1]=[2]
        tv[t_ind[i][0]][t_ind[i][1]] += t_value[i] * v[t_ind[i][2]];
      }
    }
  }
}
void check_forward_over_second(
    std::shared_ptr<TrivialTrace<double>> trace,
    int ind_num, int dep_num,
    double* ind_init_values,
    double* adjoint_init_values) {
  BaseReverseThird<double> third(trace);
  DerivativeTensor<int, double> tensor = third.compute(ind_num, dep_num);
  int t_size;
  int** t_tind;
  double* t_value;
  tensor.get_internal_coordinate_list(0, 3, &t_size, &t_tind, &t_value);
//  std::cout << "t_size = " << t_size << std::endl;
//  for (int i=0; i<t_size; i++) {
//    std::cout<<"T["<<t_tind[i][0]<<", "<<t_tind[i][1]
//             <<", "<<t_tind[i][2] <<"] = "<<t_value[i]<<std::endl;
//  }
  double** tv = new double*[ind_num];
  double** ctv = new double*[ind_num];
  for (int i=0; i<ind_num; i++) {
    tv[i] = new double[ind_num];
    ctv[i] = new double[ind_num];
  }
  forward_over_second(trace, ind_num, dep_num,
      ind_init_values, adjoint_init_values, &tv);
  symmetric_third_vector(ind_num, t_size, t_tind, t_value, adjoint_init_values, ctv);
  for (int i=0; i<ind_num; i++) {
    for(int j=0;j<ind_num; j++) {
      //std::cout << "tv["<<i<<", "<<j<<"] = "<<tv[i][j]<<std::endl;
      //std::cout << "ctv["<<i<<", "<<j<<"] = "<<ctv[i][j]<<std::endl;
      if (fabs(tv[i][j] - ctv[i][j]) > myEps) {
        std::cout << "forward over second error!" << std::endl;
        exit(-1);
      }
    }
  }
  std::cout << "forward over second OK!" << std::endl;
  for (int i=0; i<ind_num; i++) {
    delete[] tv[i];
    delete[] ctv[i];
  }
  delete[] tv;
  delete[] ctv; 
}
void symmetric_matrix_vector(int n, int h_size, int** h_tind,
    double* h_value, double* v, double* hv) {
  for (int i=0; i<n; i++) {
    hv[i] = 0.0;
  }
  for (int i=0; i<h_size; i++) {
    if (h_tind[i][0] != h_tind[i][1]) {
      hv[h_tind[i][0]] += h_value[i] * v[h_tind[i][1]];
      hv[h_tind[i][1]] += h_value[i] * v[h_tind[i][0]];
    } else { // h_tind[i][0] == h_tind[i][1]
      hv[h_tind[i][0]] += h_value[i] * v[h_tind[i][1]];
    }
  }
}
void check_forward_over_reverse(
    std::shared_ptr<TrivialTrace<double>> trace,
    int ind_num, int dep_num,
    double* ind_init_values,
    double* adjoint_init_values) {
  BaseReverseHessian<double> hessian(trace);
  DerivativeTensor<int, double> tensor = hessian.compute(ind_num, dep_num);
  int h_size;
  int** h_tind;
  double* h_value;
  tensor.get_internal_coordinate_list(0, 2, &h_size, &h_tind, &h_value);
//  std::cout << "h_size = " << h_size << std::endl;
//  for (int i=0; i<h_size; i++) {
//    std::cout<<"H["<<h_tind[i][0]<<", "<<h_tind[i][1]<<"] = "<<h_value[i]<<std::endl;
//  }
  double* hv = new double[ind_num];
  double* chv = new double[ind_num];
  forward_over_reverse(trace, ind_num, dep_num,
      ind_init_values, adjoint_init_values, &hv);
  symmetric_matrix_vector(ind_num, h_size, h_tind, h_value, adjoint_init_values, chv);
  for (int i=0; i<ind_num; i++) {
    //std::cout << "hv["<<i<<"] = "<<hv[i]<<std::endl;
    //std::cout << "chv["<<i<<"] = "<<chv[i]<<std::endl;
    if (fabs(hv[i] - chv[i]) > myEps) {
      std::cout << "forward over reverse error!" << std::endl;
      exit(-1);
    }
  }
  std::cout << "forward over reverse OK!" << std::endl;
  delete[] hv;
  delete[] chv; 
}

template <typename T>
std::shared_ptr<TrivialTrace<T>> foo(T a, T b, T c) {
  typedef BaseActive<T> AT;
  T y;
  AT af, bf, cf, yf;
  ReverseAD::trace_on<T>();
  af <<= a;
  bf <<= b;
  cf <<= c;
  yf = af * bf * cf;
  yf >>= y;
  return ReverseAD::trace_off<T>();
}
template <typename T>
std::shared_ptr<TrivialTrace<T>> bar(T a, T b, T c) {
  typedef BaseActive<T> AT;
  T y;
  AT af, bf, cf, yf;
  ReverseAD::trace_on<T>();
  af <<= a;
  bf <<= b;
  cf <<= c;
  yf = af * bf;
  yf += sin(cf);
  yf *= cos(af);
  yf /= log(bf);
  yf >>= y;
  return ReverseAD::trace_off<T>();
}
int main() {
  std::shared_ptr<TrivialTrace<double>> trace = foo<double>(1,2,3);
  double x[3] = {1, 2, 3};
  double a[3] = {10, 20, 30};
  check_forward_over_reverse(trace, 3, 1, x, a);
  check_forward_over_second(trace, 3, 1, x, a);
  trace = bar<double>(1, 2, 3);
  check_forward_over_reverse(trace, 3, 1, x, a);
  check_forward_over_second(trace, 3, 1, x, a);
  return 0;
}
