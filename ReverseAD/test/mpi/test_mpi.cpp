#include <mpi.h>
#include <iostream>
#include "reversead/reversead.hpp"
using ReverseAD::RMPI_Send;
using ReverseAD::RMPI_Recv;
using ReverseAD::RMPI_ADOUBLE;
using ReverseAD::BaseMpiReverseHessian;

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
  ReverseAD::trace_on();
  if (rank == 0) {
    adouble v0;
    v0 <<= 2.0;
    RMPI_Send(&v0, 1, RMPI_ADOUBLE, 1, 0, MPI_COMM_WORLD);
    adouble v1;
    RMPI_Recv(&v1, 1, RMPI_ADOUBLE, 1, 0, MPI_COMM_WORLD, NULL);
    adouble v2 = v1 * v1;
    adouble v3 = v0 * v2;
    double y;
    v3 >>= y;
    std::cout << "y = " << y << std::endl;
  } else {
    adouble t0;
    RMPI_Recv(&t0, 1, RMPI_ADOUBLE, 0, 0, MPI_COMM_WORLD, NULL);
    std::cout << "t0 = " << t0.getVal() << std::endl;
    adouble t1 = t0 * t0;
    RMPI_Send(&t1, 1, RMPI_ADOUBLE, 0, 0, MPI_COMM_WORLD);
  }
  ReverseAD::TrivialTrace* trace = ReverseAD::trace_off();
  BaseMpiReverseHessian<double> hessian(trace);
  hessian.compute_mpi();

  ReverseAD::RMPI_Finalize();
}
