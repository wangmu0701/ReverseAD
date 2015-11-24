  // div operator
  friend BaseActive<Base> operator/(const BaseActive<Base>& lhs, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(lhs.val / rhs.val);
    trace_put<Base>(div_a_a, res.loc, lhs.loc, rhs.loc, lhs.val, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] / L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> operator/(const BaseActive<Base>& lhs, const Base& val) {
    BaseActive<Base> res(lhs.val / val);
    trace_put<Base>(mult_d_a, res.loc, lhs.loc, 1.0/val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] / const(" << val << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> operator/(const Base& val, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(val / rhs.val);
    trace_put<Base>(div_d_a, res.loc, rhs.loc, val, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "const("<< val << ") / L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return res;
  }

#ifdef REVERSE_AD_CPP11 
  // R-value mult
  friend BaseActive<Base>&& operator/(BaseActive<Base>&& lhs, const BaseActive<Base>& rhs) {
    locint resloc = get_next_loc();
    trace_put<Base>(div_a_a, resloc, lhs.loc, rhs.loc, lhs.val, rhs.val);
    lhs.val = lhs.val / rhs.val;
    lhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] / L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(lhs); 
  }
  friend BaseActive<Base>&& operator/(const BaseActive<Base>& lhs, BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put<Base>(div_a_a, resloc, lhs.loc, rhs.loc, lhs.val, rhs.val);
    rhs.val = rhs.val / lhs.val;
    rhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R(" << &rhs <<")[" << resloc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] / R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(rhs);
  }
  friend BaseActive<Base>&& operator/(BaseActive<Base>&& lhs, BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put<Base>(mult_a_a, resloc, lhs.loc, rhs.loc, lhs.val, rhs.val);
    lhs.val = lhs.val / rhs.val;
    lhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] / R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator/(BaseActive<Base>&& lhs, const Base& val) {
    lhs.val = lhs.val / val;
    locint resloc = get_next_loc();
    trace_put<Base>(mult_d_a, resloc, lhs.loc, 1.0 / val);
    lhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] / const(" << val << ")" << std::endl;
#endif
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator/(const Base& val, BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put<Base>(div_d_a, resloc, rhs.loc, val, rhs.val);
    rhs.val = val / rhs.val;
    rhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R(" << &rhs <<")[" << resloc << "] = " 
              << "const("<< val << ") / R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(rhs);
  }
#endif // REVERSE_AD_CPP11
