#ifndef REVERSEAD_SYMMETRY_TENSOR_H_
#define REVERSEAD_SYMMETRY_TENSOR_H_

#include <iostream>
#include <map>

namespace ReverseAD {

template <typename LocType>
class TensorIndex {
 public:
  TensorIndex() : _len(0) {};
  TensorIndex(const TensorIndex<LocType>& rhs) = default;
  TensorIndex<LocType>& operator = (const TensorIndex<LocType>& rhs) = default;

  void insert(LocType x) {
    int l = 0;
    while ((l < _len) && (_data[l] > x)) {
      l++;
    }
    for (int i = _len; i >= l+1; i--) {
      _data[i] = _data[i-1];
    }
    _data[l] = x;
    _len += 1;
  }
  void insert(LocType x, int count) {
    if (count == 0) {return;}
    int l = 0;
    while ((l < _len) && (_data[l] > x)) {
      l++;
    }
    for (int i = _len+count-1; i >= l+count; i--) {
      _data[i] = _data[i-count];
    }
    for (int i = 0; i < count; i++) {
      _data[l+i] = x;
    }
    _len += count;
  }
  void clear() {_len = 0;}
  int size() const {return _len;}
  LocType* get_array() {return &(_data[0]);}
  LocType _data[10];
  int _len;
};

template <typename LocType, typename Base>
class SymmetryTensorBase {
 public:
  virtual ~SymmetryTensorBase() = default;
  virtual bool increase(const LocType*&& x, const Base& w) = 0;
  virtual void to_array(LocType** tind, Base* values, int, int) const = 0;
  virtual void debug() const = 0;
  virtual int size() const = 0;
};

template <typename LocType, typename Base, int DIM>
class SymmetryTensor : public SymmetryTensorBase<LocType, Base>{
 public:
  SymmetryTensor() : _size(0), _data(){};
  // true means a new distinct element
  bool increase(const LocType*&& x, const Base& w) override final { 
    if (_data[x[0]].increase(&x[1], w)) {
      _size++;
      return true;
    }
    return false;
  }
  SymmetryTensor<LocType, Base, DIM-1> get_and_erase(LocType x) {
    if (_data.find(x) != _data.end()) {
      SymmetryTensor<LocType, Base, DIM-1> ret = std::move(_data[x]);
      _size -= ret.size();
      _data.erase(x);
      return ret;
    }
    return SymmetryTensor<LocType, Base, DIM-1>();
  }
  void to_array(LocType** tind, Base* values,
                int mybegin, int mydim) const override final {
    int nextbegin = mybegin;
    for (const auto& kv : _data) {
      for (int i = 0; i < kv.second.size(); i++) {
        tind[nextbegin+i][mydim] = kv.first;
      }
      kv.second.to_array(tind, values, nextbegin, mydim+1);
      nextbegin = nextbegin + kv.second.size();
    }
  }
  void debug() const override final {
    std::cout << "DIM : " << DIM << std::endl;
    for (const auto& kv : _data) {
      std::cout << "Value = " << kv.first << std::endl;
      kv.second.debug();
    }
  }
  int size() const override final {
    return _size;
  }
 private:
  // maintain the total number of distinct elements in the tensor
  int _size;
  std::map<LocType, SymmetryTensor<LocType, Base, DIM-1>> _data;
};

template <typename LocType, typename Base>
class SymmetryTensor<LocType, Base, 1> : public SymmetryTensorBase<LocType, Base>{
 public:
  SymmetryTensor() : _size(0), _data() {};
  // true means a new distinct element
  bool increase(const LocType*&& x, const Base& w) override final{
    if (_data.find(x[0]) != _data.end()) {
      _data[x[0]] += w;
      return false;
    } else {
      _data.insert(std::pair<LocType, Base>(x[0], w));
      _size++;
      return true;
    }
  }
  SymmetryTensor<LocType, Base, 0> get_and_erase(LocType x) {
    if (_data.find(x) != _data.end()) {
      SymmetryTensor<LocType, Base, 0> ret = std::move(_data[x]);
      _size -= 1;
      _data.erase(x);
      return ret;
    }
    return 0.0;
  }
  void to_array(LocType** tind, Base* values,
                int mybegin, int mydim) const override final {
    int l = 0;
    for (const auto& kv : _data) {
      tind[mybegin+l][mydim] = kv.first;
      values[mybegin+l] = kv.second;
      l++;
    }
  }
  void debug() const override final {
    for (const auto& kv : _data) {
      std::cout << "A["<<kv.first<<"] = " << kv.second << std::endl;
    }
  }
  int size() const override final {
    return _size;
  }
 private:
  int _size;  // for array _size = _data._size;
  std::map<LocType, Base> _data;
};

template <typename LocType, typename Base>
class SymmetryTensor<LocType, Base, 0> : public SymmetryTensorBase<LocType, Base>{
 public:
  SymmetryTensor() : _size(1), _data(0.0){};
  SymmetryTensor(const Base&& data) : _size(1), _data(data) {};
  SymmetryTensor(const SymmetryTensor<LocType, Base, 0>&) = default;
  SymmetryTensor(SymmetryTensor<LocType, Base, 0>&&) = default;
  SymmetryTensor<LocType,Base, 0>& operator = (const SymmetryTensor<LocType, Base, 0>&) = default;
  SymmetryTensor<LocType,Base, 0>& operator = (SymmetryTensor<LocType, Base, 0>&&) = default;


  // true means a new distinct element
  bool increase(const LocType*&& x, const Base& w) override final{
    return false;
  }
  void to_array(LocType** tind, Base* values,
                int mybegin, int mydim) const override final {
    values[0] = _data;
  }
  void debug() const override final {
    std::cout << "Tensor0 = " << _data << std::endl;
  }
  int size() const override final {
    return _size;
  }
 private:
  int _size;
  Base _data;
};


} // namespace ReverseAD

#endif // REVERSEAD_SYMMETRY_TENSOR_H_
