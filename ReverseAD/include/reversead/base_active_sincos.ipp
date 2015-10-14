  // sincos operator
  friend BaseActive<Base> sin(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(sin(rhs.val));
    trace_put(sin_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "L(" << &res << ")[" << res.loc << "] = "
             << "sin L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> cos(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(cos(rhs.val));
    trace_put(cos_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "L(" << &res << ")[" << res.loc << "] = "
             << "cos L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    return res;
  }

#ifdef REVERSE_AD_CPP11 
  friend BaseActive<Base>&& sin(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put(sin_a, resloc, rhs.loc, rhs.val);
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
    trace_put(cos_a, resloc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R(" << &rhs << ")[" << resloc << "] = "
             << "sin R(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    rhs.val = cos(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }
#endif // REVERSE_AD_CPP11
