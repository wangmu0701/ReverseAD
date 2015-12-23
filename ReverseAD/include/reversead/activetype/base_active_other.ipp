  // fabs
  friend BaseActive<Base> fabs(const BaseActive<Base>& rhs) {
    BaseActive<Base> res(fabs(rhs.val), get_next_loc());
    trace_put_ollb(fabs_a, res.loc, rhs.loc, rhs.val);
    return res;
  }
