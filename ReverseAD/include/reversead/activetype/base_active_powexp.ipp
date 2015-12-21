  // pow, sqrt, exp, log
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
  friend BaseActive<Base> log(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(log(rhs.val), get_next_loc());
    trace_put_ollb<Base>(log_a, res.loc, rhs.loc, rhs.val);
    return res;
  }

  friend BaseActive<Base> pow(const BaseActive<Base>& pow_base,
                              const BaseActive<Base>& pow_exp) {
    BaseActive<Base> res(pow(pow_base.val, pow_exp.val), get_next_loc());
    trace_put_olllbb<Base>(pow_a_a, res.loc, pow_base.loc, pow_exp.loc,
                           pow_base.val, pow_exp.val);
    return res;
  }
  friend BaseActive<Base> pow(const BaseActive<Base>& pow_base,
                              const double& pow_exp) {
    BaseActive<Base> res(pow(pow_base.val, pow_exp), get_next_loc());
    trace_put_ollbd<Base>(pow_a_d, res.loc, pow_base.loc,
                           pow_base.val, pow_exp);
    return res;
  }
  friend BaseActive<Base> pow(const double& pow_base,
                              const BaseActive<Base>& pow_exp) {
    BaseActive<Base> res(pow(pow_base, pow_exp.val), get_next_loc());
    trace_put_ollbd<Base>(pow_d_a, res.loc, pow_exp.loc,
                           pow_exp.val, pow_base);
    return res;
  } 
#ifdef REVERSE_AD_CPP11 
  friend BaseActive<Base>&& sqrt(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(sqrt_a, resloc, rhs.loc, rhs.val);
    rhs.val = sqrt(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& exp(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(exp_a, resloc, rhs.loc, rhs.val);
    rhs.val = exp(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }
  friend BaseActive<Base>&& log(BaseActive<Base>&& rhs) {
    locint resloc = get_next_loc();
    trace_put_ollb<Base>(log_a, resloc, rhs.loc, rhs.val);
    rhs.val = log(rhs.val);
    rhs.loc = resloc;
    return std::move(rhs);
  }

#endif // REVERSE_AD_CPP11
