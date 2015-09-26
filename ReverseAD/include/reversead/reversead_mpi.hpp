#ifndef REVERSE_AD_MPI_H_
#define REVERSE_AD_MPI_H_

#include <mpi.h>
#include <iostream>
#include "reversead_base.hpp"
#include "reversead/tape/abstract_tape.hpp"

#define COMM_RMPI_SEND 0
#define COMM_RMPI_RECV 1

namespace ReverseAD {

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
    friend std::ostream& operator<<(std::ostream& os,const SendRecvInfo& info) {
      if (info.comm_op == COMM_RMPI_SEND) {
        os << "sending " << info.count << " numbers to " << info.peer << std::endl;
      } else if (info.comm_op == COMM_RMPI_RECV) {
        os << "recving " << info.count << " numbers from " << info.peer << std::endl;
      }
      return os;
    }
  };

  extern MPI_Datatype RMPI_ADOUBLE;

  void RMPI_Init(int* argc, char** argv[]);
  void RMPI_Finalize();
  
  void trace_put(const SendRecvInfo& sr_info);
  AbstractTape<SendRecvInfo>* RMPI_get_comm_tape();

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

} // namespace ReverseAD

#endif // REVERSE_AD_MPI_H_
