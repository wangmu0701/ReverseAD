  // plus operator  
  friend BaseActive<Base> operator+(const BaseActive<Base>& lhs, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(lhs.val + rhs.val);
    trace_put(plus_a_a, res.loc, lhs.loc, rhs.loc);
    std::cout << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + L("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return res;
  }
  friend BaseActive<Base> operator+(const BaseActive<Base>& lhs, const Base& val) {
    BaseActive<Base> res(lhs.val + val);
    trace_put(plus_d_a, res.loc, lhs.loc, val);
    std::cout << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + const("
              << val << ")" << std::endl;
    return res;
  }
  friend BaseActive<Base> operator+(const Base& val, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(val + rhs.val);
    trace_put(plus_d_a, res.loc, rhs.loc, val);
    std::cout << "L(" << &res <<")[" << res.loc << "] = " 
              << "const("<< val << ") + L(" << &rhs << ")["
              << rhs.loc << "]" << std::endl;
    return res;
  }

#ifdef REVERSE_AD_CPP11 
  // R-value plus
  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, const BaseActive<Base>& rhs) {
    lhs.val += rhs.val;
    trace_put(plus_a_a, lhs.loc, lhs.loc, rhs.loc);
    std::cout << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] + L("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(lhs); 
  }
  friend BaseActive<Base>&& operator+(const BaseActive<Base>& lhs, BaseActive<Base>&& rhs) {
    rhs.val += lhs.val;
    trace_put(plus_a_a, rhs.loc, lhs.loc, rhs.loc);
    std::cout << "R(" << &rhs <<")[" << rhs.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + R("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, BaseActive<Base>&& rhs) {
    lhs.val += rhs.val;
    trace_put(plus_a_a, lhs.loc, lhs.loc, rhs.loc);
    std::cout << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] + R("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, const Base& val) {
    lhs.val += val;
    trace_put(plus_d_a, lhs.loc, lhs.loc, val);
    std::cout << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] + const("
              << val << ")" << std::endl;
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator+(const Base& val, BaseActive<Base>&& rhs) {
    rhs.val += val;
    trace_put(plus_d_a, rhs.loc, rhs.loc, val);
    std::cout << "R(" << &rhs <<")[" << rhs.loc << "] = " 
              << "const("<< val << ") + R(" << &rhs << ")["
              << rhs.loc << "]" << std::endl;
    return std::move(rhs);
  }
#endif // REVERSE_AD_CPP11
