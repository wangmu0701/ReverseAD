#include <sys/time.h>
#include <mpi.h>
#include <iostream>
#include "reversead/reversead.hpp"

using ReverseAD::RMPI_Send;
using ReverseAD::RMPI_Recv;
using ReverseAD::RMPI_Reduce;
using ReverseAD::RMPI_ADOUBLE;
using ReverseAD::BaseMpiReverseHessian;
using ReverseAD::get_timing;

#define N 400

#define PI 3.1416926

inline adouble get_eulid_dist(
    adouble x1, adouble y1, adouble z1,
    adouble x2, adouble y2, adouble z2) {
  return sqrt((z1-z2)*(z1-z2) + (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
adouble compute_thomson_function(adouble* x, adouble* p, int rank, int size) {
  adouble ret = 0;
  for (int i=0; i< N*size; i++) {
    adouble t = cos(x[i*2]);
    p[i*3] = sin(x[i*2]);
    p[i*3+1] = t * cos(x[i*2+1]);
    p[i*3+2] = t * sin(x[i*2+1]);
  }
  for(int i=rank*N; i<(rank+1)*N; i++) {
    for(int j=0; j<size*N; j++) {
      if (i!=j) {
      ret = ret + 1.0 / get_eulid_dist(p[i*3], p[i*3+1], p[i*3+2],
                                       p[j*3], p[j*3+1], p[j*3+2]);
      }
    }
  }
  return ret;
}
//parallel thomson problem
int main(int argc, char** argv) {
  int size;
  int rank;
  ReverseAD::RMPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::cout << "rank : " << rank << " of " << size << std::endl;
  if (rank == 0) {
    //ReverseAD::logging_on();
  }
  ReverseAD::trace_on();
  adouble* x = new adouble[size*N*2];
  adouble* p = new adouble[size*N*3];
  adouble tad = 0;
  if (rank == 0) {
    get_timing();
    srand(12345);
    for (int i = 0; i < size * N; i++) {
      x[i*2] <<= (double)rand();
      x[i*2+1] <<= (double)rand();
    }
    for (int i = 1; i < size; i++) {
      RMPI_Send_ind(&(x[0]), size*N*2, i, 0, MPI_COMM_WORLD);
    }
    tad = compute_thomson_function(x, p, rank, size);
    adouble yad = 0;
    RMPI_Reduce(&tad, &yad, 1, RMPI_ADOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    double y;
    yad >>= y;
    double time = get_timing();
    std::cout << "y = " << y << " time_elapsed = " << time << std::endl;
  } else {
    RMPI_Recv_ind(x, size*N*2, 0, 0, MPI_COMM_WORLD);
    tad = compute_thomson_function(x, p, rank, size);
    RMPI_Reduce(&tad, NULL, 1, RMPI_ADOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  }
  ReverseAD::TrivialTrace* trace = ReverseAD::trace_off();
  BaseMpiReverseHessian<double> hessian(trace);
  struct timeval tv1, tv2;
  if (rank == 0) {
    gettimeofday(&tv1, NULL);
  }
  hessian.compute_mpi();
  if (rank == 0) {
    gettimeofday(&tv2, NULL);
    double time_elapsed = (tv2.tv_sec - tv1.tv_sec)
                        + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000;
    std::cout << "Total Hessian Time = " << time_elapsed << std::endl;
  }
  ReverseAD::RMPI_Finalize();
}
