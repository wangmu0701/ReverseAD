#ifndef REVERSE_AD_MPI_H_
#define REVERSE_AD_MPI_H_

#include <mpi.h>
#include <iostream>
#include "reversead_base.hpp"

#define COMM_RMPI_SEND 0
#define COMM_RMPI_RECV 1

namespace ReverseAD {
  extern MPI_Datatype RMPI_ADOUBLE;
  void RMPI_Init(int* argc, char** argv[]);
  void RMPI_Finalize();
 
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

  class SendRecvInfo {
   public:
    SendRecvInfo(int comm_op, int count, int peer, int tag, MPI_Comm comm,
      locint* locs) {
      this->comm_op = comm_op;
      this->count = count;
      this->peer = peer;
      this->tag = tag;
      this->comm = comm;
      this->locs = locs;
    }
    int comm_op;
    int count;
    int peer;
    int tag;
    MPI_Comm comm;
    locint* locs;
    friend std::ostream& operator << (std::ostream& os, const SendRecvInfo& info) {
      os << info.comm_op;
      return os;
    }
  };
} // namespace ReverseAD

#endif // REVERSE_AD_MPI_H_
