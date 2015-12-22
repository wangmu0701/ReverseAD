  // ==, !=, <, >, <=, >=
  // put rhs.loc before lhs.loc because the order in olld<Base>
  friend bool operator == (const BaseActive<Base>& lhs,
                           const BaseActive<Base>& rhs) {
    bool ret = (lhs.val == rhs.val);
    double coval = (ret?1.0:0.0);
    trace_put_olld<Base>(comp_eq, rhs.loc, lhs.loc, coval);
    return ret;
  }
  friend bool operator != (const BaseActive<Base>& lhs,
                           const BaseActive<Base>& rhs) {
    return !operator==(lhs,rhs);
  }
  friend bool operator < (const BaseActive<Base>& lhs,
                          const BaseActive<Base>& rhs) {
    bool ret = (lhs.val < rhs.val);
    double coval = (ret?1.0:0.0);
    trace_put_olld<Base>(comp_lt, rhs.loc, lhs.loc, coval);
    return ret;
  }
  friend bool operator > (const BaseActive<Base>& lhs,
                          const BaseActive<Base>& rhs) {
    return operator<(rhs, lhs);
  }
  friend bool operator <= (const BaseActive<Base>& lhs,
                           const BaseActive<Base>& rhs) {
    return !operator>(lhs, rhs);
  }
  friend bool operator >= (const BaseActive<Base>& lhs,
                           const BaseActive<Base>& rhs) {
    return !operator<(lhs, rhs);
  }
