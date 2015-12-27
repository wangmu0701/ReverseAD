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
using ReverseAD::TrivialTrace;

#define N 2

int main(int argc, char** argv) {
  int size;
  int rank;
  ReverseAD::RMPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::cout << "rank : " << rank << " of " << size << std::endl;
  if (rank == 0) {
    ReverseAD::logging_on();
  }
  ReverseAD::trace_on<double>();
  if (rank == 0) {
    get_timing();
    adouble* x = new adouble[size * N];
    for (int i = 0; i < size * N; i++) {
      x[i] <<= (i+1);
    }
    for (int i = 1; i < size; i++) {
      RMPI_Send_ind(&(x[i*N-1]), N+1, i, 0, MPI_COMM_WORLD);
    }
    adouble yad = 0;
    for (int i = 0; i < N - 1; i++) {
      yad = yad + (1-x[i])*(1-x[i]) + 100*(x[i+1]-x[i]*x[i])*(x[i+1]-x[i]*x[i]);
    }
    std::cout << "yad.val = " << yad.getVal() << std::endl;
    adouble tad = 0;
    RMPI_Reduce(&yad, &tad, 1, RMPI_ADOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    double y;
    tad >>= y;
    double time = get_timing();
    std::cout << "y = " << y << " time_elapsed = " << time << std::endl;
  } else {
    adouble* x = new adouble[N + 1];
    RMPI_Recv_ind(x, N+1, 0, 0, MPI_COMM_WORLD);
    adouble yad = 0;
    for (int i = 0; i<N; i++) {
      yad = yad + (1-x[i])*(1-x[i]) + 100*(x[i+1]-x[i]*x[i])*(x[i+1]-x[i]*x[i]);
    }
    //adouble t1 = t0 * t0;
    std::cout << "yad.val = " << yad.getVal() << std::endl;
    RMPI_Reduce(&yad, NULL, 1, RMPI_ADOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  }
  std::shared_ptr<TrivialTrace<double>> trace = ReverseAD::trace_off<double>();
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
