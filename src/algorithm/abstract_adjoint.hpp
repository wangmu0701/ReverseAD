#ifndef ABSTRACT_ADJOINT_H_
#define ABSTRACT_ADJOINT_H_

namespace ReverseAD {

template <typename LocType, typename Base>
class AbstractAdjoint {
 public:
  class enumerator {
   public:
    // dummy copy constructor
    enumerator(const enumerator& other) {
    }
    virtual ~enumerator() {};
    virtual void operator =
      (const enumerator& other) = 0;

    virtual bool has_next() = 0;
    virtual bool get_next(LocType& x, Base& w) = 0;
  };

  // modify
  virtual void increase(LocType x, Base v) = 0;
  virtual Base&& get_and_erase(LocType x) = 0;
  virtual Base& operator[] (LocType x) = 0;
  virtual void erase(LocType x) = 0;
  // query
  virtual int get_size() const = 0;
  virtual bool has_live(LocType target) const = 0;
  virtual void debug() const = 0;

  // serialization
  virtual int byte_size() const = 0;
  virtual void write_to_byte(char* buf) const = 0;
};

} // namespace ReverseAD

#endif // ABSTRACT_ADJOINT_H_ 
