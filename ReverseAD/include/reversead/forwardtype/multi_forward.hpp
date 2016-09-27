#ifndef REVERSEAD_MULTI_FORWARD_H_
#define REVERSEAD_MULTI_FORWARD_H_

#include <cmath>

#include "reversead/common/reversead_const.hpp"

namespace ReverseAD {

template <size_t DIM>
class MultiForward {
 public:
  explicit MultiForward() = default;
  MultiForward(const MultiForward<DIM>&) = default;
  MultiForward(double val) : _val(val) {
    for (int i = 0; i < DIM; i++) {
      _der[i] = 0.0;
     }
  }
  MultiForward(double val, double* der) : _val(val) {
    for (int i = 0; i < DIM; i++) {
      _der[i] = der[i];
    }
  }
  double getVal() const {
    return _val;
  }
  double getDer(size_t index) const {
    return _der[index];
  }

  // unary arithmetic
  MultiForward<DIM>& operator++() {
    this->_val += 1.0;
    return (*this);
  }

  MultiForward<DIM> operator++(int) {
    MultiForward<DIM> ret(*this);
    this->_val += 1.0;
    return ret;
  }
    
  MultiForward<DIM>& operator--() {
    this->_val -= 1.0;
    return (*this);
  }  
  MultiForward<DIM> operator--(int) {
    MultiForward<DIM> ret(*this);
    this->_val -= 1.0;
    return ret;
  }

  MultiForward<DIM> operator+() const {
    return MultiForward<DIM>(*this);
  }
  MultiForward<DIM> operator-() const {
    return 0.0 - (*this);
  }

  // binary arithmetic
  MultiForward<DIM>& operator+=(const MultiForward<DIM>& rhs) {
    this->_val += rhs._val;
    for (int i = 0; i < DIM; i++) {
      this->_der[i] += rhs._der[i];
    }
    return (*this);
  }

  MultiForward<DIM>& operator-=(const MultiForward<DIM>& rhs) {
    this->_val -= rhs._val;
    for (int i = 0; i < DIM; i++) {
      this->_der[i] -= rhs._der[i];
    }
    return (*this);
  }

  MultiForward<DIM>& operator*=(const MultiForward<DIM>& rhs) {
    for (int i = 0; i < DIM; i++) {
      this->_der[i] = this->_val * rhs._der[i] + this->_der[i] * rhs._val;
    }
    this->_val *= rhs._val;
    return (*this);
  }

  MultiForward<DIM>& operator/=(const MultiForward<DIM>& rhs) {
    for (int i = 0; i < DIM; i++) {
      this->_der[i] = (this->_der[i] * rhs._val - rhs._der[i] * this->_val) /
                      (rhs._val * rhs._val);
    }
    this->_val /= rhs._val;
    return (*this);
  }

 private:
  double _val;
  double _der[DIM];

  MultiForward<DIM>& scale_der(const double& t) {
    for (int i = 0; i < DIM; i++) {
      this->_der[i] *= t;
    }
    return (*this);
  } 
  
  friend MultiForward operator+ (MultiForward lhs,
                                 const MultiForward& rhs) {
    MultiForward ret(lhs);
    ret += rhs;
    return ret;
  }
  friend MultiForward operator- (MultiForward lhs,
                                 const MultiForward& rhs) {
    MultiForward ret(lhs);
    ret -= rhs;
    return ret;
  }
  friend MultiForward operator* (MultiForward lhs,
                                 const MultiForward& rhs) {
    MultiForward ret(lhs);
    ret *= rhs;
    return ret;
  }
  friend MultiForward operator/ (MultiForward lhs,
                                 const MultiForward& rhs) {
    MultiForward ret(lhs);
    ret /= rhs;
    return ret;
  }

  friend bool operator== (const MultiForward& lhs,
                          const MultiForward& rhs) {
    return (lhs._val == rhs._val);
  }
  friend bool operator!= (const MultiForward& lhs,
                          const MultiForward& rhs) {
    return !(lhs._val == rhs._val);
  }
  
