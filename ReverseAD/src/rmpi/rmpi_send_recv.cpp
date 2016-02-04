#include "mpi.h"

#include "reversead/activetype/base_active.hpp"
#include "reversead/common/reversead_type.hpp"
#include "reversead/rmpi/reversead_mpi.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/util/temp_memory_allocator.hpp"

namespace ReverseAD {

  extern MPI_Datatype RMPI_ADOUBLE;

  extern void* global_trace;

  extern TempMemoryAllocator* temp_memory_allocator;

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
      logger.fatal << "Sending vals in Send_ind error." << std::endl;
    }
    rc = MPI_Send((void*)send_loc, count, MPI_LOCINT, dest, tag, comm);
    if (rc != MPI_SUCCESS) {
      logger.fatal << "Sending locs in Send_ind error." << std::endl;
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
      logger.fatal << "Recving vals in Send_ind error." << std::endl;
    }
    rc = MPI_Recv((void*)recv_loc, count, MPI_LOCINT, src, tag, comm, MPI_STATUS_IGNORE);
    if (rc != MPI_SUCCESS) {
      logger.fatal << "Recving locs in Send_ind error." << std::endl;
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

      if (global_trace) {
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
      if (global_trace) {
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

} // namespace ReverseAD

