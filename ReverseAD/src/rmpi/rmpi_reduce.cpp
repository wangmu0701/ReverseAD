#include "mpi.h"

#include "reversead/activetype/base_active.hpp"
#include "reversead/common/reversead_type.hpp"
#include "reversead/rmpi/reversead_mpi.hpp"
#include "reversead/rmpi/rmpi_send_recv.hpp"

namespace ReverseAD {

  extern MPI_Datatype RMPI_ADOUBLE;
  extern int rank;

  int RMPI_Reduce(void* sendbuf,
                  void* recvbuf,
                  int count,
                  MPI_Datatype datatype,
                  MPI_Op op,
                  int root,
                  MPI_Comm comm) {
    int rc = MPI_SUCCESS;
    if (datatype == RMPI_ADOUBLE) {
      adouble* t_buf = new adouble[count];
      adouble* s_buf = (adouble*)sendbuf;
      int size;
      int myid;
      MPI_Comm_size(comm, &size);
      MPI_Comm_rank(comm, &myid);
      int p = 1;
      int mask, peer;
      while(p < size) {
        mask = p - 1;
        if ((myid & mask) == 0) {
          peer = myid ^ p;
          if (peer < size) {
            if ((myid & p) == 0) {
              rc = RMPI_Recv((void*)t_buf, count, RMPI_ADOUBLE, peer, 0, comm,
                             MPI_STATUS_IGNORE);
              for (int i = 0; i < count; i++) {
                if (op == MPI_SUM) {
                  s_buf[i] = s_buf[i] + t_buf[i];
                } else if (op == MPI_PROD) {
                  s_buf[i] = s_buf[i] * t_buf[i];
                } else {
                  logger.warning << "Unsupported reduction op!" << std::endl;
                }
              }
            } else {
              rc = RMPI_Send(sendbuf, count, RMPI_ADOUBLE, peer, 0, comm);
            }
          }
        }
        if (rc != MPI_SUCCESS) {
          logger.fatal << "RMPI_Reduce fail on : " << myid << std::endl;
        }
        p = p * 2;
      }
      if (myid == 0) {
        adouble* r_buf = (adouble*) recvbuf;
        for (int i = 0; i < count; i++) {
          r_buf[i] = s_buf[i];
        }
      }
      delete[] t_buf;
    } else {
      rc = MPI_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm);
    }
    return rc;
  }
} // namespace ReverseAD
