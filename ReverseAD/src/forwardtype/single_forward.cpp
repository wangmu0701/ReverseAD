#include <cmath>
#include <iostream>
#include "reversead/forwardtype/single_forward.hpp"

namespace ReverseAD {
// stream output
std::ostream& operator<<(std::ostream& os, const SingleForward& obj) {
  os << "[" << &obj << "]" << " val = " << obj.getVal()
  << " der = " << obj.getDer() << std::endl;
  return os;
}

//unary arithmetic
SingleForward& SingleForward::operator++() {
  this->_val++;
  return *this;
}
SingleForward SingleForward::operator++(int) {
  SingleForward res(*this);
  this->_val++;
  return res;
}
SingleForward& SingleForward::operator--() {
  this->_val--;
  return *this;
}
SingleForward SingleForward::operator--(int) {
  SingleForward res(*this);
  this->_val--;
  return res;
}
// binary arithmetic
SingleForward& SingleForward::operator+=(const SingleForward& rhs) {
  this->_val += rhs._val;
  this->_der += rhs._der;
  return *this;
}
SingleForward& SingleForward::operator-=(const SingleForward& rhs) {
  this->_val -= rhs._val;
  this->_der -= rhs._der;
  return *this;
}
SingleForward& SingleForward::operator*=(const SingleForward& rhs) {
  this->_der = this->_val * rhs._der + this->_der * rhs._val;
  this->_val *= rhs._val;
  return *this;
}
SingleForward& SingleForward::operator/=(const SingleForward& rhs) {
  this->_der = (this->_der * rhs._val - rhs._der * this->_val) / (rhs._val * rhs._val);
  this->_val /= rhs._val;
  return *this;
}

// comparison operators
bool operator==(const SingleForward& lhs,
                       const SingleForward& rhs) {
  return (lhs._val == rhs._val);
}
bool operator!=(const SingleForward& lhs,
                       const SingleForward& rhs) {
  return !(lhs==rhs);
}
bool operator< (const SingleForward& lhs,
                       const SingleForward& rhs) {
  return (lhs._val < rhs._val);
}
bool operator> (const SingleForward& lhs,
                       const SingleForward& rhs) {
  return (rhs < lhs);
}
bool operator<=(const SingleForward& lhs,
                       const SingleForward& rhs) {
  return !(rhs < lhs);
}
bool operator>=(const SingleForward& lhs,
                       const SingleForward& rhs) {
  return !(lhs < rhs);
}

// binary arithmetic
SingleForward operator+(SingleForward lhs,
                               const SingleForward& rhs) {
  lhs += rhs;
  return lhs;
}
SingleForward operator-(SingleForward lhs,
                               const SingleForward& rhs) {
  lhs -= rhs;
  return lhs;
}
SingleForward operator*(SingleForward lhs,
                               const SingleForward& rhs) {
  lhs *= rhs;
  return lhs;
}
SingleForward operator/(SingleForward lhs,
                               const SingleForward& rhs) {
  lhs /= rhs;
  return lhs;
}

SingleForward sqrt(const SingleForward& rhs) {
  return SingleForward(std::sqrt(rhs._val),
                       rhs._der / (2.0 * std::sqrt(rhs._val)));
}
SingleForward log(const SingleForward& rhs) {
  return SingleForward(std::log(rhs._val), 1.0 / rhs._val * rhs._der);
}
SingleForward exp(const SingleForward& rhs) {
  return SingleForward(std::exp(rhs._val), std::exp(rhs._val) * rhs._der);
}
SingleForward pow(const SingleForward& base,
                         const SingleForward& exponent) {
  return exp(log(base) * exponent);
}
SingleForward pow(double base,
                         const SingleForward& exponent) {
  return SingleForward(std::pow(base, exponent._val),
                       std::pow(base, exponent._val) * std::log(base) * exponent._der);
}
SingleForward pow(const SingleForward& base,
                         double exponent) {
  return SingleForward(std::pow(base._val, exponent),
                       exponent * std::pow(base._val, exponent - 1.0) * base._der);
}

SingleForward sin(const SingleForward& rhs) {
  return SingleForward(std::sin(rhs._val), std::cos(rhs._val) * rhs._der);
}
SingleForward cos(const SingleForward& rhs) {
  return SingleForward(std::cos(rhs._val), -std::sin(rhs._val) * rhs._der);
}
SingleForward tan(const SingleForward& rhs) {
  return SingleForward(std::tan(rhs._val),
                       rhs._der / (std::cos(rhs._val) * std::cos(rhs._val)));
}

SingleForward asin(const SingleForward& rhs) {
  return SingleForward(std::asin(rhs._val),
                       rhs._der / (1.0 - rhs._val * rhs._val));
}
SingleForward acos(const SingleForward& rhs) {
  return SingleForward(std::acos(rhs._val),
                       -rhs._der / (1.0 - rhs._val * rhs._val));
}
SingleForward atan(const SingleForward& rhs) {
  return SingleForward(std::atan(rhs._val),
                       rhs._der / (1.0 + rhs._val * rhs._val));
}

} // namespace ReverseAD
