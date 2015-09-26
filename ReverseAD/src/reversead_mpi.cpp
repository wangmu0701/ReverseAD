
#include "reversead/base_active.hpp"
#include "reversead/reversead_base.hpp"
#include "reversead/reversead_mpi.hpp"
#include "reversead/tape/trivial_tape.hpp"

namespace ReverseAD {

  MPI_Datatype RMPI_ADOUBLE;
  extern bool is_tracing;
  extern int rank;
 
  TrivialTape<SendRecvInfo>* comm_tape; 
  void RMPI_Init(int* argc, char** argv[]) {
    MPI_Init(argc, argv);
    MPI_Type_contiguous(1, MPI_DOUBLE, &RMPI_ADOUBLE);
    MPI_Type_commit(&RMPI_ADOUBLE);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    comm_tape = new TrivialTape<SendRecvInfo>();
  }

  void RMPI_Finalize() {
    if (RMPI_ADOUBLE != MPI_DATATYPE_NULL) {MPI_Type_free(&RMPI_ADOUBLE);}
    MPI_Finalize();
  }

  void trace_put(const SendRecvInfo& sr_info) {
    comm_tape->put(sr_info);
  }
  AbstractTape<SendRecvInfo>* RMPI_get_comm_tape() {
    return comm_tape;
  }

  int RMPI_Send(void* buf,
                int count,
                MPI_Datatype datatype,
                int dest,
                int tag,
                MPI_Comm comm) {
    int rc = 0;
    if (datatype == RMPI_ADOUBLE) {
      adouble* dummy_dep = (adouble*)buf;
      double* send_buf = new double[count];
      locint* locs = new locint[count];
      for (int i = 0; i < count; i++) {
        dummy_dep[i] >>= send_buf[i];
        locs[i] = dummy_dep[i].getLoc();
      }
      if (is_tracing) {
        trace_put(rmpi_send);
        SendRecvInfo info(COMM_RMPI_SEND, count, dest, tag, comm, locs);
        trace_put(info);
      } else {
        delete locs;
      }
      rc = MPI_Send((void*)send_buf, count, MPI_DOUBLE, dest, tag, comm);
      delete send_buf;
    } else {
      rc = MPI_Send(buf, count, datatype, dest, tag, comm);
    }
    return rc;
  }

  int RMPI_Recv(void* buf,
                int count,
                MPI_Datatype datatype,
                int src,
                int tag,
                MPI_Comm comm,
                MPI_Status* status) {
    int rc = 0;
    if (datatype == RMPI_ADOUBLE) {
      adouble* dummy_ind = (adouble*) buf;
      double* recv_buf = new double[count];
      locint* locs = new locint[count];
      rc = MPI_Recv((void*)recv_buf, count, MPI_DOUBLE, src, tag, comm, status);
      if (rc != MPI_SUCCESS) {return rc;}
      for (int i = 0; i < count; i++) {
        dummy_ind[i].markDummyInd(recv_buf[i]);
        locs[i] = dummy_ind[i].getLoc();
      }
      if (is_tracing) {
        trace_put(rmpi_recv);
        SendRecvInfo info(COMM_RMPI_RECV, count, src, tag, comm, locs);
        trace_put(info);
      } else {
        delete locs;
      }
    } else {
      rc = MPI_Recv(buf, count, datatype, src, tag, comm, status);
    }
    return rc;
  }
} // namespace ReverseAD
