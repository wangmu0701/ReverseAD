  // All assignment related operations:
  // value c-tor, copy c-tor, d-tor, assign_a, assign_d, assign_dep, assign_ind
  explicit BaseActive() {
    this->val = 0.0;
    this->loc = get_next_loc();
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "V-ctor: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
#endif
    trace_put_old<Base>(assign_d, this->loc, 0.0);
  }

  ~BaseActive() {
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "free loc: " << this << "["<<this->loc<<"]" << std::endl;
#endif
  }

  BaseActive(const double& val) {
    this->val = val;
    this->loc = get_next_loc();
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "V-ctor: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
#endif
    trace_put_old<Base>(assign_d, this->loc, val);
  }
  
  // copy c-tor
  BaseActive(const BaseActive<Base>& other) {
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L-ctor: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
#endif
    this->val = other.val;
    this->loc = get_next_loc();
    trace_put_oll<Base>(assign_a, this->loc, other.loc);
  }

  BaseActive<Base>& operator=(BaseActive<Base> other) {
    swap(*this, other);
    return *this;
  } 

  void markDummyInd(const Base& val) {
    this->val = val;
    this->loc = get_next_dummy_loc();
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "dummy ind: " << this << "[" << this->loc << "] = "
             << val << std::endl;
#endif
    trace_put_olb<Base>(assign_ind, this->loc, val);
  }

  void markRemoteInd(const Base& val, const locint& loc) {
    this->val = val;
    this->loc = loc;
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "remote ind: " << this << "[" << this->loc << "] = "
             << val << std::endl;
#endif
    trace_put_olb<Base>(assign_ind, this->loc, val);
  }

  BaseActive<Base>& operator <<= (const Base& val) {
    this->val = val;
    this->loc = get_next_ind_loc();
    trace_put_olb<Base>(assign_ind, this->loc, val);
    trace_declare_ind<Base>();
    return *this;
  }

  BaseActive<Base>& operator >>= (Base& val) {
    val = this->val;
    trace_put_olb<Base>(assign_dep, this->loc, val);
    trace_declare_dep<Base>();
    return *this;
  }

/*
  // value assignment
  BaseActive<Base>& operator = (const double& val) {
    this->val = val;
    this->loc = get_next_loc();
    trace_put_old<Base>(assign_d, this->loc, val);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "V-assign: " << this <<"["<<this->loc<<"]" << " = " << val << std::endl;
#endif
    return *this;
  }
*/
/*
  // copy assignment
  BaseActive<Base>& operator = (const BaseActive<Base>& other) {
    if (this != (&other)) {
      this->val = other.val;
      this->loc = get_next_loc();
    }
    trace_put_oll<Base>(assign_a, this->loc, other.loc);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "L-assign: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
#endif
    return *this;
  }
*/

#ifdef REVERSE_AD_CPP11 
  // move c-tor
  BaseActive(BaseActive<Base>&& other) {
    this->val = other.val;
    this->loc = get_next_loc();
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R-ctor: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
#endif
    trace_put_oll<Base>(assign_a, this->loc, other.loc);
  }

/*
  // move assignment
  BaseActive<Base>& operator = (const BaseActive<Base>&& other) {
    if (this != &other) {
      this->val = other.val;
      this->loc = get_next_loc();
    }
    trace_put_oll<Base>(assign_a, this->loc, other.loc);
#ifdef REVERSEAD_BASE_ACTIVE_DEBUG
    logger.info << "R-assign: " << this <<"["<<this->loc<<"]" 
              <<" <- " << &other <<"["<<other.loc<<"]"<< std::endl;
#endif
    return *this;
  }
*/
#endif
