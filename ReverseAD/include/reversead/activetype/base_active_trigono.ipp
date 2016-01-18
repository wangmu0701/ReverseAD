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
/*
    BaseActive<Base> res(tan(rhs.val), get_next_loc());
    trace_put_ollb<Base>(tan_a, res.loc, rhs.loc, rhs.val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L(" << &res << ")[" << res.loc << "] = "
             << "tan L(" << &rhs << ")[" << rhs.loc << ")" << std::endl;
#endif
*/
    return sin(rhs) / cos(rhs);
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
 
