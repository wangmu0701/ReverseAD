#ifndef REVERSEAD_DERIVATIVE_TENSOR_H_
#define REVERSEAD_DERIVATIVE_TENSOR_H_

#include <map>

namespace ReverseAD {

template <typename Base> class BaseReverseAdjoint;
template <typename Base> class BaseReverseHessian;
template <typename Base> class BaseReverseThird;
template <typename Base> class BaseReverseGeneric;

template <typename LocType, typename Base>
class DerivativeTensor {
  friend class BaseReverseAdjoint<Base>;
  friend class BaseReverseHessian<Base>;
  friend class BaseReverseThird<Base>;
  friend class BaseReverseGeneric<Base>;

 public:
  DerivativeTensor() {}

  void get_internal_coordinate_list(
      int dep, int order, int* size, LocType*** tind, Base** values) {
    (*size) = _data[dep][order]->get_size();
    _data[dep][order]->get_internal_coordinate_list(tind, values);
  }

  int get_dep_size() { return _dep_size;}

 private:

  class SingleTensor {
   public:
    ~SingleTensor() {
      delete[] values;
      delete[] tarray;
      delete[] tind;
    }

    SingleTensor(int order, int size) {
      this->_inited = true;
      this->_order = order;
      this->_size = size;
      tarray = new LocType[size * order];
      values = new Base[size];
      tind = new LocType*[size];
      for (int i = 0; i < size; i++) {
        tind[i] = &tarray[i * order];
      }
    }

  private:
    friend class DerivativeTensor<LocType, Base>;
    void put_value(int num, const LocType* const corind, const Base& value) {
      for (int i = 0; i < _order; i++) {
        tind[num][i] = corind[i];
      }
      values[num] = value;
    }
    int get_size() const {
      return _size;
    }
    void get_internal_coordinate_list(LocType*** tind, Base** values) {
      (*tind) = this->tind;
      (*values) = this->values;
    }

    bool _inited;
    int _order;
    int _size;
    LocType* tarray;
    LocType** tind;
    Base* values;
  };

  DerivativeTensor(int dep_size, int ind_size, int order) {
    this->_dep_size = dep_size;
    this->_ind_size = ind_size;
    this->_order = order;
    for (int i = 0; i < dep_size; i++) {
      _data.insert(std::make_pair(i, std::map<int, std::shared_ptr<SingleTensor> >()));
    }
  }

  void init_single_tensor(int dep, int order, int order_size) {
    _data[dep].insert(std::make_pair(order,
        std::make_shared<SingleTensor>(order, order_size)));
  }

  void put_value(int dep, int order, int num,
                 const LocType* const corind, const Base& value) {
    _data[dep][order]->put_value(num, corind, value);
  }

  int _dep_size;
  int _ind_size;
  int _order; 
  std::map<int, std::map<int, std::shared_ptr<SingleTensor> > > _data; 
};

} // namespace ReverseAD

#endif // REVERSEAD_DERIVATIEV_TENSOR_H_
