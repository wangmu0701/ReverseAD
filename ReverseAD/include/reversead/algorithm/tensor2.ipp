template <typename Base>
void unary_case_1010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_1010100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_1010200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_1010300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=4.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_1010400(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=5.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_1010500(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=6.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_2010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_2010100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_2010200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=6.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_2010300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=4.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=10.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_2010400(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=5.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=15.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_2020000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_2020100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_2020200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=6.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_2020300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=10.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_2020400(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=15.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3010100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=4.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3010200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=6.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=10.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3010300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=4.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=10.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=20.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3020000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3020100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=12.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3020200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=6.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=30.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3020300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=10.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=60.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3030000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3030100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3030200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_3030300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3);
  w=20.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=1.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4010100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=4.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=5.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4010200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=6.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=10.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=15.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4020000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=4.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=3.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4020100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=12.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=20.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=15.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4020200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=6.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=30.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=60.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=45.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4030000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4030100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=30.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4030200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=90.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4040000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4040100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4);
  w=5.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_4040200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4);
  w=15.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_5010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=1.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=1.0*sw*ginfo.pxxxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_5010100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=4.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=5.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=6.0*sw*ginfo.pxxxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_5020000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=4.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=5.0*sw*ginfo.dx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=3.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=10.0*sw*ginfo.pxx*ginfo.pxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_5020100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=12.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=20.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=30.0*sw*ginfo.dx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=15.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=60.0*sw*ginfo.pxx*ginfo.pxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_5030000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=15.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_5030100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=30.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=60.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=90.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_5040000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_5040100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4);
  w=5.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=60.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_5050000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,5);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_5050100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,5);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_6010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=1.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=1.0*sw*ginfo.pxxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6);
  w=1.0*sw*ginfo.pxxxxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_6020000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=4.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=5.0*sw*ginfo.dx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6);
  w=6.0*sw*ginfo.dx*ginfo.pxxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=3.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=10.0*sw*ginfo.pxx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6);
  w=15.0*sw*ginfo.pxx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6);
  w=10.0*sw*ginfo.pxxx*ginfo.pxxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_6030000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6);
  w=15.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=15.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6);
  w=60.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6);
  w=15.0*sw*ginfo.pxx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_6040000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6);
  w=20.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6);
  w=45.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_6050000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,5);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6);
  w=15.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