  friend bool operator< (const MultiForward& lhs,
                         const MultiForward& rhs) {
    return (lhs._val < rhs._val);
  }
  friend bool operator> (const MultiForward& lhs,
                         const MultiForward& rhs) {
    return (rhs._val < lhs._val);
  }
  friend bool operator<= (const MultiForward& lhs,
                         const MultiForward& rhs) {
    return !(rhs._val < lhs._val);
  }
  friend bool operator>= (const MultiForward& lhs,
                         const MultiForward& rhs) {
    return !(lhs._val < rhs._val);
  }

  friend MultiForward sqrt(const MultiForward& rhs) {
    MultiForward ret(rhs);
    ret._val = std::sqrt(rhs._val);
    return ret.scale_der(0.5 / ret._val); 
  }
  friend MultiForward log(const MultiForward& rhs) {
    MultiForward ret(rhs);
    ret._val = std::log(rhs._val);
    return ret.scale_der(1.0 / rhs._val); 
  }
  friend MultiForward exp(const MultiForward& rhs) {
    MultiForward ret(rhs);
    ret._val = std::exp(rhs._val);
    return ret.scale_der(ret._val); 
  }
  friend MultiForward pow(const MultiForward& base,
                          const MultiForward& exponent) {
    return exp(log(base) * exponent);
  }
  friend MultiForward pow(const double& base,
                          const MultiForward& exponent) {
    MultiForward ret(exponent);
    ret._val = std::pow(base, exponent._val);
    return ret.scale_der(ret._val * std::log(base));
  }
  friend MultiForward pow(const MultiForward& base,
                          const double& exponent) {
    MultiForward ret(base);
    ret._val = std::pow(base._val, exponent);
    return ret.scale_der(exponent * std::pow(base._val, (exponent - 1.0)));
  }

  friend MultiForward sin(const MultiForward& rhs) {
    MultiForward ret(rhs);
    ret._val = std::sin(rhs._val);
    return ret.scale_der(std::cos(rhs._val));
  }
  friend MultiForward cos(const MultiForward& rhs) {
    MultiForward ret(rhs);
    ret._val = std::cos(rhs._val);
    return ret.scale_der(-std::sin(rhs._val));
  }
  friend MultiForward tan(const MultiForward& rhs) {
    MultiForward ret(rhs);
    ret._val = std::tan(rhs._val);
    return ret.scale_der(1.0 / (std::cos(rhs._val) * std::cos(rhs._val)));
  }

  friend MultiForward asin(const MultiForward& rhs) {
    MultiForward ret(rhs);
    ret._val = std::asin(rhs._val);
    return ret.scale_der(1.0 / (1.0 - rhs._val * rhs._val));
  }

  friend MultiForward acos(const MultiForward& rhs) {
    MultiForward ret(rhs);
    ret._val = std::acos(rhs._val);
    return ret.scale_der(1.0 / (rhs._val * rhs._val - 1.0));
  }
  friend MultiForward atan(const MultiForward& rhs) {
    MultiForward ret(rhs);
    ret._val = std::atan(rhs._val);
    return ret.scale_der(1.0 / (1.0 + rhs._val * rhs._val));
  }

  friend MultiForward erf(const MultiForward& rhs) {
    MultiForward ret(rhs);
    ret._val = std::erf(rhs._val);
    return ret.scale_der(2.0 / std::sqrt(PI) * std::sqrt(-rhs._val*rhs._val));
  }

  friend MultiForward fabs(const MultiForward& rhs) {
    MultiForward ret(0);
    if (rhs._val > 0) {
      ret._val = rhs._val;
      for (int i = 0; i < DIM; i++) {
        ret._der[i] = 1.0;
      }
    } else if (rhs._val < 0) {
      ret._val = -rhs._val;
      for (int i = 0; i < DIM; i++) {
        ret._der[i] = -1.0;
      }
    }
    for (int i = 0; i < DIM; i++) {
      if (rhs._der[i] > 0) {
        ret._der[i] = 1.0;
      } else if (rhs._der[i] < 0) {
        ret._der[i] = -1.0;
      }
    }
    return ret;
  }


  friend std::ostream& operator<< (std::ostream& os, const MultiForward& obj) {
    os << "val = " << obj._val << ", der = [ ";
    for (int i = 0; i < DIM; i++) {
      os << obj._der[i] << " ";
    }
    os << " ]";
    return os;
  }
};

} // namespace ReverseAD

#endif // REVERSEAD_MULTI_FORWARD_H_
