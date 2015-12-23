  // +a, -a, ++a, a++, --a, a--
  BaseActive<Base> operator+() const {
    BaseActive<Base> ret(*this);
    return ret;
  }
  BaseActive<Base> operator-() const {
    BaseActive<Base> ret = 0.0 - *this;
    return ret;
  }
  BaseActive<Base>& operator++() {
    locint resloc = get_next_loc();
    trace_put_olld<Base>(eq_plus_d, resloc, this->loc, 1.0);
    this->val += 1.0;
    this->loc = resloc;
    return *this;
  }
  BaseActive<Base> operator++(int) {
    BaseActive<Base> ret(this->val, this->loc);
    locint resloc = get_next_loc();
    trace_put_olld<Base>(eq_plus_d, resloc, this->loc, 1.0);
    this->val += 1.0;
    this->loc = resloc;
    return ret;
  }

  BaseActive<Base>& operator--() {
    locint resloc = get_next_loc();
    trace_put_olld<Base>(eq_plus_d, resloc, this->loc, -1.0);
    this->val -= 1.0;
    this->loc = resloc;
    return *this;
  }
  BaseActive<Base> operator--(int) {
    BaseActive<Base> ret(this->val-1.0, this->loc);
    locint resloc = get_next_loc();
    trace_put_olld<Base>(eq_plus_d, ret.loc, this->loc, -1.0);
    this->val -= 1.0;
    this->loc = resloc;
    return ret;
  }
