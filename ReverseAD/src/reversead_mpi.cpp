#include "reversead/common/reversead_config.h"

#ifdef ENABLE_REVERSEAD_MPI
#include "mpi.h"

#include "reversead/activetype/base_active.hpp"
#include "reversead/common/reversead_type.hpp"
#include "reversead/common/reversead_mpi.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/util/temp_memory_allocator.hpp"

namespace ReverseAD {

  MPI_Datatype RMPI_ADOUBLE;

  extern void* global_trace;
  extern bool is_tracing;
  extern int rank;
  TempMemoryAllocator* temp_memory_allocator;
 
  void RMPI_Init(int* argc, char** argv[]) {
    MPI_Init(argc, argv);
    MPI_Type_contiguous(1, MPI_DOUBLE, &RMPI_ADOUBLE);
    MPI_Type_commit(&RMPI_ADOUBLE);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    temp_memory_allocator = new TempMemoryAllocator();
  }

  void RMPI_Finalize() {
    delete temp_memory_allocator;
    if (RMPI_ADOUBLE != MPI_DATATYPE_NULL) {MPI_Type_free(&RMPI_ADOUBLE);}
    MPI_Finalize();
  }

  void trace_put(const SendRecvInfo& sr_info) {
    ((TrivialTrace<double>*)global_trace)->put_sr_info(sr_info);
  }
  void trace_put_comm_loc(const locint& comm_loc) {
    ((TrivialTrace<double>*)global_trace)->put_comm_loc(comm_loc);
  }

  int RMPI_Send_ind(adouble* buf,
                    int count,
                    int dest,
                    int tag,
                    MPI_Comm comm) {
    int rc = MPI_SUCCESS;
    char* temp_buf = (char*)temp_memory_allocator->get_temp_memory(
      (sizeof(double) + sizeof(locint)) * count);
    double* send_val = (double*)(temp_buf);
    locint* send_loc = (locint*)(temp_buf + sizeof(double) * count);
    for (int i = 0; i < count; i++) {
      send_val[i] = buf[i].getVal();
      send_loc[i] = buf[i].getLoc();
    }
    rc = MPI_Send((void*)send_val, count, MPI_DOUBLE, dest, tag, comm);
    if (rc != MPI_SUCCESS) {
      log.fatal << "Sending vals in Send_ind error." << std::endl;
    }
    rc = MPI_Send((void*)send_loc, count, MPI_LOCINT, dest, tag, comm);
    if (rc != MPI_SUCCESS) {
      log.fatal << "Sending locs in Send_ind error." << std::endl;
    }
    temp_memory_allocator->return_temp_memory((void*)temp_buf);
    return rc;
  }

  int RMPI_Recv_ind(adouble* buf,
                    int count,
                    int src,
                    int tag,
                    MPI_Comm comm) {
    int rc= MPI_SUCCESS;
    char* temp_buf = (char*)temp_memory_allocator->get_temp_memory(
      (sizeof(double) + sizeof(locint)) * count);
    double* recv_val = (double*)(temp_buf);
    locint* recv_loc = (locint*)(temp_buf + sizeof(double) * count);
    rc = MPI_Recv((void*)recv_val, count, MPI_DOUBLE, src, tag, comm, MPI_STATUS_IGNORE);
    if (rc != MPI_SUCCESS) {
      log.fatal << "Recving vals in Send_ind error." << std::endl;
    }
    rc = MPI_Recv((void*)recv_loc, count, MPI_LOCINT, src, tag, comm, MPI_STATUS_IGNORE);
    if (rc != MPI_SUCCESS) {
      log.fatal << "Recving locs in Send_ind error." << std::endl;
    }
    for (int i = 0; i < count; i++) {
      buf[i].markRemoteInd(recv_val[i], recv_loc[i]);
    }
    ((TrivialTrace<double>*)global_trace)->increase_dummy_ind(count);
    temp_memory_allocator->return_temp_memory((void*)temp_buf);
    return rc;
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
      double* send_buf =
        (double*)temp_memory_allocator->get_temp_memory(sizeof(double) * count);
      for (int i = 0; i < count; i++) {
        dummy_dep[i] >>= send_buf[i];
      }

      if (is_tracing) {
        for (int i = 0; i < count; i++) {
          trace_put_comm_loc(dummy_dep[i].getLoc());
        }
        trace_put_o<double>(rmpi_send);
        SendRecvInfo info(COMM_RMPI_SEND, count, dest, tag, comm);
        trace_put(info);
        ((TrivialTrace<double>*)global_trace)->increase_dummy_dep(count);
      }
      rc = MPI_Send((void*)send_buf, count, MPI_DOUBLE, dest, tag, comm);
      temp_memory_allocator->return_temp_memory((void*)send_buf);
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
      double* recv_buf =
        (double*)temp_memory_allocator->get_temp_memory(sizeof(double) * count);
      rc = MPI_Recv((void*)recv_buf, count, MPI_DOUBLE, src, tag, comm, status);
      if (rc != MPI_SUCCESS) {return rc;}
      for (int i = 0; i < count; i++) {
        dummy_ind[i].markDummyInd(recv_buf[i]);
      }
      if (is_tracing) {
        for (int i = 0; i < count; i++) {
          trace_put_comm_loc(dummy_ind[i].getLoc());
        }
        trace_put_o<double>(rmpi_recv);
        SendRecvInfo info(COMM_RMPI_RECV, count, src, tag, comm);
        trace_put(info);
        ((TrivialTrace<double>*)global_trace)->increase_dummy_ind(count);
      }
      temp_memory_allocator->return_temp_memory((void*)recv_buf);
    } else {
      rc = MPI_Recv(buf, count, datatype, src, tag, comm, status);
    }
    return rc;
  }

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
                  log.warning << "Unsupported reduction op!" << std::endl;
                }
              }
            } else {
              rc = RMPI_Send(sendbuf, count, RMPI_ADOUBLE, peer, 0, comm);
            }
          }
        }
        if (rc != MPI_SUCCESS) {
          log.fatal << "RMPI_Reduce fail on : " << myid << std::endl;
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

#endif // ENABLE_REVERSEAD_MPI
