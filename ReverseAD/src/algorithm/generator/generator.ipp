inline void generator_unary_1_1_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
}

inline void generator_unary_1_1_1(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
}

inline void generator_unary_1_1_2(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
}

inline void generator_unary_2_1_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
}

inline void generator_unary_2_1_1(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,2);
  w=3.0*sw*ginfo.pxx;
  global_deriv.increase(D, w);
}

inline void generator_unary_2_2_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

inline void generator_unary_2_2_1(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,2);
  w=3.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

inline void generator_unary_3_1_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
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

inline void generator_unary_3_2_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,2);
  w=1.0*sw*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,3);
  w=3.0*sw*ginfo.dx*ginfo.pxx;
  global_deriv.increase(D, w);
}

inline void generator_unary_3_3_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,3);
  w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
  global_deriv.increase(D, w);
}

inline void generator_binary_1_1_0_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

inline void generator_binary_1_1_0_1(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

inline void generator_binary_1_1_0_2(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=1.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=3.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

inline void generator_binary_1_1_1_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

inline void generator_binary_1_1_1_1(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=2.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=2.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

inline void generator_binary_1_1_2_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
  D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
  w=3.0*sw*ginfo.dx;
  global_deriv.increase(D, w);
  D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
  w=1.0*sw*ginfo.dy;
  global_deriv.increase(D, w);
}

inline void generator_binary_2_1_0_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
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

inline void generator_binary_2_1_0_1(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
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

inline void generator_binary_2_1_1_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
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

inline void generator_binary_2_2_0_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
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

inline void generator_binary_2_2_0_1(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
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

inline void generator_binary_2_2_1_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
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

inline void generator_binary_3_1_0_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
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

inline void generator_binary_3_2_0_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
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

inline void generator_binary_3_3_0_0(const ReverseADMultiSet<locint>& Z, const double& sw, const GeneratorInfo<locint, double>& ginfo, GenericDeriv<locint, double>& global_deriv) {
  ReverseADMultiSet<locint> D;
  double w;
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

