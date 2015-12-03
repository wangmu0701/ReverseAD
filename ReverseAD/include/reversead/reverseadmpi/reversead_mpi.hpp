#ifndef REVERSEAD_MPI_H_
#define REVERSEAD_MPI_H_

#include "reversead/common/reversead_config.h"

#ifdef ENABLE_REVERSEAD_MPI
#include <mpi.h>

#include "reversead/activetype/base_active.hpp"

namespace ReverseAD {
  extern MPI_Datatype RMPI_ADOUBLE;

  void RMPI_Init(int* argc, char** argv[]);
  void RMPI_Finalize();
  
  void trace_put(const SendRecvInfo& sr_info);
  void trace_put_comm_loc(const locint& comm_loc);

  int RMPI_Send_ind(adouble* buf,
                    int count,
                    int dest,
                    int tag,
                    MPI_Comm comm);

  int RMPI_Recv_ind(adouble* buf,
                    int count,
                    int src,
                    int tag,
                    MPI_Comm comm);

  int RMPI_Send(void* buf,
                int count,
                MPI_Datatype datatype,
                int dest,
                int tag,
                MPI_Comm comm);

  int RMPI_Recv(void* buf,
                int count,
                MPI_Datatype datatype,
                int src,
                int tag,
                MPI_Comm comm,
                MPI_Status* status);

  int RMPI_Reduce(void* sendbuf,
                  void* recvbuf,
                  int count,
                  MPI_Datatype datatype,
                  MPI_Op op,
                  int root,
                  MPI_Comm comm);
} // namespace ReverseAD

#endif // ENABLE_REVERSEAD_MPI

#endif // REVERSEAD_MPI_H_
