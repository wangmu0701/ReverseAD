  // div operator
  friend BaseActive<Base> operator/(const BaseActive<Base>& lhs, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(lhs.val / rhs.val, get_next_loc());
    trace_put_olllbb<Base>(div_a_a, res.loc, lhs.loc, rhs.loc, lhs.val, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] / L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> operator/(const BaseActive<Base>& lhs, const double& val) {
    BaseActive<Base> res(lhs.val / val, get_next_loc());
    trace_put_olld<Base>(mult_d_a, res.loc, lhs.loc, 1.0/val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] / const(" << val << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> operator/(const double& val, const BaseActive<Base>& rhs) {
    BaseActive<Base> res(val / rhs.val, get_next_loc());
    trace_put_ollbd<Base>(div_d_a, res.loc, rhs.loc, rhs.val, val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res <<")[" << res.loc << "] = " 
              << "const("<< val << ") / L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return res;
  }

  BaseActive<Base>& operator /= (const BaseActive<Base>& rhs) {
    locint resloc = get_next_loc();
    trace_put_olllbb<Base>(eq_div_a, resloc, this->loc, rhs.loc, this->val, rhs.val);
    this->val /= rhs.val;
    this->loc = resloc;
    return *this;
  }

  BaseActive<Base>& operator /= (const double& rhs) {
    locint resloc = get_next_loc();
    trace_put_olld<Base>(eq_mult_d, resloc, this->loc, 1.0 / rhs);
    this->val /= rhs;
    this->loc = resloc;
    return *this;
  }


#ifdef REVERSE_AD_CPP11 
  // R-value mult
  friend BaseActive<Base>&& operator/(BaseActive<Base>&& lhs, const BaseActive<Base>& rhs) {
    locint resloc = get_next_loc();
    trace_put_olllbb<Base>(div_a_a, resloc, lhs.loc, rhs.loc, lhs.val, rhs.val);
    lhs.val = lhs.val / rhs.val;
    lhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] / L(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(lhs); 
  }
  friend BaseActive<Base>&& operator/(const BaseActive<Base>& lhs, BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_olllbb<Base>(div_a_a, resloc, lhs.loc, rhs.loc, lhs.val, rhs.val);
    rhs.val = rhs.val / lhs.val;
    rhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &rhs <<")[" << resloc << "] = " 
              << "L("<< &lhs << ")["<<lhs.loc<<"] / R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(rhs);
  }
  friend BaseActive<Base>&& operator/(BaseActive<Base>&& lhs, BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_olllbb<Base>(div_a_a, resloc, lhs.loc, rhs.loc, lhs.val, rhs.val);
    lhs.val = lhs.val / rhs.val;
    lhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &lhs <<")[" << resloc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] / R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator/(BaseActive<Base>&& lhs, const double& val) {
    lhs.val = lhs.val / val;
    locint resloc = get_next_loc();
    trace_put_olld<Base>(mult_d_a, resloc, lhs.loc, 1.0 / val);
    lhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &lhs <<")[" << lhs.loc << "] = " 
              << "R("<< &lhs << ")["<<lhs.loc<<"] / const(" << val << ")" << std::endl;
#endif
    return std::move(lhs);
  }
  friend BaseActive<Base>&& operator/(const double& val, BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollbd<Base>(div_d_a, resloc, rhs.loc, rhs.val, val);
    rhs.val = val / rhs.val;
    rhs.loc = resloc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &rhs <<")[" << resloc << "] = " 
              << "const("<< val << ") / R(" << &rhs << ")[" << rhs.loc << "]" << std::endl;
#endif
    return std::move(rhs);
  }
#endif // REVERSE_AD_CPP11
