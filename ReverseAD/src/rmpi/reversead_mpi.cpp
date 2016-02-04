#include "reversead/common/reversead_config.h"

#include "mpi.h"

#include "reversead/activetype/base_active.hpp"
#include "reversead/common/reversead_type.hpp"
#include "reversead/rmpi/reversead_mpi.hpp"
#include "reversead/rmpi/rmpi_wrapper.hpp"
#include "reversead/trace/trivial_trace.hpp"
#include "reversead/util/temp_memory_allocator.hpp"

namespace ReverseAD {

  MPI_Datatype RMPI_ADOUBLE;

  extern void* global_trace;
  TempMemoryAllocator* temp_memory_allocator;
 
  void RMPI_Init(int* argc, char** argv[]) {
    MPI_Init(argc, argv);
    MPI_Type_contiguous(1, MPI_DOUBLE, &RMPI_ADOUBLE);
    MPI_Type_commit(&RMPI_ADOUBLE);
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
} // namespace ReverseAD
