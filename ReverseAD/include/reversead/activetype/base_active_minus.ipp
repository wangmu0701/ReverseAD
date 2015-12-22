  // minus operator  
  friend BaseActive<Base> operator-(const BaseActive<Base>& lhs, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(lhs.val - rhs.val, get_next_loc());
    trace_put_olll<Base>(minus_a_a, res.loc, lhs.loc, rhs.loc);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] - L("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> operator-(const BaseActive<Base>& lhs, const double& val) {
    BaseActive<Base> res(lhs.val - val, get_next_loc());
    trace_put_olld<Base>(plus_d_a, res.loc, lhs.loc, -val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] - const("
              << val << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> operator-(const double& val, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(val - rhs.val, get_next_loc());
    trace_put_olld<Base>(minus_d_a, res.loc, rhs.loc, val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "const("<< val << ") - L(" << &rhs << ")["
              << rhs.loc << "]" << std::endl;
#endif
    return res;
  }

  BaseActive<Base>& operator -= (const BaseActive<Base>& rhs) {
    locint resloc = get_next_loc();
    trace_put_olll<Base>(eq_minus_a, resloc, this->loc, rhs.loc);
    this->val -= rhs.val;
    this->loc = resloc;
    return *this;
  }

  BaseActive<Base>& operator -= (const double& rhs) {
    this->val -= rhs;
    locint resloc = get_next_loc();
    trace_put_olld<Base>(eq_plus_d, resloc, this->loc, -rhs);
    this->loc = resloc;
    return *this;
  }

#ifdef REVERSE_AD_CPP11 
  // R-value minus
  friend BaseActive<Base>&& operator-(BaseActive<Base>&& lhs, const BaseActive<Base>& rhs) {
    lhs.val -= rhs.val;
    locint resloc = get_next_loc();
    trace_put_olll<Base>(minus_a_a, resloc, lhs.loc, rhs.loc);
    lhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] - L("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(lhs); 
  }
  friend BaseActive<Base>&& operator-(const BaseActive<Base>& lhs, BaseActive<Base>&& rhs) {
    rhs.val = lhs.val - rhs.val;
    locint resloc = get_next_loc();
    trace_put_olll<Base>(minus_a_a, resloc, lhs.loc, rhs.loc);
    rhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &rhs <<")[" << resloc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] - R("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(rhs);
  }
  friend BaseActive<Base>&& operator-(BaseActive<Base>&& lhs, BaseActive<Base>&& rhs) {
    lhs.val -= rhs.val;
    locint resloc = get_next_loc();
    trace_put_olll<Base>(minus_a_a, resloc, lhs.loc, rhs.loc);
    lhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] - R("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator-(BaseActive<Base>&& lhs, const double& val) {
    lhs.val -= val;
    locint resloc = get_next_loc();
    trace_put_olld<Base>(plus_d_a, resloc, lhs.loc, -val);
    lhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] - const("
              << val << ")" << std::endl;
#endif
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator-(const double& val, BaseActive<Base>&& rhs) {
    rhs.val = val - rhs.val;
    locint resloc = get_next_loc();
    trace_put_olld<Base>(minus_d_a, resloc, rhs.loc, val);
    rhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &rhs <<")[" << resloc << "] = " 
              << "const("<< val << ") - R(" << &rhs << ")["
              << rhs.loc << "]" << std::endl;
#endif
    return std::move(rhs);
  }
#endif // REVERSE_AD_CPP11
