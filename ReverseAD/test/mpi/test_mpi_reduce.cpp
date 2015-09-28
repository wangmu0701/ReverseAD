#include <mpi.h>
#include <iostream>
#include "reversead/reversead.hpp"
#include "reversead/reversead_mpi.hpp"
#include "reversead/algorithm/base_mpi_reverse_hessian.hpp"

using ReverseAD::RMPI_Send;
using ReverseAD::RMPI_Recv;
using ReverseAD::RMPI_Reduce;
using ReverseAD::RMPI_ADOUBLE;
using ReverseAD::BaseMpiReverseHessian;
using ReverseAD::RMPI_get_comm_tape;

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
    adouble* x = new adouble[size];
    for (int i = 0; i < size; i++) {
      x[i] <<= (i+1);
      if (i != 0) {
        RMPI_Send(&(x[i]), 1, RMPI_ADOUBLE, i, 0, MPI_COMM_WORLD);
      }
    }
    adouble yad;
    RMPI_Reduce(&x[0], &yad, 1, RMPI_ADOUBLE, MPI_PROD, 0, MPI_COMM_WORLD);
    double y;
    yad >>= y;
    std::cout << "y = " << y << std::endl;
  } else {
    adouble t;
    RMPI_Recv(&t, 1, RMPI_ADOUBLE, 0, 0, MPI_COMM_WORLD, NULL);
    std::cout << "t = " << t.getVal() << std::endl;
    //adouble t1 = t0 * t0;
    RMPI_Reduce(&t, NULL, 1, RMPI_ADOUBLE, MPI_PROD, 0, MPI_COMM_WORLD);
  }
  ReverseAD::TrivialTrace* trace = ReverseAD::trace_off();
  BaseMpiReverseHessian<double> hessian(trace, RMPI_get_comm_tape());
  hessian.compute_mpi();

  ReverseAD::RMPI_Finalize();
}
