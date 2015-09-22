#ifndef TRIVIAL_HESSIAN_H_
#define TRIVIAL_HESSIAN_H_

#include <map>

#include "abstract_serializable.hpp"
#include "trivial_adjoint.hpp"

namespace ReverseAD {

template <typename LocType, typename Base>
class TrivialHessian : public AbstractSerializable {
 public:
  TrivialHessian();
  TrivialHessian(char* buf);

  ~TrivialHessian();
  
  TrivialAdjoint<LocType, Base> get_and_erase(const LocType& x);
  TrivialAdjoint<LocType, Base>& operator [] (LocType x);

  // serializable
  int get_size() const;
  int byte_size() const;
  void write_to_byte(char*) const;
  void debug() const;

 private:
  std::map<LocType, TrivialAdjoint<LocType, Base> > _data;

};

template <typename LocType, typename Base>
TrivialHessian<LocType, Base>::TrivialHessian() {
  _data.clear();
}

template <typename LocType, typename Base>
TrivialHessian<LocType, Base>::~TrivialHessian() {
  _data.clear();
}

template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base> TrivialHessian<LocType, Base>::get_and_erase(
  const LocType& x) {
  TrivialAdjoint<LocType, Base> ret(std::move(_data[x]));
  _data.erase(x);
  return std::move(ret);
}

template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>& TrivialHessian<LocType, Base>::operator [] (LocType x) {
  return _data[x];
}

template <typename LocType, typename Base>
int TrivialHessian<LocType, Base>::get_size() const {
  int size_count = 0;
  typename std::map<LocType, TrivialAdjoint<LocType, Base> >::const_iterator t_iter;
  t_iter = _data.begin();
  while (t_iter != _data.end()) {
    size_count += t_iter->second.get_size();
    ++t_iter;
  }
  return size_count;
}

template <typename LocType, typename Base>
void TrivialHessian<LocType, Base>::debug() const {
  typename std::map<LocType, TrivialAdjoint<LocType, Base> >::const_iterator
    t_iter;
  t_iter = _data.begin();
  while (t_iter != _data.end()) {
    typename TrivialAdjoint<LocType, Base>::enumerator t_enum =
      t_iter->second.get_enumerator();
    bool has_next = t_enum.has_next();
    LocType y;
    Base w;
    while (has_next) {
      has_next = t_enum.get_next(y, w);
      std::cout << "H[" << t_iter->first << "," <<y << "] = "
                << w << std::endl;
    }
    ++t_iter;
  }
}

template <typename LocType, typename Base>
int TrivialHessian<LocType, Base>::byte_size() const {
  return get_size() * (sizeof(double) + sizeof(LocType) * 2) + sizeof(int);
}

template <typename LocType, typename Base>
void TrivialHessian<LocType, Base>::write_to_byte(char* buf) const {
  char* p = buf;
  *((int*)p) = get_size();
  p += sizeof(int);
  typename std::map<LocType, TrivialAdjoint<LocType, Base> >::const_iterator t_iter;
  t_iter = _data.begin();
  while (t_iter != _data.end()) {
    typename TrivialAdjoint<LocType, Base>::enumerator t_enum =
      t_iter->second.get_enumerator();
    bool has_next = t_enum.has_next();
    LocType y;
    Base w;
    while(has_next) {
      has_next = t_enum.get_next(y, w);
      *((LocType*)p) = t_iter->first;
      p += sizeof(LocType);
      *((LocType*)p) = y;
      p += sizeof(LocType);
      *((Base*)p) = w;
      p += sizeof(Base);
    }
    ++t_iter;
  }
}

template <typename LocType, typename Base>
TrivialHessian<LocType, Base>::TrivialHessian(char* buf) {
  _data.clear();
  char* p = buf;
  int size = 0;
  LocType x;
  LocType y;
  Base w;
  size = *((int*)p);
  p += sizeof(int);
  for(int i = 0; i < size; i++) {
    x = *((LocType*)p);
    p += sizeof(LocType);
    y = *((LocType*)p);
    p += sizeof(LocType);
    w = *((Base*)p);
    p += sizeof(Base);
    _data[x][y] = w;
  }
}

} // namespace ReverseAD

#endif // Trivial_Hessian_H_
