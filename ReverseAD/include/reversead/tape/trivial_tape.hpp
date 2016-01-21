#ifndef TRIVIAL_TAPE_H_
#define TRIVIAL_TAPE_H_


#include <vector>
#include <iostream>
#include "reversead/tape/abstract_tape.hpp"
#include "reversead/util/logger.hpp"

#define INITIAL_TAPE_VECTOR_SIZE 65536

namespace ReverseAD {

template <typename Type>
class TrivialTape : public AbstractTape<Type> {
 public:
  TrivialTape() = default;
  TrivialTape(const TrivialTape&) = default;
  TrivialTape(TrivialTape&&) = default;
  TrivialTape<Type>& operator=(const TrivialTape&) = default;
  TrivialTape<Type>& operator=(TrivialTape&&) = default;
  ~TrivialTape() = default;

  void init_taping();
  void put(Type data);
  void end_taping();
  int size();
  
  void init_forward();
  void end_forward();
  bool has_next_f();
  Type get_next_f();

  void rewrite_curr_f(Type data);

  void init_reverse();
  void end_reverse();
  bool has_next_r();
  Type get_next_r();

  void dump_tape();
  void dump_tape(Logger& logger);

 private:
  std::vector<Type> data_;
  typename std::vector<Type>::const_iterator forward_iter;
  typename std::vector<Type>::const_reverse_iterator reverse_iter;
};

template <typename Type>
void TrivialTape<Type>::put(Type data) {
  data_.push_back(data);
}
template <typename Type>
void TrivialTape<Type>::init_taping() {
  data_.reserve(INITIAL_TAPE_VECTOR_SIZE);
}

template <typename Type>
void TrivialTape<Type>::end_taping() {
}

template <typename Type>
int TrivialTape<Type>::size() {
  return data_.size();
}

template <typename Type>
void TrivialTape<Type>::init_forward() {
  forward_iter = data_.begin();
}

template <typename Type>
void TrivialTape<Type>::end_forward() {
  forward_iter = data_.end();
}

template <typename Type>
bool TrivialTape<Type>::has_next_f() {
  return (forward_iter != data_.end());
}

template <typename Type>
Type TrivialTape<Type>::get_next_f() {
  Type retval = *forward_iter;
  forward_iter++;
  return retval;
}

template <typename Type>
void TrivialTape<Type>::rewrite_curr_f(Type data) {
  typename std::vector<Type>::iterator prev_iter = forward_iter - 1;
  *prev_iter = data;
}

template <typename Type>
void TrivialTape<Type>::init_reverse() {
  reverse_iter = data_.rbegin();
}

template <typename Type>
void TrivialTape<Type>::end_reverse() {
  reverse_iter = data_.rend();
}

template <typename Type>
bool TrivialTape<Type>::has_next_r() {
  return (reverse_iter != data_.rend());
}

template <typename Type>
Type TrivialTape<Type>::get_next_r() {
  Type retval = *reverse_iter;
  reverse_iter++;
  return retval;
}

template <typename Type>
void TrivialTape<Type>::dump_tape() {
  std::cout << "[" << data_.size() << "]";
  for(size_t i = 0; i < data_.size(); i++) {
    std::cout << " " << data_[i];
  }
  std::cout << std::endl;
}

template <typename Type>
void TrivialTape<Type>::dump_tape(Logger& logger) {
  logger << "[" << data_.size() << "]";
  for(size_t i = 0; i < data_.size(); i++) {
    logger << " " << data_[i];
  }
  logger << std::endl;
}

} // namespace ReverseAD

#endif // TRIVIAL_TAPE_H_
