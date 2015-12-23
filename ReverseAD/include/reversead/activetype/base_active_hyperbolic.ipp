  // sinh, cosh, tanh
  // asinh, acosh, atanh
  friend BaseActive<Base> sinh(const BaseActive<Base>& rhs) {
    return (exp(rhs) - exp(-rhs)) / 2;
  }
  friend BaseActive<Base> cosh(const BaseActive<Base>& rhs) {
    return (exp(rhs) + exp(-rhs)) / 2;
  }
  friend BaseActive<Base> tanh(const BaseActive<Base>& rhs) {
    return (exp(2*rhs) - 1) / (exp(2*rhs) + 1);
  }

  friend BaseActive<Base> asinh(const BaseActive<Base>& rhs) {
    return log(rhs + sqrt(rhs*rhs + 1));
  }
  friend BaseActive<Base> acosh(const BaseActive<Base>& rhs) {
    return log(rhs + sqrt(rhs*rhs - 1));
  }
  friend BaseActive<Base> atanh(const BaseActive<Base>& rhs) {
    return log((1+rhs)/(1-rhs)) * 0.5;
  }
