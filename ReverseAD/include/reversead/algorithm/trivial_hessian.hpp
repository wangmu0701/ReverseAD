#ifndef TRIVIAL_HESSIAN_H_
#define TRIVIAL_HESSIAN_H_

#include <map>

#include "reversead/algorithm/abstract_serializable.hpp"
#include "reversead/algorithm/trivial_adjoint.hpp"

namespace ReverseAD {

template <typename LocType, typename Base>
class TrivialHessian : public AbstractSerializable {
 public:
  TrivialHessian();
  TrivialHessian(char* buf);

  ~TrivialHessian();
  
  TrivialAdjoint<LocType, Base> get_and_erase(const LocType& x);
  TrivialAdjoint<LocType, Base>& operator [] (LocType x);

  void clear();
  void increase(const LocType& x, const LocType& y, const Base& w) {
    if (IsZero(w)) {
      return;
    }
    if (x >= y) {
      _data[x][y] += w;
    } else {
      _data[y][x] += w;
    }
  }

  // serializable
  int get_size() const;
  int byte_size() const;
  void write_to_byte(char*) const;
  void debug() const;
  void debug(Logger&) const;

  class enumerator {
   public:
    bool has_next() {
      return _iter != _data->end();
    }
    bool get_next(LocType& x, LocType& y, Base& w) {
      x = _iter->first;
      _enum.get_next(y, w);
      find_next();
      return _iter != _data->end();
    }
    
    enumerator() {} 
    void operator = (const enumerator& other) {
      this->_data = other._data;
      this->_iter = other._iter;
      this->_enum = other._enum;
    }
    enumerator(const enumerator& other) : _data(other._data) {
      this->_iter = other._iter;
      this->_enum = other._enum;
    }

   private:
    enumerator(const typename std::map<LocType, TrivialAdjoint<LocType, Base> >* const data) {
      this->_data = data;
      this->_iter = data->begin();
      if (_iter != _data->end()) {
        this->_enum = _iter->second.get_enumerator();
        find_next();
      }
    }
    void find_next() {
      while(_iter != _data->end() && !_enum.has_next()) {
        ++_iter;
        if (_iter != _data->end()) {
          _enum = _iter->second.get_enumerator();
        }
      }
    }
    void swap(enumerator& lhs, enumerator& rhs) {
      using std::swap;
      swap(lhs._data, rhs._data);
      swap(lhs._iter, rhs._iter);
      swap(lhs._enum, rhs._enum);
    }
    const typename std::map<LocType, TrivialAdjoint<LocType, Base> >* _data;
    typename std::map<LocType, TrivialAdjoint<LocType, Base> >::const_iterator _iter;
    typename TrivialAdjoint<LocType, Base>::enumerator _enum;

    friend class TrivialHessian<LocType, Base>;
  };
  enumerator get_enumerator() const;
 private:
  std::map<LocType, TrivialAdjoint<LocType, Base> > _data;

};


template <typename LocType, typename Base>
typename TrivialHessian<LocType, Base>::enumerator
  TrivialHessian<LocType, Base>::get_enumerator() const {
  TrivialHessian<LocType, Base>::enumerator ret(&_data);
  return ret;
}

template <typename LocType, typename Base>
TrivialHessian<LocType, Base>::TrivialHessian() {
  _data.clear();
}

template <typename LocType, typename Base>
void TrivialHessian<LocType, Base>::clear() {
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
void TrivialHessian<LocType, Base>::debug(Logger& logger) const {
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
      logger << "H[" << t_iter->first << "," <<y << "] = "
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
