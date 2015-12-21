  // sin, cos, tan
  // asin, acos, atan
  friend BaseActive<Base> sin(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(sin(rhs.val), get_next_loc());
    trace_put_ollb<Base>(sin_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res << ")[" << res.loc << "] = "
             << "sin L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> cos(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(cos(rhs.val), get_next_loc());
    trace_put_ollb<Base>(cos_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res << ")[" << res.loc << "] = "
             << "cos L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> tan(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(tan(rhs.val), get_next_loc());
    trace_put_ollb<Base>(tan_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res << ")[" << res.loc << "] = "
             << "tan L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    return res;
  }

  friend BaseActive<Base> asin(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(asin(rhs.val), get_next_loc());
    trace_put_ollb<Base>(asin_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res << ")[" << res.loc << "] = "
             << "asin L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> acos(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(acos(rhs.val), get_next_loc());
    trace_put_ollb<Base>(acos_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res << ")[" << res.loc << "] = "
             << "acos L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    return res;
  }
  friend BaseActive<Base> atan(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(atan(rhs.val), get_next_loc());
    trace_put_ollb<Base>(atan_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res << ")[" << res.loc << "] = "
             << "atan L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    return res;
  }
 
#ifdef REVERSE_AD_CPP11 
  friend BaseActive<Base>&& sin(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(sin_a, resloc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &rhs << ")[" << resloc << "] = "
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
    logger.info << "R(" << &rhs << ")[" << resloc << "] = "
             << "cos R(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    rhs.val = cos(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& tan(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(tan_a, resloc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &rhs << ")[" << resloc << "] = "
             << "tan R(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    rhs.val = tan(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }

  friend BaseActive<Base>&& asin(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(asin_a, resloc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &rhs << ")[" << resloc << "] = "
             << "asin R(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    rhs.val = asin(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& acos(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(acos_a, resloc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &rhs << ")[" << resloc << "] = "
             << "acos R(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    rhs.val = acos(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& atan(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(atan_a, resloc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R(" << &rhs << ")[" << resloc << "] = "
             << "atan R(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
    rhs.val = atan(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }

#endif // REVERSE_AD_CPP11
