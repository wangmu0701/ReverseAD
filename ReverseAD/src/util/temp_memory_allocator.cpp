#include <cstdlib>
#include <iostream>

#include "reversead/util/temp_memory_allocator.hpp"

#define TEMP_MEMORY_ALLOCATOR_INITIAL_SIZE 1024

namespace ReverseAD {

TempMemoryAllocator::TempMemoryAllocator() {
  this->buf = malloc(TEMP_MEMORY_ALLOCATOR_INITIAL_SIZE);
  this->curr_buf_size = 0;
  this->in_use = false;
}

TempMemoryAllocator::~TempMemoryAllocator() {
  if (in_use) {
    std::cerr << "Trying to free in_use temp memory, bug in code?" << std::endl;
  }
  curr_buf_size = 0;
  free(buf);
}

void* TempMemoryAllocator::get_temp_memory(size_t size) {
  if (in_use) {
    return nullptr;
  }
  if (curr_buf_size < size) {
    free(buf);
    buf = malloc(size);
    curr_buf_size = size;
  }
  in_use = true;
  return buf;
}

void TempMemoryAllocator::return_temp_memory(void* temp_buf) {
  in_use = false;
}

} // namespace ReverseAD
