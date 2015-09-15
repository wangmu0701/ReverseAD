#ifndef BASE_ACBaseIVE_H_
#define BASE_ACBaseIVE_H_

#include <iostream>
#include "reversead.hpp"
#include "opcodes.hpp"

#define REVERSE_AD_CPP11

namespace ReverseAD {

template <typename Base>
class BaseActive {
 public:
  BaseActive() {
    this->val = 0.0;
    this->loc = get_next_loc();
    std::cout << "V-ctor: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
  }
  ~BaseActive() {
    std::cout << "free loc: " << this << "["<<this->loc<<"]" << std::endl;
  }

  // value c-tor
  BaseActive(Base val) {
    this->val = val;
    this->loc = get_next_loc();
    std::cout << "V-ctor: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
    trace_put(assign_d, this->loc, val);
  }
  // copy c-tor
  BaseActive(const BaseActive<Base>& other) {
    std::cout << "L-ctor: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
    this->val = other.val;
    this->loc = get_next_loc();
    trace_put(assign_a, this->loc, other.loc);
  }

  // value assignment
  BaseActive<Base>& operator = (Base val) {
    this->val = val;
    trace_put(assign_d, this->loc, val);
    std::cout << "V-assign: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
    return *this;
  }
  // copy assignment
  BaseActive<Base>& operator = (const BaseActive<Base>& other) {
    if (this != &other) {
      this->val = other.val;
    }
    trace_put(assign_a, this->loc, other.loc);
    std::cout << "L-assign: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
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
    trace_put(plus_a_a, res.loc, lhs.loc, rhs.loc);
    std::cout << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return res;
  }
  friend BaseActive<Base> operator+(const BaseActive<Base>& lhs, const Base& val) {
    BaseActive<Base> res(lhs.val + val);
    trace_put(plus_d_a, res.loc, lhs.loc, val);
    std::cout << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + const(" << val << ")" << std::endl;
    return res;
  }
  friend BaseActive<Base> operator+(const Base& val, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(val + rhs.val);
    trace_put(plus_d_a, res.loc, rhs.loc, val);
    std::cout << "L(" << &res <<")[" << res.loc << "] = " 
              << "const("<< val << ") + L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return res;
  }

  friend BaseActive<Base> operator*(const BaseActive<Base>& lhs, const BaseActive<Base>& rhs) {
    std::cout << "L("<< &lhs << ") * "<< "L(" << &rhs << ")" << std::endl;
    BaseActive<Base> res(lhs.val * rhs.val);
    trace_put(mult_a_a, res.loc, lhs.loc, rhs.loc);
    std::cout << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] * L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return res;
  }
  friend BaseActive<Base> operator*(const BaseActive<Base>& lhs, const Base& val) {
    BaseActive<Base> res(lhs.val * val);
    trace_put(mult_d_a, res.loc, lhs.loc, val);
    std::cout << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] * const(" << val << ")" << std::endl;
    return res;
  }
  friend BaseActive<Base> operator*(const Base& val, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(val * rhs.val);
    trace_put(mult_d_a, res.loc, rhs.loc, val);
    std::cout << "L(" << &res <<")[" << res.loc << "] = " 
              << "const("<< val << ") * L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return res;
  }

#ifdef REVERSE_AD_CPP11 
  // move c-tor
  BaseActive(BaseActive<Base>&& other) {
    this->val = other.val;
    this->loc = other.loc;
    std::cout << "R-ctor: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
    trace_put(assign_a, this->loc, other.loc);
  }

  // move assignment
  BaseActive<Base>& operator = (const BaseActive<Base>&& other) {
    if (this != &other) {
      this->val = other.val;
    }
    trace_put(assign_a, this->loc, other.loc);
    std::cout << "R-assign: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
    return *this;
  }
  
  // R-value plus
  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, const BaseActive<Base>& rhs) {
    lhs.val += rhs.val;
    trace_put(plus_a_a, lhs.loc, lhs.loc, rhs.loc);
    std::cout << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] + L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(lhs); 
  }
  friend BaseActive<Base>&& operator+(const BaseActive<Base>& lhs, BaseActive<Base>&& rhs) {
    rhs.val += lhs.val;
    trace_put(plus_a_a, rhs.loc, lhs.loc, rhs.loc);
    std::cout << "R(" << &rhs <<")[" << rhs.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, BaseActive<Base>&& rhs) {
    lhs.val += rhs.val;
    trace_put(plus_a_a, lhs.loc, lhs.loc, rhs.loc);
    std::cout << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] + R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, const Base& val) {
    lhs.val += val;
    trace_put(plus_d_a, lhs.loc, lhs.loc, val);
    std::cout << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] + const(" << val << ")" << std::endl;
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator+(const Base& val, BaseActive<Base>&& rhs) {
    rhs.val += val;
    trace_put(plus_d_a, rhs.loc, rhs.loc, val);
    std::cout << "R(" << &rhs <<")[" << rhs.loc << "] = " 
              << "const("<< val << ") + R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(rhs);
  }

  // R-value mult
  friend BaseActive<Base>&& operator*(BaseActive<Base>&& lhs, const BaseActive<Base>& rhs) {
    lhs.val *= rhs.val;
    trace_put(mult_a_a, lhs.loc, lhs.loc, rhs.loc);
    std::cout << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] * L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(lhs); 
  }
  friend BaseActive<Base>&& operator*(const BaseActive<Base>& lhs, BaseActive<Base>&& rhs) {
    rhs.val *= lhs.val;
    trace_put(mult_a_a, rhs.loc, lhs.loc, rhs.loc);
    std::cout << "R(" << &rhs <<")[" << rhs.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] * R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& operator*(BaseActive<Base>&& lhs, BaseActive<Base>&& rhs) {
    lhs.val *= rhs.val;
    trace_put(mult_a_a, lhs.loc, lhs.loc, rhs.loc);
    std::cout << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] * R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator*(BaseActive<Base>&& lhs, const Base& val) {
    lhs.val *= val;
    trace_put(mult_d_a, lhs.loc, lhs.loc, val);
    std::cout << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] * const(" << val << ")" << std::endl;
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator*(const Base& val, BaseActive<Base>&& rhs) {
    rhs.val *= val;
    trace_put(mult_d_a, rhs.loc, rhs.loc, val);
    std::cout << "R(" << &rhs <<")[" << rhs.loc << "] = " 
              << "const("<< val << ") * R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(rhs);
  }
#endif // REVERSE_AD_CPP11

  inline Base getVal() { return val;}

 private:
  Base val;
  locint loc;
};  

} // namespace ReverseAD

typedef ReverseAD::BaseActive<double> adouble;

#endif // BASE_ACTIVE_H_
