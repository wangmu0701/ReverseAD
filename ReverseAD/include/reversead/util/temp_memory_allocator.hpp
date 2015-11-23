#ifndef REVERSEAD_TEMP_MEMORY_ALLOCATOR_H_
#define REVERSEAD_TEMP_MEMORY_ALLOCATOR_H_

namespace ReverseAD {

class TempMemoryAllocator {
 public:
  TempMemoryAllocator();
  ~TempMemoryAllocator();
  void* get_temp_memory(size_t size);
  void return_temp_memory(void* temp_buf);
 private:
  void* buf;
  size_t curr_buf_size;
  bool in_use;
};

} // namespace ReverseAD

#endif // REVERSEAD_TEMP_MEMORY_ALLOCATOR_H_
