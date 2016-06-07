#ifndef REVERSEAD_SINGLE_FORWARD_H_
#define REVERSEAD_SINGLE_FORWARD_H_

#include <cmath>

class ostream;

namespace ReverseAD {

class SingleForward {
 public:
  // A default c-tor will make it POD
  explicit SingleForward() = default;
  SingleForward(double val) : _val(val), _der(0) {}
  SingleForward(double val, double der) : _val(val), _der(der) {}
  
  double getVal() const {return _val;}
  double getDer() const {return _der;}

  // unary arithmetic
  SingleForward& operator++();
  SingleForward operator++(int);
  SingleForward& operator--();
  SingleForward operator--(int);

  SingleForward operator+() const;
  SingleForward operator-() const;

  // binary arithmetic
  SingleForward& operator+=(const SingleForward& rhs);
  SingleForward& operator-=(const SingleForward& rhs);
  SingleForward& operator*=(const SingleForward& rhs);
  SingleForward& operator/=(const SingleForward& rhs);

 private:
  double _val;
  double _der;

  friend bool operator==(const SingleForward& lhs,
                                const SingleForward& rhs);
  friend bool operator< (const SingleForward& lhs,
                                const SingleForward& rhs);
  friend SingleForward sqrt(const SingleForward& rhs);
  friend SingleForward log(const SingleForward& rhs);
  friend SingleForward exp(const SingleForward& rhs);
  friend SingleForward pow(const SingleForward& base, const SingleForward& exponent);
  friend SingleForward pow(double base, const SingleForward& exponent);
  friend SingleForward pow(const SingleForward& base, double exponent);

  friend SingleForward sin(const SingleForward& rhs);
  friend SingleForward cos(const SingleForward& rhs);
  friend SingleForward tan(const SingleForward& rhs);
  friend SingleForward asin(const SingleForward& rhs);
  friend SingleForward acos(const SingleForward& rhs);
  friend SingleForward atan(const SingleForward& rhs);
 
  friend SingleForward fabs(const SingleForward& rhs);
};

// stream output
std::ostream& operator<<(std::ostream& os, const SingleForward& obj);

// comparison operators
bool operator==(const SingleForward& lhs,
                       const SingleForward& rhs);
bool operator!=(const SingleForward& lhs,
                       const SingleForward& rhs);
bool operator< (const SingleForward& lhs,
                       const SingleForward& rhs);
bool operator> (const SingleForward& lhs,
                       const SingleForward& rhs);
bool operator<=(const SingleForward& lhs,
                       const SingleForward& rhs);
bool operator>=(const SingleForward& lhs,
                       const SingleForward& rhs);

// binary arithmetic
SingleForward operator+(SingleForward lhs,
                               const SingleForward& rhs);
SingleForward operator-(SingleForward lhs,
                               const SingleForward& rhs);
SingleForward operator*(SingleForward lhs,
                               const SingleForward& rhs);
SingleForward operator/(SingleForward lhs,
                               const SingleForward& rhs);

// unary arithmetic
SingleForward sqrt(const SingleForward& rhs);
SingleForward log(const SingleForward& rhs);
SingleForward exp(const SingleForward& rhs);
SingleForward pow(const SingleForward& base, 
                         const SingleForward& exponent);
SingleForward pow(double base,
                         const SingleForward& exponent);
SingleForward pow(const SingleForward& base,
                         double exponent);
SingleForward sin(const SingleForward& rhs);
SingleForward cos(const SingleForward& rhs);
SingleForward tan(const SingleForward& rhs);

SingleForward asin(const SingleForward& rhs);
SingleForward acos(const SingleForward& rhs);
SingleForward atan(const SingleForward& rhs);

SingleForward fabs(const SingleForward& rhs);

} // namespace ReverseAD

#endif // REVERSEAD_SINGLE_FORWARD_H_
