#ifndef TRIVIAL_ADJOINT_H_
#define TRIVIAL_ADJOINT_H_

#include <map>

#include "abstract_adjoint.hpp"

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
  Base&& get_and_erase(LocType x);
  Base& operator[] (LocType x);
  void erase(LocType x);
  int get_size() const;

  bool has_live(LocType target) const;
  int byte_size() const;
  void write_to_byte(char* buf) const;
  void debug() const;

  class enumerator : public AbstractAdjoint<LocType, Base>::enumerator {
   public:
    enumerator(const enumerator& other) {
      this->_data = other._data;
      this->_iter = other._iter;
    }
    ~enumerator() {};
    void operator = (const typename AbstractAdjoint<LocType, Base>::enumerator& other) {
      TrivialAdjoint<LocType, Base>::enumerator* dp =
        dynamic_cast<TrivialAdjoint<LocType, Base>::enumerator*>(&other);
      if (dp) {
        this->_data = dp->_data;
        this->_iter = dp->_iter;
      } else {
        std::cout << "TrivialAdjoint can not be assigned"
                  << " from another Adjoint impelmentation." << std::endl;
      }
    }
    bool has_next() {
      return _iter != _data.end();
    }
    bool get_next(LocType& x, Base& w) {
      x = _iter->first;
      w = _iter->second;
      _iter++;
      return _iter != _data->end();;
    }

   private:
    enumerator(const typename std::map<LocType, Base>::const_iterator* _data) {
      this->_data = _data;
      this->_iter = _data.begin();
    }

    const typename std::map<LocType, Base>* const _data;
    typename std::map<LocType, Base>::const_iterator _iter;
   
   friend class TrivialAdjoint<LocType, Base>;
  };

  typename TrivialAdjoint<LocType, Base>::enumerator get_enumerator();

 private:
  std::map<LocType, Base> _data;
};


template <typename LocType, typename Base>
typename TrivialAdjoint<LocType, Base>::enumerator TrivialAdjoint<LocType, Base>::get_enumerator() {
  TrivialAdjoint<LocType, Base>::enumerator enumtor(&_data);
  return enumtor;
}

template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint() {
  _data.clear();
}

// L-value c-tor
template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint(std::map<LocType, Base>& source) {
  std::cout << "TrivialAdjoint (L-ctor)" << std::endl;
  _data = source;
}

// R-value c-tor
template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::TrivialAdjoint(std::map<LocType, Base>&& source) {
  std::cout << "TrivialAdjoint (R-ctor)" << std::endl;
  _data = std::move(source);
}

// D-tor
template <typename LocType, typename Base>
TrivialAdjoint<LocType, Base>::~TrivialAdjoint() {
}


template <typename LocType, typename Base>
void TrivialAdjoint<LocType, Base>::increase(LocType x, Base v) {
  _data[x]+=v;
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

template <typename LocType, typename Base>
bool TrivialAdjoint<LocType, Base>::has_live(LocType target) const {
  return _data.find(target) != _data.end();
}

} // namespace ReverseAD

#endif // TRIVIAL_ADJOINT_H_
