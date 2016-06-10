#include <cstdlib>

void symmetric_third_vector(
    size_t n, size_t t_size, size_t** t_ind, double* t_value,
    double* v, double** tv) {
  for(size_t i=0;i<n;i++) {
    for(size_t j=0;j<n;j++) {
      tv[i][j] = 0;
    }
  }
  for (size_t i=0;i<t_size;i++) {
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
void symmetric_matrix_vector(
    size_t n, size_t h_size, size_t** h_tind, double* h_value,
    double* v, double* hv) {
  for (size_t i=0; i<n; i++) {
    hv[i] = 0.0;
  }
  for (size_t i=0; i<h_size; i++) {
    if (h_tind[i][0] != h_tind[i][1]) {
      hv[h_tind[i][0]] += h_value[i] * v[h_tind[i][1]];
      hv[h_tind[i][1]] += h_value[i] * v[h_tind[i][0]];
    } else { // h_tind[i][0] == h_tind[i][1]
      hv[h_tind[i][0]] += h_value[i] * v[h_tind[i][1]];
    }
  }
}
