#ifndef TRIVIAL_ADJOINT_H_
#define TRIVIAL_ADJOINT_H_

#include <map>

#include "reversead/logger.hpp"
#include "abstract_serializable.hpp"

namespace ReverseAD {

template <typename LocType, typename Base>
class TrivialAdjoint : public AbstractSerializable {
 public:
  TrivialAdjoint();
  TrivialAdjoint(char* buf);
  TrivialAdjoint(const TrivialAdjoint<LocType, Base>& other);
  TrivialAdjoint(TrivialAdjoint<LocType, Base>&& other);

  ~TrivialAdjoint();

  Base&& get_and_erase(LocType x);
  Base& operator[] (LocType x);
  void erase(LocType x);

  // serializable
  void debug() const;
  void debug(Logger&) const;
  int get_size() const;
  int byte_size() const;
  void write_to_byte(char* buf) const;

  class enumerator {
   public:
    enumerator() {};
    enumerator(const enumerator& other): _data(other._data) {
      this->_iter = other._iter;
    }
    ~enumerator() {};
    void operator = (const enumerator& other) {
      this->_data = other._data;
      this->_iter = other._iter;
    }
    bool has_next() {
      return _iter != _data->end();
    }
    bool get_next(LocType& x, Base& w) {
      x = _iter->first;
      w = _iter->second;
      _iter++;
      return _iter != _data->end();;
    }

   private:
    enumerator(const typename std::map<LocType, Base>* const data)
      : _data(data) {
      this->_iter = data->begin();
    }

    const typename std::map<LocType, Base>* _data;
    typename std::map<LocType, Base>::const_iterator _iter;
   
   friend class TrivialAdjoint<LocType, Base>;
  };

  typename TrivialAdjoint<LocType, Base>::enumerator get_enumerator() const;

 private:
  std::map<LocType, Base> _data;
};


template <typename LocType, typename Base>
typename TrivialAdjoint<LocType, Base>::enumerator TrivialAdjoint<LocType, Base>::get_enumerator() const {
  TrivialAdjoint<LocType, Base>::enumerator enumtor(&_data);
  return enumtor;
}

template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint() {
  _data.clear();
}

// L-value c-tor
template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint(
  const TrivialAdjoint<LocType, Base>& other) {
  //std::cout << "TrivialAdjoint (L-ctor)"<< this <<" = " << &other << std::endl;
  _data = other._data;
}

// R-value c-tor
template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint(
  TrivialAdjoint<LocType, Base>&& other) {
  //std::cout << "TrivialAdjoint (R-ctor)"<< this <<" = " << &other << std::endl;
  _data = std::move(other._data);
}

// D-tor
template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::~TrivialAdjoint() {

}

template <typename LocType, typename Base>
Base&& TrivialAdjoint<LocType, Base>::get_and_erase(LocType x) {
  Base ret = std::move(_data[x]);
  _data.erase(x);
  return std::move(ret);
}

template <typename LocType, typename Base>
void TrivialAdjoint<LocType, Base>::erase(LocType x) {
  _data.erase(x);
}

template <typename LocType, typename Base>
Base& TrivialAdjoint<LocType, Base>::operator [] (LocType x) {
  return _data[x];
}

template <typename LocType, typename Base>
int TrivialAdjoint<LocType, Base>::get_size() const {
  return _data.size();
}

template <typename LocType, typename Base>
void TrivialAdjoint<LocType, Base>::debug() const {
  typename std::map<LocType, Base>::const_iterator t_iter;
  t_iter = _data.begin();
  while(t_iter != _data.end()) {
    std::cout << "A[" << t_iter->first << "]=" << t_iter->second << std::endl;
    ++t_iter;
  }
}

template <typename LocType, typename Base>
void TrivialAdjoint<LocType, Base>::debug(Logger& logger) const {
  typename std::map<LocType, Base>::const_iterator t_iter;
  t_iter = _data.begin();
  while(t_iter != _data.end()) {
    logger << "A[" << t_iter->first << "]=" << t_iter->second << std::endl;
    ++t_iter;
  }
}

template <typename LocType, typename Base>
int TrivialAdjoint<LocType, Base>::byte_size() const {
  return _data.size() * (sizeof(LocType) + sizeof(Base)) + sizeof(int);
}

template <typename LocType, typename Base>
void TrivialAdjoint<LocType, Base>::write_to_byte(char* buf) const {
  char* p = buf;
  *((int*)p) = _data.size();
  p += sizeof(int);
  typename std::map<LocType, Base>::const_iterator t_iter;
  t_iter = _data.begin();
  while(t_iter != _data.end()) {
    *((LocType*)p) = t_iter->first;
    p += sizeof(LocType);
    *((Base*)p) = t_iter->second;
    p += sizeof(Base);
    ++t_iter;
  }
}

template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint(char* buf) {
  _data.clear();
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
    _data[loc] = w;
  }
}

} // namespace ReverseAD

#endif // TRIVIAL_ADJOINT_H_
