#ifndef BASE_ACBaseIVE_H_
#define BASE_ACBaseIVE_H_

#include <iostream>
#include "reversead.hpp"

namespace ReverseAD {

template <typename Base>
class BaseActive {
 public:
  BaseActive() {
  }
  ~BaseActive() {
  }

  // value c-tor
  BaseActive(double val) {
    std::cout << "V-ctor: " << this << " = " << val << std::endl;
    this->val = val;
  }
  // copy c-tor
  BaseActive(BaseActive<Base>& other) {
    std::cout << "L-ctor: " << this << " <- " << &other << std::endl;
    this->val = other.val;
  }
  // move c-tor
  BaseActive(BaseActive<Base>&& other) {
    std::cout << "R-ctor: " << this << " <- " << &other << std::endl;
    this->val = other.val;
  }

  // value assignment
  BaseActive<Base>& operator = (double val) {
    this->val = val;
  }
  // copy assignment
  BaseActive<Base>& operator = (const BaseActive<Base>& other) {
    std::cout << "L-ctor: " << this << " <- " << &other << std::endl;
    if (this != &other) {
      this->val = other.val;
    }
    return *this;
  }

  // move assignment
  BaseActive<Base>& operator = (const BaseActive<Base>&& other) {
    std::cout << "R-ctor: " << this << " <- " << &other << std::endl;
    if (this != &other) {
      this->val = other.val;
    }
    return *this;
  }
  
  // pre-inc ++i
  BaseActive<Base>& operator++() {
    this->val++;
    return *this;
  }
  // post-inc i++
  BaseActive<Base> operator++(int) {
    BaseActive<Base> tmp(*this); // copy c-tor
    operator++(); // pre-inc
    return tmp;
  }
  
  BaseActive<Base>& operator+=(const BaseActive<Base>& rhs) {
    this->val += rhs.val;
    return *this;
  }
  
  friend BaseActive<Base> operator+(const BaseActive<Base>& lhs, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(lhs.val + rhs.val);
    return res;
  }

  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, const BaseActive<Base>& rhs) {
    lhs.val += rhs.val;
    return std::move(lhs); 
  }
  friend BaseActive<Base>&& operator+(const BaseActive<Base>& lhs, BaseActive<Base>&& rhs) {
    rhs.val += lhs.val;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, BaseActive<Base>&& rhs) {
    lhs.val += rhs.val;
    return std::move(lhs);
  }

  inline double getVal() { return val;}

 private:
  Base val;
  locint loc;
};  

} // namespace ReverseAD

#endif // BASE_ACTIVE_H_