template <typename Base>
void unary_case_6060000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,6);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010002(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010003(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010004(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010005(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010101(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010102(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010103(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010104(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010201(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010202(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010203(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010301(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010302(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010400(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010401(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_1010500(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010002(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010003(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=10.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010004(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=15.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010101(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010102(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010103(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=10.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010201(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010202(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=9.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010301(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2010400(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020002(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020003(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=10.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020004(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=15.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020101(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020102(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020103(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=10.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020201(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020202(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=9.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020301(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_2020400(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3010001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3010002(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=10.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3010003(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=10.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=10.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=20.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3010100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3010101(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3010102(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=9.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=10.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3010200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3010201(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3010300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=20.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3020000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3020001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3020002(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=30.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3020003(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=10.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=10.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=20.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=60.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3020100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=12.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3020101(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=12.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3020102(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=12.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=18.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=9.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=24.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=30.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3020200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=30.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3020201(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=30.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=24.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=18.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3020300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=60.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=20.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=8.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3030000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3030001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3030002(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3030003(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=10.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=20.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3030100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3030101(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3030102(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=9.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3030200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3030201(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_3030300(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=20.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.pyyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4010001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=5.0*sw*ginfo.pyyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4010002(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=10.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=10.0*sw*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=15.0*sw*ginfo.pyyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4010100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=2.0*sw*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.pyyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4010101(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=8.0*sw*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=5.0*sw*ginfo.pyyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4010200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.pyyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4020000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=3.0*sw*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4020001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=20.0*sw*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=15.0*sw*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4020002(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=9.0*sw*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=10.0*sw*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=30.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=30.0*sw*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=60.0*sw*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=9.0*sw*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=30.0*sw*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=45.0*sw*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4020100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=12.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=20.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=2.0*sw*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=3.0*sw*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4020101(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=12.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=20.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=24.0*sw*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=18.0*sw*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=8.0*sw*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=18.0*sw*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=24.0*sw*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=20.0*sw*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=24.0*sw*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=18.0*sw*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=24.0*sw*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=15.0*sw*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4020200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=30.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=60.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=30.0*sw*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=45.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=30.0*sw*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=3.0*sw*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4030000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4030001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=30.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4030002(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=9.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=9.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=24.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=30.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=30.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=90.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4030100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=30.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4030101(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=30.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=24.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=24.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=36.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=24.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=24.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=30.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4030200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=90.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=30.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=30.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=24.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4040000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4040001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=5.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4040002(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=10.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=15.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4040100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=2.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4040101(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=8.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=5.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_4040200(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pxxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.pxyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=1.0*sw*ginfo.pyyyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5010001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=5.0*sw*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.pxxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=5.0*sw*ginfo.pxyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=6.0*sw*ginfo.pyyyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5010100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=2.0*sw*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.pxxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.pxxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.pxxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.pxxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=2.0*sw*ginfo.pxyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=1.0*sw*ginfo.pyyyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5020000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.dx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=2.0*sw*ginfo.dx*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dx*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dy*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=5.0*sw*ginfo.dy*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.pxx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pxx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.pxy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.pxy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=3.0*sw*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.pyy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.pyy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.pyy*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5020001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.dx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.dx*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.dx*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=8.0*sw*ginfo.dx*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=5.0*sw*ginfo.dx*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=20.0*sw*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=20.0*sw*ginfo.dy*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=30.0*sw*ginfo.dy*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.pxx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.pxx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.pxx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.pxx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.pxy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=18.0*sw*ginfo.pxy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=24.0*sw*ginfo.pxy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=20.0*sw*ginfo.pxy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=15.0*sw*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pyy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.pyy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=30.0*sw*ginfo.pyy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=60.0*sw*ginfo.pyy*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5020100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=12.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=20.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=2.0*sw*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=30.0*sw*ginfo.dx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=20.0*sw*ginfo.dx*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dx*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=2.0*sw*ginfo.dx*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.dy*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=8.0*sw*ginfo.dy*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dy*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=8.0*sw*ginfo.dy*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=5.0*sw*ginfo.dy*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=60.0*sw*ginfo.pxx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=30.0*sw*ginfo.pxx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.pxx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.pxx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=20.0*sw*ginfo.pxy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=24.0*sw*ginfo.pxy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=18.0*sw*ginfo.pxy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=8.0*sw*ginfo.pxy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=3.0*sw*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.pyy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.pyy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=12.0*sw*ginfo.pyy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.pyy*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5030000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dx*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=3.0*sw*ginfo.dx*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dy*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=12.0*sw*ginfo.dy*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=15.0*sw*ginfo.dy*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5030001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.dx*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=18.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=24.0*sw*ginfo.dx*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=20.0*sw*ginfo.dx*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=24.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.dx*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=18.0*sw*ginfo.dx*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=24.0*sw*ginfo.dx*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=15.0*sw*ginfo.dx*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=30.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=30.0*sw*ginfo.dy*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=60.0*sw*ginfo.dy*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=18.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dy*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=24.0*sw*ginfo.dy*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=60.0*sw*ginfo.dy*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=90.0*sw*ginfo.dy*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5030100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=30.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=60.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=30.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=20.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=24.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=18.0*sw*ginfo.dx*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=8.0*sw*ginfo.dx*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=90.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=60.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=24.0*sw*ginfo.dx*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=18.0*sw*ginfo.dx*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dx*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=12.0*sw*ginfo.dy*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=15.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=24.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dy*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=18.0*sw*ginfo.dy*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=24.0*sw*ginfo.dy*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=15.0*sw*ginfo.dy*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5040000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5040001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=8.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=18.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=12.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=9.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=24.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=30.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=5.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=20.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=60.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5040100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=60.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=20.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=30.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=24.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=2.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=18.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=8.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5050000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5050001(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=5.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_5050100(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=2.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_6010000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pxxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.pxyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=1.0*sw*ginfo.pyyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.pxxxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.pxxxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxxxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pxxxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.pxxyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=1.0*sw*ginfo.pxyyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=1.0*sw*ginfo.pyyyyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_6020000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=4.0*sw*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=5.0*sw*ginfo.dx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=2.0*sw*ginfo.dx*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dx*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.pxxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.dx*ginfo.pxxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.pxxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.pxxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=2.0*sw*ginfo.dx*ginfo.pxyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=1.0*sw*ginfo.dx*ginfo.pyyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dy*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=5.0*sw*ginfo.dy*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy*ginfo.pxxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.dy*ginfo.pxxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pxxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.pxxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=5.0*sw*ginfo.dy*ginfo.pxyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=6.0*sw*ginfo.dy*ginfo.pyyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.pxx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.pxx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pxx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.pxx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.pxx*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxx*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.pxx*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.pxx*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=2.0*sw*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.pxy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.pxy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.pxy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.pxy*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=8.0*sw*ginfo.pxy*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.pxy*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=8.0*sw*ginfo.pxy*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=5.0*sw*ginfo.pxy*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=3.0*sw*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.pyy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.pyy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.pyy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.pyy*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.pyy*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.pyy*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.pyy*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=15.0*sw*ginfo.pyy*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.pxxx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.pxxx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.pxxx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.pxxx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.pxxy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.pxxy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.pxxy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.pxyy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.pxyy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=10.0*sw*ginfo.pyyy*ginfo.pyyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_6030000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=8.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dx*ginfo.dy*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=8.0*sw*ginfo.dx*ginfo.dy*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=5.0*sw*ginfo.dx*ginfo.dy*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=12.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=60.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=30.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.pxx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.pxx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dx*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=20.0*sw*ginfo.dx*ginfo.pxy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=24.0*sw*ginfo.dx*ginfo.pxy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=18.0*sw*ginfo.dx*ginfo.pxy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=8.0*sw*ginfo.dx*ginfo.pxy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=3.0*sw*ginfo.dx*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.pyy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dx*ginfo.pyy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=12.0*sw*ginfo.dx*ginfo.pyy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dx*ginfo.pyy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pxxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.pxyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=15.0*sw*ginfo.dy*ginfo.dy*ginfo.pyyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dy*ginfo.pxx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.pxx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dy*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=12.0*sw*ginfo.dy*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=8.0*sw*ginfo.dy*ginfo.pxy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=18.0*sw*ginfo.dy*ginfo.pxy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=24.0*sw*ginfo.dy*ginfo.pxy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=20.0*sw*ginfo.dy*ginfo.pxy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=15.0*sw*ginfo.dy*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dy*ginfo.pyy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=12.0*sw*ginfo.dy*ginfo.pyy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=30.0*sw*ginfo.dy*ginfo.pyy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=60.0*sw*ginfo.dy*ginfo.pyy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.pxx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=15.0*sw*ginfo.pxx*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.pxx*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.pxx*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.pxx*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=3.0*sw*ginfo.pxx*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.pxy*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=12.0*sw*ginfo.pxy*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=15.0*sw*ginfo.pxy*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=15.0*sw*ginfo.pyy*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_6040000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=20.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=45.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=30.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=12.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dx*ginfo.dx*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=4.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=12.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=15.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=24.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dx*ginfo.dy*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=18.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=24.0*sw*ginfo.dx*ginfo.dy*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=15.0*sw*ginfo.dx*ginfo.dy*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=4.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=20.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pyyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=3.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dy*ginfo.dy*ginfo.pxx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=12.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=30.0*sw*ginfo.dy*ginfo.dy*ginfo.pxy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=45.0*sw*ginfo.dy*ginfo.dy*ginfo.pyy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_6050000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=15.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=5.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=10.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=8.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=9.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=3.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=8.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=10.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,5);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=5.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pxy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=15.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.pyy;
  global_deriv.increase(D, w);
}

template <typename Base>
void binary_case_6060000(const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> D;
  Base w;
  D = Z; D.insert(ginfo.x,6); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,5); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,4); D.insert(ginfo.y,2);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3); D.insert(ginfo.y,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2); D.insert(ginfo.y,4);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,5);
  w=1.0*sw*ginfo.dx*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,6);
  w=1.0*sw*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy*ginfo.dy;
  global_deriv.increase(D, w);
}

template <typename Base>
void generator_unary (size_t caseCode, const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  switch (caseCode) {
    case 1010000 : 
      {
        unary_case_1010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010100 : 
      {
        unary_case_1010100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010200 : 
      {
        unary_case_1010200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010300 : 
      {
        unary_case_1010300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010400 : 
      {
        unary_case_1010400(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010500 : 
      {
        unary_case_1010500(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010000 : 
      {
        unary_case_2010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010100 : 
      {
        unary_case_2010100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010200 : 
      {
        unary_case_2010200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010300 : 
      {
        unary_case_2010300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010400 : 
      {
        unary_case_2010400(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020000 : 
      {
        unary_case_2020000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020100 : 
      {
        unary_case_2020100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020200 : 
      {
        unary_case_2020200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020300 : 
      {
        unary_case_2020300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020400 : 
      {
        unary_case_2020400(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010000 : 
      {
        unary_case_3010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010100 : 
      {
        unary_case_3010100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010200 : 
      {
        unary_case_3010200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010300 : 
      {
        unary_case_3010300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020000 : 
      {
        unary_case_3020000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020100 : 
      {
        unary_case_3020100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020200 : 
      {
        unary_case_3020200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020300 : 
      {
        unary_case_3020300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030000 : 
      {
        unary_case_3030000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030100 : 
      {
        unary_case_3030100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030200 : 
      {
        unary_case_3030200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030300 : 
      {
        unary_case_3030300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4010000 : 
      {
        unary_case_4010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4010100 : 
      {
        unary_case_4010100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4010200 : 
      {
        unary_case_4010200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4020000 : 
      {
        unary_case_4020000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4020100 : 
      {
        unary_case_4020100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4020200 : 
      {
        unary_case_4020200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4030000 : 
      {
        unary_case_4030000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4030100 : 
      {
        unary_case_4030100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4030200 : 
      {
        unary_case_4030200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4040000 : 
      {
        unary_case_4040000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4040100 : 
      {
        unary_case_4040100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4040200 : 
      {
        unary_case_4040200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5010000 : 
      {
        unary_case_5010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5010100 : 
      {
        unary_case_5010100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5020000 : 
      {
        unary_case_5020000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5020100 : 
      {
        unary_case_5020100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5030000 : 
      {
        unary_case_5030000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5030100 : 
      {
        unary_case_5030100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5040000 : 
      {
        unary_case_5040000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5040100 : 
      {
        unary_case_5040100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5050000 : 
      {
        unary_case_5050000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5050100 : 
      {
        unary_case_5050100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6010000 : 
      {
        unary_case_6010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6020000 : 
      {
        unary_case_6020000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6030000 : 
      {
        unary_case_6030000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6040000 : 
      {
        unary_case_6040000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6050000 : 
      {
        unary_case_6050000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6060000 : 
      {
        unary_case_6060000(Z, sw, ginfo, global_deriv);
      }
      break;
    default:
      std::cout << "unrecongized case code = " << caseCode << std::endl;
  }
}

template <typename Base>
void generator_binary (size_t caseCode, const TensorIndex<locint>& Z, const Base& sw, const TensorDerivativeInfo<locint, Base>& ginfo, TensorDeriv<locint, Base>& global_deriv) {
  switch (caseCode) {
    case 1010000 : 
      {
        binary_case_1010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010001 : 
      {
        binary_case_1010001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010002 : 
      {
        binary_case_1010002(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010003 : 
      {
        binary_case_1010003(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010004 : 
      {
        binary_case_1010004(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010005 : 
      {
        binary_case_1010005(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010100 : 
      {
        binary_case_1010100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010101 : 
      {
        binary_case_1010101(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010102 : 
      {
        binary_case_1010102(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010103 : 
      {
        binary_case_1010103(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010104 : 
      {
        binary_case_1010104(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010200 : 
      {
        binary_case_1010200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010201 : 
      {
        binary_case_1010201(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010202 : 
      {
        binary_case_1010202(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010203 : 
      {
        binary_case_1010203(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010300 : 
      {
        binary_case_1010300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010301 : 
      {
        binary_case_1010301(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010302 : 
      {
        binary_case_1010302(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010400 : 
      {
        binary_case_1010400(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010401 : 
      {
        binary_case_1010401(Z, sw, ginfo, global_deriv);
      }
      break;
    case 1010500 : 
      {
        binary_case_1010500(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010000 : 
      {
        binary_case_2010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010001 : 
      {
        binary_case_2010001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010002 : 
      {
        binary_case_2010002(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010003 : 
      {
        binary_case_2010003(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010004 : 
      {
        binary_case_2010004(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010100 : 
      {
        binary_case_2010100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010101 : 
      {
        binary_case_2010101(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010102 : 
      {
        binary_case_2010102(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010103 : 
      {
        binary_case_2010103(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010200 : 
      {
        binary_case_2010200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010201 : 
      {
        binary_case_2010201(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010202 : 
      {
        binary_case_2010202(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010300 : 
      {
        binary_case_2010300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010301 : 
      {
        binary_case_2010301(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2010400 : 
      {
        binary_case_2010400(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020000 : 
      {
        binary_case_2020000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020001 : 
      {
        binary_case_2020001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020002 : 
      {
        binary_case_2020002(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020003 : 
      {
        binary_case_2020003(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020004 : 
      {
        binary_case_2020004(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020100 : 
      {
        binary_case_2020100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020101 : 
      {
        binary_case_2020101(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020102 : 
      {
        binary_case_2020102(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020103 : 
      {
        binary_case_2020103(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020200 : 
      {
        binary_case_2020200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020201 : 
      {
        binary_case_2020201(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020202 : 
      {
        binary_case_2020202(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020300 : 
      {
        binary_case_2020300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020301 : 
      {
        binary_case_2020301(Z, sw, ginfo, global_deriv);
      }
      break;
    case 2020400 : 
      {
        binary_case_2020400(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010000 : 
      {
        binary_case_3010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010001 : 
      {
        binary_case_3010001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010002 : 
      {
        binary_case_3010002(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010003 : 
      {
        binary_case_3010003(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010100 : 
      {
        binary_case_3010100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010101 : 
      {
        binary_case_3010101(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010102 : 
      {
        binary_case_3010102(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010200 : 
      {
        binary_case_3010200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010201 : 
      {
        binary_case_3010201(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3010300 : 
      {
        binary_case_3010300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020000 : 
      {
        binary_case_3020000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020001 : 
      {
        binary_case_3020001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020002 : 
      {
        binary_case_3020002(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020003 : 
      {
        binary_case_3020003(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020100 : 
      {
        binary_case_3020100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020101 : 
      {
        binary_case_3020101(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020102 : 
      {
        binary_case_3020102(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020200 : 
      {
        binary_case_3020200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020201 : 
      {
        binary_case_3020201(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3020300 : 
      {
        binary_case_3020300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030000 : 
      {
        binary_case_3030000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030001 : 
      {
        binary_case_3030001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030002 : 
      {
        binary_case_3030002(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030003 : 
      {
        binary_case_3030003(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030100 : 
      {
        binary_case_3030100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030101 : 
      {
        binary_case_3030101(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030102 : 
      {
        binary_case_3030102(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030200 : 
      {
        binary_case_3030200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030201 : 
      {
        binary_case_3030201(Z, sw, ginfo, global_deriv);
      }
      break;
    case 3030300 : 
      {
        binary_case_3030300(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4010000 : 
      {
        binary_case_4010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4010001 : 
      {
        binary_case_4010001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4010002 : 
      {
        binary_case_4010002(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4010100 : 
      {
        binary_case_4010100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4010101 : 
      {
        binary_case_4010101(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4010200 : 
      {
        binary_case_4010200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4020000 : 
      {
        binary_case_4020000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4020001 : 
      {
        binary_case_4020001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4020002 : 
      {
        binary_case_4020002(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4020100 : 
      {
        binary_case_4020100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4020101 : 
      {
        binary_case_4020101(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4020200 : 
      {
        binary_case_4020200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4030000 : 
      {
        binary_case_4030000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4030001 : 
      {
        binary_case_4030001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4030002 : 
      {
        binary_case_4030002(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4030100 : 
      {
        binary_case_4030100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4030101 : 
      {
        binary_case_4030101(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4030200 : 
      {
        binary_case_4030200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4040000 : 
      {
        binary_case_4040000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4040001 : 
      {
        binary_case_4040001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4040002 : 
      {
        binary_case_4040002(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4040100 : 
      {
        binary_case_4040100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4040101 : 
      {
        binary_case_4040101(Z, sw, ginfo, global_deriv);
      }
      break;
    case 4040200 : 
      {
        binary_case_4040200(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5010000 : 
      {
        binary_case_5010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5010001 : 
      {
        binary_case_5010001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5010100 : 
      {
        binary_case_5010100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5020000 : 
      {
        binary_case_5020000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5020001 : 
      {
        binary_case_5020001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5020100 : 
      {
        binary_case_5020100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5030000 : 
      {
        binary_case_5030000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5030001 : 
      {
        binary_case_5030001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5030100 : 
      {
        binary_case_5030100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5040000 : 
      {
        binary_case_5040000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5040001 : 
      {
        binary_case_5040001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5040100 : 
      {
        binary_case_5040100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5050000 : 
      {
        binary_case_5050000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5050001 : 
      {
        binary_case_5050001(Z, sw, ginfo, global_deriv);
      }
      break;
    case 5050100 : 
      {
        binary_case_5050100(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6010000 : 
      {
        binary_case_6010000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6020000 : 
      {
        binary_case_6020000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6030000 : 
      {
        binary_case_6030000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6040000 : 
      {
        binary_case_6040000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6050000 : 
      {
        binary_case_6050000(Z, sw, ginfo, global_deriv);
      }
      break;
    case 6060000 : 
      {
        binary_case_6060000(Z, sw, ginfo, global_deriv);
      }
      break;
    default:
      std::cout << "unrecongized case code = " << caseCode << std::endl;
  }
}

