#ifndef REVERSEAD_RMPI_WARPPER_SEND_RECV_H_
#define REVERSEAD_RMPI_WARPPER_SEND_RECV_H_

namespace ReverseAD {

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

} // namespace ReverseAD

#endif // REVERSEAD_RMPI_WRAPPER_SEND_RECV_H_
