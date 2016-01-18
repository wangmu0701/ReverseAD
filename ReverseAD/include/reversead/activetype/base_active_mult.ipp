  // mult operator
  friend BaseActive<Base> operator*(const BaseActive<Base>& lhs, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(lhs.val * rhs.val, get_next_loc());
    trace_put_olllbb<Base>(mult_a_a, res.loc, lhs.loc, rhs.loc, lhs.val, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] * L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> operator*(const BaseActive<Base>& lhs, const double& val) {
    BaseActive<Base> res(lhs.val * val, get_next_loc());
    trace_put_olld<Base>(mult_d_a, res.loc, lhs.loc, val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] * const(" << val << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> operator*(const double& val, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(val * rhs.val, get_next_loc());
    trace_put_olld<Base>(mult_d_a, res.loc, rhs.loc, val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "const("<< val << ") * L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return res;
  }


  BaseActive<Base>& operator *= (const BaseActive<Base>& rhs) {
    locint resloc = get_next_loc();
    trace_put_olllbb<Base>(eq_mult_a, resloc, this->loc, rhs.loc, this->val, rhs.val);
    this->val *= rhs.val;
    this->loc = resloc;
    return *this;
  }

  BaseActive<Base>& operator *= (const double& rhs) {
    locint resloc = get_next_loc();
    trace_put_olld<Base>(eq_mult_d, resloc, this->loc, rhs);
    this->val *= rhs;
    this->loc = resloc;
    return *this;
  }

