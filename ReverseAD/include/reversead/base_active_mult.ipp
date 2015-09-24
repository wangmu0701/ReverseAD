  // mult operator
  friend BaseActive<Base> operator*(const BaseActive<Base>& lhs, const BaseActive<Base>& rhs) {
    log.info << "L("<< &lhs << ") * "<< "L(" << &rhs << ")" << std::endl;
    BaseActive<Base> res(lhs.val * rhs.val);
    trace_put(mult_a_a, res.loc, lhs.loc, rhs.loc, lhs.val, rhs.val);
    log.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] * L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return res;
  }
  friend BaseActive<Base> operator*(const BaseActive<Base>& lhs, const Base& val) {
    BaseActive<Base> res(lhs.val * val);
    trace_put(mult_d_a, res.loc, lhs.loc, val);
    log.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] * const(" << val << ")" << std::endl;
    return res;
  }
  friend BaseActive<Base> operator*(const Base& val, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(val * rhs.val);
    trace_put(mult_d_a, res.loc, rhs.loc, val);
    log.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "const("<< val << ") * L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return res;
  }

#ifdef REVERSE_AD_CPP11 
  // R-value mult
  friend BaseActive<Base>&& operator*(BaseActive<Base>&& lhs, const BaseActive<Base>& rhs) {
    locint resloc = get_next_loc();
    trace_put(mult_a_a, resloc, lhs.loc, rhs.loc, lhs.val, rhs.val);
    lhs.val *= rhs.val;
    lhs.loc = resloc;
    log.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] * L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(lhs); 
  }
  friend BaseActive<Base>&& operator*(const BaseActive<Base>& lhs, BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put(mult_a_a, resloc, lhs.loc, rhs.loc, lhs.val, rhs.val);
    rhs.val *= lhs.val;
    rhs.loc = resloc;
    log.info << "R(" << &rhs <<")[" << resloc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] * R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& operator*(BaseActive<Base>&& lhs, BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put(mult_a_a, resloc, lhs.loc, rhs.loc, lhs.val, rhs.val);
    lhs.val *= rhs.val;
    lhs.loc = resloc;
    log.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] * R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator*(BaseActive<Base>&& lhs, const Base& val) {
    lhs.val *= val;
    locint resloc = get_next_loc();
    trace_put(mult_d_a, resloc, lhs.loc, val);
    lhs.loc = resloc;
    log.info << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] * const(" << val << ")" << std::endl;
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator*(const Base& val, BaseActive<Base>&& rhs) {
    rhs.val *= val;
    locint resloc = get_next_loc();
    trace_put(mult_d_a, resloc, rhs.loc, val);
    rhs.loc = resloc;
    log.info << "R(" << &rhs <<")[" << resloc << "] = " 
              << "const("<< val << ") * R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(rhs);
  }
#endif // REVERSE_AD_CPP11
