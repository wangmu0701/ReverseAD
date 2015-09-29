  // All assignment related operations:
  // value c-tor, copy c-tor, d-tor, assign_a, assign_d, assign_dep, assign_ind
  BaseActive() {
    this->val = 0.0;
    this->loc = get_next_loc();
    log.info << "V-ctor: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
    trace_put(assign_d, this->loc, 0.0);
  }
  ~BaseActive() {
    log.info << "free loc: " << this << "["<<this->loc<<"]" << std::endl;
  }

  // value c-tor
  BaseActive(Base val) {
    this->val = val;
    this->loc = get_next_loc();
    log.info << "V-ctor: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
    trace_put(assign_d, this->loc, val);
  }
  
  // copy c-tor
  BaseActive(const BaseActive<Base>& other) {
    log.info << "L-ctor: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
    this->val = other.val;
    this->loc = get_next_loc();
    trace_put(assign_a, this->loc, other.loc);
  }

  void markDummyInd(const Base& val) {
    this->val = val;
    this->loc = get_next_dummy_loc();
    log.info << "dummy ind: " << this << "[" << this->loc << "] = "
             << val << std::endl;
    trace_put(assign_ind, this->loc, val);
  }

  void markRemoteInd(const Base& val, const locint& loc) {
    this->val = val;
    this->loc = loc;
    log.info << "remote ind: " << this << "[" << this->loc << "] = "
             << val << std::endl;
    trace_put(assign_ind, this->loc, val);
  }

  BaseActive<Base>& operator <<= (const Base& val) {
    this->val = val;
    this->loc = get_next_ind_loc();
    trace_put(assign_ind, this->loc, val);
    return *this;
  }

  BaseActive<Base>& operator >>= (Base& val) {
    std::cout << "this->val = " << this->val << std::endl;
    val = this->val;
    trace_put(assign_dep, this->loc, val);
    return *this;
  }

  // value assignment
  BaseActive<Base>& operator = (Base val) {
    this->val = val;
    this->loc = get_next_loc();
    trace_put(assign_d, this->loc, val);
    log.info << "V-assign: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
    return *this;
  }

  // copy assignment
  BaseActive<Base>& operator = (const BaseActive<Base>& other) {
    log.info << this << " ==? " << (&other) << std::endl;
    if (this != (&other)) {
      this->val = other.val;
      this->loc = get_next_loc();
      log.info << "this.val = " << this->val << std::endl;
      log.info << "other.val = " << other.val << std::endl; 
    }

    trace_put(assign_a, this->loc, other.loc);
    log.info << "L-assign: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
    return *this;
  }

  // I guess we can safely reuse the location assigned to a r-value?
#ifdef REVERSE_AD_CPP11 
  // move c-tor
  BaseActive(BaseActive<Base>&& other) {
    this->val = other.val;
    this->loc = get_next_loc();
    log.info << "R-ctor: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
    trace_put(assign_a, this->loc, other.loc);
  }

  // move assignment
  BaseActive<Base>& operator = (const BaseActive<Base>&& other) {
    if (this != &other) {
      this->val = other.val;
      this->loc = get_next_loc();
    }
    trace_put(assign_a, this->loc, other.loc);
    log.info << "R-assign: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
    return *this;
  }
#endif
