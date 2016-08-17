#ifndef REVERSEAD_DERIVATIVE_TENSOR_H_
#define REVERSEAD_DERIVATIVE_TENSOR_H_

#include <map>
#include <memory>

namespace ReverseAD {

template <typename Base> class BaseReverseMode;
template <typename Base> class BaseReverseAdjoint;
template <typename Base> class BaseReverseHessian;
template <typename Base> class BaseReverseThird;
template <typename Base> class BaseReverseGeneric;
template <typename Base> class BaseReverseTensor;

template <typename LocType, typename Base>
class DerivativeTensor {
  friend class BaseReverseMode<Base>;
  friend class BaseReverseAdjoint<Base>;
  friend class BaseReverseHessian<Base>;
  friend class BaseReverseThird<Base>;
  friend class BaseReverseGeneric<Base>;
  friend class BaseReverseTensor<Base>;
//  friend std::shared_ptr<DerivativeTensor<size_t, double>> strip_derivative(
//      const std::shared_ptr<DerivativeTensor<size_t, SingleForward>> tensor,
//      size_t t_order, size_t ind_size, size_t dep_size);

 public:
  DerivativeTensor(): _dep_size(0), _order(0) {}

  DerivativeTensor(size_t dep_size, size_t ind_size, size_t order) {
    this->_dep_size = dep_size;
    this->_ind_size = ind_size;
    this->_dep_value.resize(dep_size);
    this->_order = order;
    for (size_t i = 0; i < dep_size; i++) {
      _data.insert(std::make_pair(i, std::map<size_t, std::shared_ptr<SingleTensor> >()));
    }
  }

  void get_internal_coordinate_list(
      size_t dep, size_t order, size_t* size, LocType*** tind, Base** values) const {
    if (dep >=_dep_size || order == 0 || order >_order) {
      // error message
      std::cout << "This derivative tensor does not have information about : "
                << " dep = "<< dep << " order = " << order << std::endl;
      (*size) = 0;
      return;
    }
    if (_data.find(dep) == _data.end()) {
      (*size) = 0;
      return;
    }
    if (_data.find(dep)->second.find(order) == _data.find(dep)->second.end()) {
      (*size) = 0;
      return;
    }
    (*size) = ((_data.find(dep)->second).find(order))->second->get_size();
    //_data[dep][order]->get_internal_coordinate_list(tind, values);
    ((_data.find(dep)->second).find(order))->second->get_internal_coordinate_list(tind, values);
  }
  Base get_dep_value(size_t dep) const {
    return _dep_value[dep];
  }

  size_t get_dep_size() const {return _dep_size;}

 private:

  class SingleTensor {
   public:
    ~SingleTensor() {
      delete[] values;
      delete[] tarray;
      delete[] tind;
    }

    SingleTensor(size_t order, size_t size) {
      this->_order = order;
      this->_size = size;
      tarray = new LocType[size * order];
      values = new Base[size];
      tind = new LocType*[size];
      for (size_t i = 0; i < size; i++) {
        tind[i] = &tarray[i * order];
      }
    }

  private:
    friend class DerivativeTensor<LocType, Base>;
    void put_value(size_t num, const LocType* const corind, const Base& value) {
      for (size_t i = 0; i < _order; i++) {
        tind[num][i] = corind[i];
      }
      values[num] = value;
    }
    size_t get_size() const {
      return _size;
    }
    void get_internal_coordinate_list(LocType*** tind, Base** values) const {
      (*tind) = this->tind;
      (*values) = this->values;
    }

    size_t _order;
    size_t _size;
    LocType* tarray;
    LocType** tind;
    Base* values;
  };

  void init_single_tensor(size_t dep, size_t order, size_t order_size) {
    _data[dep].insert(std::make_pair(order,
        std::make_shared<SingleTensor>(order, order_size)));
  }

  void put_value(size_t dep, size_t order, size_t num,
                 const LocType* const corind, const Base& value) {
    _data[dep][order]->put_value(num, corind, value);
  }

  void put_dep_value(size_t dep, const Base& value) {
    _dep_value[dep] = value;
  }

  size_t _dep_size;
  size_t _ind_size;
  size_t _order; 
  std::map<size_t, std::map<size_t, std::shared_ptr<SingleTensor> > > _data; 
  std::vector<Base> _dep_value;
};

} // namespace ReverseAD

#endif // REVERSEAD_DERIVATIEV_TENSOR_H_
