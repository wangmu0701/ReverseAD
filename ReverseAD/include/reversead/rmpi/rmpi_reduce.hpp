#ifndef REVERSEAD_RMPI_REDUCE_H_
#define REVERSEAD_RMPI_REDUCE_H_

namespace ReverseAD {

  int RMPI_Reduce(void* sendbuf,
                  void* recvbuf,
                  int count,
                  MPI_Datatype datatype,
                  MPI_Op op,
                  int root,
                  MPI_Comm comm);

} // namespace ReverseAD

#endif // REVERSEAD_RMPI_REDUCE_H_
