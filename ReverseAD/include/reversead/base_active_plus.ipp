  // plus operator  
  friend BaseActive<Base> operator+(const BaseActive<Base>& lhs, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(lhs.val + rhs.val);
    trace_put(plus_a_a, res.loc, lhs.loc, rhs.loc);
    log.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + L("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return res;
  }
  friend BaseActive<Base> operator+(const BaseActive<Base>& lhs, const Base& val) {
    BaseActive<Base> res(lhs.val + val);
    trace_put(plus_d_a, res.loc, lhs.loc, val);
    log.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + const("
              << val << ")" << std::endl;
    return res;
  }
  friend BaseActive<Base> operator+(const Base& val, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(val + rhs.val);
    trace_put(plus_d_a, res.loc, rhs.loc, val);
    log.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "const("<< val << ") + L(" << &rhs << ")["
              << rhs.loc << "]" << std::endl;
    return res;
  }

#ifdef REVERSE_AD_CPP11 
  // R-value plus
  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, const BaseActive<Base>& rhs) {
    lhs.val += rhs.val;
    locint resloc = get_next_loc();
    trace_put(plus_a_a, resloc, lhs.loc, rhs.loc);
    lhs.loc = resloc;
    log.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] + L("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(lhs); 
  }
  friend BaseActive<Base>&& operator+(const BaseActive<Base>& lhs, BaseActive<Base>&& rhs) {
    rhs.val += lhs.val;
    locint resloc = get_next_loc();
    trace_put(plus_a_a, resloc, lhs.loc, rhs.loc);
    rhs.loc = resloc;
    log.info << "R(" << &rhs <<")[" << resloc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + R("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, BaseActive<Base>&& rhs) {
    lhs.val += rhs.val;
    locint resloc = get_next_loc();
    trace_put(plus_a_a, resloc, lhs.loc, rhs.loc);
    lhs.loc = resloc;
    log.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] + R("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator+(BaseActive<Base>&& lhs, const Base& val) {
    lhs.val += val;
    locint resloc = get_next_loc();
    trace_put(plus_d_a, resloc, lhs.loc, val);
    lhs.loc = resloc;
    log.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] + const("
              << val << ")" << std::endl;
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator+(const Base& val, BaseActive<Base>&& rhs) {
    rhs.val += val;
    locint resloc = get_next_loc();
    trace_put(plus_d_a, resloc, rhs.loc, val);
    rhs.loc = resloc;
    log.info << "R(" << &rhs <<")[" << resloc << "] = " 
              << "const("<< val << ") + R(" << &rhs << ")["
              << rhs.loc << "]" << std::endl;
    return std::move(rhs);
  }
#endif // REVERSE_AD_CPP11
