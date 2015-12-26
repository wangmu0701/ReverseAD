#ifndef TRIVIAL_THRID_H_
#define TRIVIAL_THIRD_H_

#include <map>

#include "reversead/algorithm/abstract_serializable.hpp"
#include "reversead/algorithm/trivial_adjoint.hpp"
#include "reversead/algorithm/trivial_hessian.hpp"

namespace ReverseAD {

template <typename LocType, typename Base>
class TrivialThird : public AbstractSerializable {
 public:
  TrivialThird();
  TrivialThird(char* buf);

  ~TrivialThird();
  
  TrivialHessian<LocType, Base> get_and_erase(const LocType& x);

  void clear();
  void increase(const LocType& x, const LocType& y, const LocType& z, 
                const Base& w) {
    if (x >= y) {
      if (z >= x) { // z>=x>=y
        _data[z][x][y] += w;
      } else if (z >= y) { // x>z>=y
        _data[x][z][y] += w;
      } else { // x>=y>z;
        _data[x][y][z] += w;
      }
    } else {
      if (z >= y) { // z>=y>x
        _data[z][y][x] += w;
      } else if (z >= x) { // y>z>=x
        _data[y][z][x] += w;
      } else { // y>x>z
        _data[y][x][z] += w;
      }
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
    bool get_next(LocType& x, LocType& y, LocType& z, Base& w) {
      x = _iter->first;
      _enum.get_next(y, z, w);
      find_next();
      return _iter != _data->end();
    }
    
   private:
    enumerator(const typename std::map<LocType, TrivialHessian<LocType, Base> >* const data) {
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
    const typename std::map<LocType, TrivialHessian<LocType, Base> >* _data;
    typename std::map<LocType, TrivialHessian<LocType, Base> >::const_iterator _iter;
    typename TrivialHessian<LocType, Base>::enumerator _enum;

    friend class TrivialThird<LocType, Base>;
  };
  enumerator get_enumerator() const;
 private:
  std::map<LocType, TrivialHessian<LocType, Base> > _data;

};


template <typename LocType, typename Base>
typename TrivialThird<LocType, Base>::enumerator
  TrivialThird<LocType, Base>::get_enumerator() const {
  typename TrivialThird<LocType, Base>::enumerator ret(&_data);
  return ret;
}

template <typename LocType, typename Base>
TrivialThird<LocType, Base>::TrivialThird() {
  _data.clear();
}

template <typename LocType, typename Base>
void TrivialThird<LocType, Base>::clear() {
  _data.clear();
}

template <typename LocType, typename Base>
TrivialThird<LocType, Base>::~TrivialThird() {
  _data.clear();
}

template <typename LocType, typename Base>
TrivialHessian<LocType, Base> TrivialThird<LocType, Base>::get_and_erase(
  const LocType& x) {
  TrivialHessian<LocType, Base> ret(std::move(_data[x]));
  _data.erase(x);
  return std::move(ret);
}

template <typename LocType, typename Base>
int TrivialThird<LocType, Base>::get_size() const {
  int size_count = 0;
  typename std::map<LocType, TrivialHessian<LocType, Base> >::const_iterator t_iter;
  t_iter = _data.begin();
  while (t_iter != _data.end()) {
    size_count += t_iter->second.get_size();
    ++t_iter;
  }
  return size_count;
}

template <typename LocType, typename Base>
void TrivialThird<LocType, Base>::debug() const {
  typename TrivialThird<LocType, Base>::enumerator d_enum =
      this->get_enumerator();
  LocType x, y, z;
  Base w;
  while (d_enum.has_next()) {
    d_enum.get_next(x, y, z, w);
    std::cout << "T[" << x << ", " << y << ", " << z << "] = "
              << w << std::endl;
  }
}

template <typename LocType, typename Base>
void TrivialThird<LocType, Base>::debug(Logger& logger) const {
  typename TrivialThird<LocType, Base>::enumerator d_enum =
      this->get_enumerator();
  LocType x, y, z;
  Base w;
  while (d_enum.has_next()) {
    d_enum.get_next(x, y, z, w);
    logger << "T[" << x << ", " << y << ", " << z << "] = "
           << w << std::endl;
  }
}

template <typename LocType, typename Base>
int TrivialThird<LocType, Base>::byte_size() const {
  return get_size() * (sizeof(double) + sizeof(LocType) * 3) + sizeof(int);
}

template <typename LocType, typename Base>
void TrivialThird<LocType, Base>::write_to_byte(char* buf) const {

  char* p = buf;
  *((int*)p) = get_size();
  p += sizeof(int);

  typename TrivialThird<LocType, Base>::enumerator d_enum =
      this->get_enumerator();
  LocType x, y, z;
  Base w;
  while(d_enum.has_next()) {
    d_enum.get_next(x, y, z, w);
    *((LocType*)p) = x;
    p += sizeof(LocType);
    *((LocType*)p) = y;
    p += sizeof(LocType);
    *((LocType*)p) = z;
    p += sizeof(LocType);
    *((Base*)p) = w;
    p += sizeof(Base);
  }
}

template <typename LocType, typename Base>
TrivialThird<LocType, Base>::TrivialThird(char* buf) {
  _data.clear();
  char* p = buf;
  int size = 0;
  LocType x, y, z;
  Base w;
  size = *((int*)p);
  p += sizeof(int);
  for(int i = 0; i < size; i++) {
    x = *((LocType*)p);
    p += sizeof(LocType);
    y = *((LocType*)p);
    p += sizeof(LocType);
    z = *((LocType*)p);
    p += sizeof(LocType);
    w = *((Base*)p);
    p += sizeof(Base);
    _data[x][y][z] = w;
  }
}

} // namespace ReverseAD

#endif // Trivial_Third_H_
