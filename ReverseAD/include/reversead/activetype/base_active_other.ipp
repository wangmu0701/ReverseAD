  // fabs
  friend BaseActive<Base> fabs(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(fabs(rhs.val), get_next_loc());
    trace_put_ollb(fabs_a, res.loc, rhs.loc, rhs.val);
    return res;
  }
  // erf
  friend BaseActive<Base> erf(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(erf(rhs.val), get_next_loc());
    trace_put_ollb(erf_a, res.loc, rhs.loc, rhs.val);
    return res;
  }
