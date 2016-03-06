#ifndef REVERSEAD_MULTISET
#define REVERSEAD_MULTISET

#include <set>
#include <iostream>

namespace ReverseAD {

template <typename T>
class ReverseADMultiSet {
 public:
  ReverseADMultiSet();
  ReverseADMultiSet(const ReverseADMultiSet& rsh);
  ReverseADMultiSet(const ReverseADMultiSet&& rhs);
  ReverseADMultiSet(char* const buf, const int t_size);
  ReverseADMultiSet& operator = (const ReverseADMultiSet& rhs);
  ReverseADMultiSet& operator = (const ReverseADMultiSet&& rhs);
  inline bool operator == (const ReverseADMultiSet<T>& rhs) const;
  inline bool operator != (const ReverseADMultiSet<T>& rhs) const;
  inline bool operator < (const ReverseADMultiSet<T>& rhs) const;

  int insert(T element);
  int insert(T element, int count);
  int remove(T element);
  int size() const;
  void debug() const;
  bool find(T target) const;
  int count(T target) const;
  void write_to_byte(char* buf) const;
  void to_array(T*) const;
  void clear();

 private:
  std::multiset<T> _data;
};

template <typename T>
ReverseADMultiSet<T>::ReverseADMultiSet() {
  _data.clear();
}

template <typename T>
ReverseADMultiSet<T>::ReverseADMultiSet(const ReverseADMultiSet& rhs) {
//  std::cout << "ReverseADMultiSet L-ctor" << std::endl;
  _data = rhs._data;
}

template <typename T>
ReverseADMultiSet<T>::ReverseADMultiSet(const ReverseADMultiSet&& rhs) {
//  std::cout << "ReverseADMultiSet R-ctor" << std::endl;
  _data = std::move(rhs._data);
}

template <typename T>
ReverseADMultiSet<T>& ReverseADMultiSet<T>::operator = (
    const ReverseADMultiSet<T>& rhs) {
//  std::cout << "ReverseADMultiSet L-assign" << std::endl;
  this->_data = rhs._data;
  return *this;
}

template <typename T>
ReverseADMultiSet<T>& ReverseADMultiSet<T>::operator = (
    const ReverseADMultiSet<T>&& rhs) {
//  std::cout << "ReverseADMultiSet R-assign" << std::endl;
  this->_data = std::move(rhs._data);
  return *this;
}

template <typename T>
int ReverseADMultiSet<T>::insert(T element) {
  _data.insert(element);
  return _data.count(element);
}

template <typename T>
int ReverseADMultiSet<T>::insert(T element, int count) {
  for(int i = 0; i < count; i++) {
    _data.insert(element);
  }
  return _data.count(element);
}

template <typename T>
int ReverseADMultiSet<T>::remove(T element) {
  typename std::multiset<T>::iterator hit(_data.find(element));
  if (hit != _data.end()) {
    _data.erase(hit);
  }
  return _data.count(element);
}

template <typename T>
void ReverseADMultiSet<T>::to_array(T* array) const {
  typename std::multiset<T>::const_iterator iter = _data.begin();
  int l = 0;
  while (iter != _data.end()) {
    array[l++] = *iter;
    iter++;
  }
}

template <typename T>
int ReverseADMultiSet<T>::size() const {
  return _data.size();
}

template <typename T>
bool ReverseADMultiSet<T>::find(T target) const {
  if (_data.find(target) != _data.end()) {
    return true;
  }
  return false;
}

template <typename T>
int ReverseADMultiSet<T>::count(T target) const {
  return _data.count(target);
}

template <typename T>
void ReverseADMultiSet<T>::debug() const {
  typename std::multiset<T>::iterator iter;
  std::cout << "{ ";
  for(iter = _data.begin(); iter != _data.end(); ++iter) {
    std::cout << (*iter) << " ";
  }
  std::cout << "}";
}

template <typename T>
void ReverseADMultiSet<T>::clear() {
  _data.clear();
}

// kind of redundent because we have < operator.
// But it's more efficient to keep it.
template <typename T>
inline bool ReverseADMultiSet<T>::operator == (
    const ReverseADMultiSet<T>& rhs) const {
  typename std::multiset<T>::iterator iter1;
  typename std::multiset<T>::iterator iter2;
  if (this->_data.size() != rhs._data.size()) {
    return false;
  }
  iter1 = this->_data.begin();
  iter2 = rhs._data.begin();
  while (iter1 != this->_data.end() && iter2 != rhs._data.end()) {
    if (*iter1 != *iter2) {
      return false;
    }
    ++iter1;
    ++iter2;
  }
  return true;
}

template <typename T> 
inline bool ReverseADMultiSet<T>::operator != (
    const ReverseADMultiSet<T>& rhs) const{
  return !((*this) == rhs);
}

template <typename T> 
inline bool ReverseADMultiSet<T>::operator < (
    const ReverseADMultiSet<T>& rhs) const{
  typename std::multiset<T>::iterator iter1;
  typename std::multiset<T>::iterator iter2;
  if (this->_data.size() < rhs._data.size()) {
    return true;
  } else if (this->_data.size() > rhs._data.size()) {
    return false;
  }
  iter1 = this->_data.begin();
  iter2 = rhs._data.begin();
  while (iter1 != this->_data.end() && iter2 != rhs._data.end()) {
    if (*iter1 < *iter2) {
      return true;
    } else if (*iter1 > *iter2) {
      return false;
    }
    ++iter1;
    ++iter2;
  }
  return false;
}

} // namespace ReverseAD

#endif // REVERSEAD_MULTISET
