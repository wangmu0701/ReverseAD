  // sincos operator
  friend BaseActive<Base> sin(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(sin(rhs.val), get_next_loc());
    trace_put_ollb<Base>(sin_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "L(" << &res << ")[" << res.loc << "] = "
             << "sin L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> cos(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(cos(rhs.val), get_next_loc());
    trace_put_ollb<Base>(cos_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "L(" << &res << ")[" << res.loc << "] = "
             << "cos L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> sqrt(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(sqrt(rhs.val), get_next_loc());
    trace_put_ollb<Base>(sqrt_a, res.loc, rhs.loc, rhs.val);
    return res;
  }
  friend BaseActive<Base> exp(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(exp(rhs.val), get_next_loc());
    trace_put_ollb<Base>(exp_a, res.loc, rhs.loc, rhs.val);
    return res;
  }
  
#ifdef REVERSE_AD_CPP11 
  friend BaseActive<Base>&& sin(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(sin_a, resloc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R(" << &rhs << ")[" << resloc << "] = "
             << "sin R(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    rhs.val = sin(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& cos(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(cos_a, resloc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R(" << &rhs << ")[" << resloc << "] = "
             << "cos R(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    rhs.val = cos(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& sqrt(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(sqrt_a, resloc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R(" << &rhs << ")[" << resloc << "] = "
             << "sqrt R(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    rhs.val = sqrt(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& exp(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(exp_a, resloc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R(" << &rhs << ")[" << resloc << "] = "
             << "exp R(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    rhs.val = exp(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }

#endif // REVERSE_AD_CPP11
