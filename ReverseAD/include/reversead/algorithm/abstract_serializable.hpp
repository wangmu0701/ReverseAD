#ifndef ABSTRACT_SERIALIZABLE_H_
#define ABSTRACT_SERIALIZABLE_H_

namespace ReverseAD {

class AbstractSerializable {
 public:
  virtual void debug() const = 0;
  virtual int get_size() const = 0;
  virtual int byte_size() const = 0;
  virtual void write_to_byte(char* buf) const = 0;
};

} // namespace ReverseAD

#endif // ABSTRACT_SERIALIZABLE_H_
