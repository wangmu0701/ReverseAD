  // plus operator  
  friend BaseActive<Base> operator+(const BaseActive<Base>& lhs, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(lhs.val + rhs.val, get_next_loc());
    trace_put_olll<Base>(plus_a_a, res.loc, lhs.loc, rhs.loc);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + L("
              << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> operator+(const BaseActive<Base>& lhs, const double& val) {
    BaseActive<Base> res(lhs.val + val, get_next_loc());
    trace_put_olld<Base>(plus_d_a, res.loc, lhs.loc, val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] + const("
              << val << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> operator+(const double& val, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(val + rhs.val, get_next_loc());
    trace_put_olld<Base>(plus_d_a, res.loc, rhs.loc, val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "const("<< val << ") + L(" << &rhs << ")["
              << rhs.loc << "]" << std::endl;
#endif
    return res;
  }

  BaseActive<Base>& operator += (const BaseActive<Base>& rhs) {
    this->val += rhs.val;
    locint resloc = get_next_loc();
    trace_put_olll<Base>(eq_plus_a, resloc, this->loc, rhs.loc);
    this->loc = resloc;
    return *this;
  }

  BaseActive<Base>& operator += (const double& rhs) {
    this->val += rhs;
    locint resloc = get_next_loc();
    trace_put_olld<Base>(eq_plus_d, resloc, this->loc, rhs);
    this->loc = resloc;
    return *this;
  }
