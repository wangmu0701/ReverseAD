#ifndef TRIVIAL_ADJOINT_H_
#define TRIVIAL_ADJOINT_H_

#include <map>

#include "VectorGraph.h"

namespace ReverseAD {

template <typename LocType, typename Base>
class TrivialAdjoint : public AbstractAdjoint<LocType, Base> {
 public:
  TrivialAdjoint();
  TrivialAdjoint(char* buf);
  TrivialAdjoint(std::map<LocType, Base>& source);
  TrivialAdjoint(std::map<LocType, Base>&& source);

  ~TrivialAdjoint();

  void increase(LocType x, Base v);
  Base get_and_erase(LocType x);
  Base get(LocType x);
  int get_size() const;

  bool has_live(LocType target) const;
  int byte_size() const;
  void write_to_byte(char* buf) const;
  void debug() const;

  class iterator : public AbstractAdjoint<LocType, Base>::iterator {
   public:
    iterator(TrivialAdjoint<LocType>::iterator* c_iter):_data(c_iter->_data),
        iter(c_iter->iter) {};
    iterator(std::map<LocType, Base>* _data_p):_data(_data_p) {};
    virtual ~iterator();
    bool reset();
    bool get_next(LocType& x, Base& w);
    typename TrivialAdjoint<LocType, Base>::iterator* copy_iter();
   private:
    const std::map<LocType, Base>* const _data;
    typename std::map<LocType, Base>::const_iterator iter;
  };

  typename VectorGraph<T>::iterator* get_iterator();

 private:
  std::map<LocType, Base> data;
};

template <typename LocType, typename Base>
typename TrivialAdjoint<LocType, Base>::iterator* TrivialAdjoint<LocType, Base>::iterator::copy_iter() {
  return new TrivialAdjoint<LocType, Base>::iterator(this);
}

template <typename LocType, typename Base>
typename VectorGraph<T>::iterator* TrivialAdjoint<LocType, Base>::get_iterator() {
  typename VectorGraph<T>::iterator* ret = new TrivialAdjoint<LocType, Base>::iterator(&data);
  return ret;
}

template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::iterator::~iterator() {

}

template <typename LocType, typename Base>
bool TrivialAdjoint<LocType, Base>::iterator::reset() {
  iter = _data->begin();
  if (iter == _data->end()) {
    return false;
  }
  return true;
}

template <typename LocType, typename Base>
bool TrivialAdjoint<LocType, Base>::iterator::get_next(T&x, double& w){
  x = iter->first;
  w = iter->second;
  ++iter;
  if (iter == _data->end()) {
    return false;
  }
  return true;
}

template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint() {
  data.clear();
}

// L-value c-tor
template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint(std::map<T, double>& source) {
  std::cout << "VectorGraph (L-ctor)" << std::endl;
  data = source;
}

// R-value c-tor
template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint(std::map<T, double>&& source) {
//  std::cout << "VectorGraph (R-ctor)" << std::endl;
  data = std::move(source);
}

// D-tor
template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::~TrivialAdjoint() {
  data.clear();
}


template <typename LocType, typename Base>
void TrivialAdjoint<LocType, Base>::increase(LocType x, Base v) {
  data[x]+=v;
}

template <typename LocType, typename Base>
Base TrivialAdjoint<LocType, Base>::get_and_erase(LocType x) {
  Base ret = std::move(data[x]);
  data.erase(x);
  return ret;
}

template <typename LocType, typename Base>
Base TrivialAdjoint<LocType, Base>::get(T x) {
  return data[x];
}

template <typename LocType, typename Base>
int TrivialAdjoint<LocType, Base>::get_size() const {
  return data.size();
}

template <typename LocType, typename Base>
void TrivialAdjoint<LocType, Base>::debug() const {
  typename std::map<LocType, Base>::const_iterator t_iter;
  t_iter = data.begin();
  while(t_iter != data.end()) {
    std::cout << "A[" << t_iter->first << "]=" << t_iter->second << std::endl;
    ++t_iter;
  }
}

template <typename LocType, typename Base>
int TrivialAdjoint<LocType, Base>::byte_size() const {
  return data.size() * (sizeof(LocType) + sizeof(Base)) + sizeof(int);
}

template <typename LocType, typename Base>
void TrivialAdjoint<LocType, Base>::write_to_byte(char* buf) const {
  char* p = buf;
  *((int*)p) = data.size();
  p += sizeof(int);
 typename std::map<LocType, Base>::const_iterator t_iter;
  t_iter = data.begin();
  while(t_iter != data.end()) {
    *((LocType*)p) = t_iter->first;
    p += sizeof(T);
    *((Base*)p) = t_iter->second;
    p += sizeof(Base);
    ++t_iter;
  }
}

template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint(char* buf) {
  data.clear();
  char* p = buf;
  LocType loc;
  Base w;
  int size = *((int*)p);
  p += sizeof(int);
  for(int i = 0; i < size; i++) {
    loc = *((LocType*)p);
    p += sizeof(LocType);
    w = *((Base*)p);
    p += sizeof(Base);
    data[loc] = w;
  }
}

template <typename LocType, typename Base>
bool TrivialAdjoint<LocType, Base>::has_live(LocType target) const {
  if (data.find(target) != data.end()) {
    return true;
  }
  return false;
}

} // namespace ReverseAD

#endif // TRIVIAL_ADJOINT_H_
