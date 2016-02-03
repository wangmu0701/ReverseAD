#ifndef REVERSEAD_TYPE_H_
#define REVERSEAD_TYPE_H_

#include <cstdint>
#include <iostream>

#include "reversead/common/reversead_config.h"

#ifdef ENABLE_REVERSEAD_MPI
#include "mpi.h"

#define MPI_LOCINT MPI_LONG_LONG

#define COMM_RMPI_SEND 0
#define COMM_RMPI_RECV 1

#define MAX_LOC 0xfffffffffffffffful
#define RANK_SHIFT 16
#define RANK_BASE 0x000000000000fffful
#define BASE_LOC 0x800000000000ul

#else // no ENABLE_REVERSE_MPI

#define MAX_LOC 0xffffffff
#define BASE_LOC 0x00800000

#endif // ENABLE_REVERSE_MPI

#define NULL_LOC 0

namespace ReverseAD {

  typedef uint8_t opbyte;
#ifdef ENABLE_REVERSEAD_MPI
  typedef uint64_t locint;
#else
  typedef uint32_t locint;
#endif // ENABLE_REVERSEAD_MPI

#ifdef ENABLE_REVERSEAD_MPI
  class SendRecvInfo {
   public:
    SendRecvInfo(int comm_op, int count, int peer, int tag, MPI_Comm comm) {
      this->comm_op = comm_op;
      this->count = count;
      this->peer = peer;
      this->tag = tag;
      this->comm = comm;
    }
    int comm_op;
    int count;
    int peer;
    int tag;
    MPI_Comm comm;
    friend std::ostream& operator<<(std::ostream& os,const SendRecvInfo& info) {
      if (info.comm_op == COMM_RMPI_SEND) {
        os << "sending " << info.count << " numbers to " << info.peer << std::endl;
      } else if (info.comm_op == COMM_RMPI_RECV) {
        os << "recving " << info.count << " numbers from " << info.peer << std::endl;
      }
      return os;
    }
  };
#else // ENABLE_REVERSEAD_MPI
  class SendRecvInfo {
    friend std::ostream& operator<<(std::ostream& os,const SendRecvInfo& info) {
      return os;
    }
  };
#endif // ENABLE_REVERSEAD_MPI

}; // namespace ReverseAD

#endif // REVERSEAD_TYPE_H_

