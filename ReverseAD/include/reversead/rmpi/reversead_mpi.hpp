#ifndef REVERSEAD_MPI_H_
#define REVERSEAD_MPI_H_

#include "reversead/common/reversead_config.h"

#ifdef ENABLE_REVERSEAD_MPI
#include "mpi.h"

#include "reversead/common/reversead_type.hpp"

namespace ReverseAD {

  extern MPI_Datatype RMPI_ADOUBLE;

  void RMPI_Init(int* argc, char** argv[]);
  void RMPI_Finalize();
  
  void trace_put(const SendRecvInfo& sr_info);
  void trace_put_comm_loc(const locint& comm_loc);

} // namespace ReverseAD

#endif // ENABLE_REVERSEAD_MPI

#endif // REVERSEAD_MPI_H_
