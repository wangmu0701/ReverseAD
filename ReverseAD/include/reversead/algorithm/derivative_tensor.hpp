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

template <typename LocType, typename Base>
class DerivativeTensor {
  friend class BaseReverseMode<Base>;
  friend class BaseReverseAdjoint<Base>;
  friend class BaseReverseHessian<Base>;
  friend class BaseReverseThird<Base>;
  friend class BaseReverseGeneric<Base>;
  friend std::shared_ptr<DerivativeTensor<int, double>> strip_derivative(
      const std::shared_ptr<DerivativeTensor<int, SingleForward>> tensor,
      int t_order, int ind_size, int dep_size);

 public:
  DerivativeTensor(): _dep_size(0), _order(0) {}

  DerivativeTensor(int dep_size, int ind_size, int order) {
    this->_dep_size = dep_size;
    this->_ind_size = ind_size;
    this->_dep_value.resize(dep_size);
    this->_order = order;
    for (int i = 0; i < dep_size; i++) {
      _data.insert(std::make_pair(i, std::map<int, std::shared_ptr<SingleTensor> >()));
    }
  }

  void get_internal_coordinate_list(
      int dep, int order, int* size, LocType*** tind, Base** values) const {
    if (dep<0 || dep >=_dep_size || order <= 0 || order >_order) {
      // error message
      std::cout << "This derivative tensor does not have information about : "
                << " dep = "<< dep << " order = " << order << std::endl;
    }
    (*size) = _data[dep][order]->get_size();
    _data[dep][order]->get_internal_coordinate_list(tind, values);
  }
  Base get_dep_value(int dep) const {
    return _dep_value[dep];
  }

  int get_dep_size() const {return _dep_size;}

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
    void get_internal_coordinate_list(LocType*** tind, Base** values) const {
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

  void init_single_tensor(int dep, int order, int order_size) {
    _data[dep].insert(std::make_pair(order,
        std::make_shared<SingleTensor>(order, order_size)));
  }

  void put_value(int dep, int order, int num,
                 const LocType* const corind, const Base& value) {
    _data[dep][order]->put_value(num, corind, value);
  }

  void put_dep_value(int dep, const Base& value) {
    _dep_value[dep] = value;
  }

  int _dep_size;
  int _ind_size;
  int _order; 
  mutable std::map<int, std::map<int, std::shared_ptr<SingleTensor> > > _data; 
  std::vector<Base> _dep_value;
};

} // namespace ReverseAD

#endif // REVERSEAD_DERIVATIEV_TENSOR_H_
