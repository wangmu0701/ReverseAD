  // All assignment related operations:
  // value c-tor, copy c-tor, d-tor, assign_a, assign_d, assign_dep, assign_ind
  BaseActive() {
    this->val = 0.0;
    this->loc = get_next_loc();
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "V-ctor: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
#endif
    trace_put(assign_d, this->loc, 0.0);
  }
  ~BaseActive() {
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "free loc: " << this << "["<<this->loc<<"]" << std::endl;
#endif
  }

  // value c-tor
  BaseActive(Base val) {
    this->val = val;
    this->loc = get_next_loc();
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "V-ctor: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
#endif
    trace_put(assign_d, this->loc, val);
  }
  
  // copy c-tor
  BaseActive(const BaseActive<Base>& other) {
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "L-ctor: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
#endif
    this->val = other.val;
    this->loc = get_next_loc();
    trace_put(assign_a, this->loc, other.loc);
  }

  void markDummyInd(const Base& val) {
    this->val = val;
    this->loc = get_next_dummy_loc();
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "dummy ind: " << this << "[" << this->loc << "] = "
             << val << std::endl;
#endif
    trace_put(assign_ind, this->loc, val);
  }

  void markRemoteInd(const Base& val, const locint& loc) {
    this->val = val;
    this->loc = loc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "remote ind: " << this << "[" << this->loc << "] = "
             << val << std::endl;
#endif
    trace_put(assign_ind, this->loc, val);
  }

  BaseActive<Base>& operator <<= (const Base& val) {
    this->val = val;
    this->loc = get_next_ind_loc();
    trace_put(assign_ind, this->loc, val);
    return *this;
  }

  BaseActive<Base>& operator >>= (Base& val) {
    val = this->val;
    trace_put(assign_dep, this->loc, val);
    return *this;
  }

  // value assignment
  BaseActive<Base>& operator = (Base val) {
    this->val = val;
    this->loc = get_next_loc();
    trace_put(assign_d, this->loc, val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "V-assign: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
#endif
    return *this;
  }

  // copy assignment
  BaseActive<Base>& operator = (const BaseActive<Base>& other) {
    if (this != (&other)) {
      this->val = other.val;
      this->loc = get_next_loc();
    }
    trace_put(assign_a, this->loc, other.loc);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "L-assign: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
#endif
    return *this;
  }

#ifdef REVERSE_AD_CPP11 
  // move c-tor
  BaseActive(BaseActive<Base>&& other) {
    this->val = other.val;
    this->loc = get_next_loc();
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R-ctor: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
#endif
    trace_put(assign_a, this->loc, other.loc);
  }

  // move assignment
  BaseActive<Base>& operator = (const BaseActive<Base>&& other) {
    if (this != &other) {
      this->val = other.val;
      this->loc = get_next_loc();
    }
    trace_put(assign_a, this->loc, other.loc);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    log.info << "R-assign: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
#endif
    return *this;
  }
#endif
