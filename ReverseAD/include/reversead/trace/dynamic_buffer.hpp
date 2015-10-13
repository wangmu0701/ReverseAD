#ifndef REVERSEAD_DYNAMIC_BUFFER_H_
#define REVERSEAD_DYNAMIC_BUFFER_H_

#define DYNAMIC_BUFFER_INIT_SIZE 10000
namespace ReverseAD {

template<typename T>
class DynamicBuffer{
 public:
  DynamicBuffer() {
    buff = new T[DYNAMIC_BUFFER_INIT_SIZE];
    curr_len = 0;
    max_len = DYNAMIC_BUFFER_INIT_SIZE;
  }

  ~DynamicBuffer() {
    delete[] buff;
  }

  T* use_size(size_t size) {
    T* ret = check_expand(size);
    curr_len += size;
    return ret;
  }

  T* use_temp_size(size_t size) {
    return check_expand(size);
  }

 private:
  T* check_expand(size_t size) {
    if (curr_len + size > max_len) {
      int new_len = max_len+(max_len>size?max_len:size);
      T* new_buff = new T[new_len];
      for(int i = 0; i < curr_len; i++) {
        new_buff[i] = buff[i];
      }
      delete[] buff;
      buff = new_buff;
      max_len = new_len;
    }
    return &buff[curr_len];
  }
  T* buff;
  int curr_len;
  int max_len;
};
}

#endif // REVERSE_AD_DYNAMIC_BUFFER_H_
