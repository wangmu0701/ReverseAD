#ifndef ABSTRACT_ADJOINT_H_
#define ABSTRACT_ADJOINT_H_

namespace ReverseAD {

template <typename LocType, typename Base>
class AbstractAdjoint {
 public:
  class iterator {
   public:
    virtual ~iterator() {};
    virtual bool reset() = 0;
    virtual bool get_next(LocType& x, Base& w) = 0;
    virtual typename AbstractAdjoint<LocType, Base>::iterator* copy_iter() = 0;
  };
  virtual bool has_live(LocType target) const = 0;
  virtual int byte_size() const = 0;
  virtual void write_to_byte(char* buf) const = 0;
  virtual void increase(T x, double v) = 0;
  virtual Base&& get_and_erase(LocType x) = 0;
  virtual Base&& get(LocType x) = 0; 
  virtual int get_size() const = 0;
  virtual void debug() const = 0;
  virtual typename VectorGraph<LocType, Base>::iterator* get_iterator() = 0;
};

} // namespace ReverseAD

#endif // ABSTRACT_ADJOINT_H_
