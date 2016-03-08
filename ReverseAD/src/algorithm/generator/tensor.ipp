inline void generator_unary (int case_code, const TensorIndex<locint>& Z, const double& sw, const TensorInfo<locint, double>& ginfo, TensorDeriv<locint, double>& global_deriv) {
  TensorIndex<locint> D;
  double w;
  switch (case_code) {
    case 1010000 : 
      {
        D = Z; D.insert(ginfo.x,1);
        w=1.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
      }
      break;
    case 1010100 : 
      {
        D = Z; D.insert(ginfo.x,1);
        w=2.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
      }
      break;
    case 1010200 : 
      {
        D = Z; D.insert(ginfo.x,1);
        w=3.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
      }
      break;
    case 1010300 : 
      {
        D = Z; D.insert(ginfo.x,1);
        w=4.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
      }
      break;
    case 2010000 : 
      {
        D = Z; D.insert(ginfo.x,1);
        w=1.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,2);
        w=1.0*sw*ginfo.pxx;
        global_deriv.increase(D, w);
      }
      break;
    case 2010100 : 
      {
        D = Z; D.insert(ginfo.x,1);
        w=2.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,2);
        w=3.0*sw*ginfo.pxx;
        global_deriv.increase(D, w);
      }
      break;
    case 2010200 : 
      {
        D = Z; D.insert(ginfo.x,1);
        w=3.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,2);
        w=6.0*sw*ginfo.pxx;
        global_deriv.increase(D, w);
      }
      break;
    case 2020000 : 
      {
        D = Z; D.insert(ginfo.x,2);
        w=1.0*sw*ginfo.dx*ginfo.dx;
        global_deriv.increase(D, w);
      }
      break;
    case 2020100 : 
      {
        D = Z; D.insert(ginfo.x,2);
        w=3.0*sw*ginfo.dx*ginfo.dx;
        global_deriv.increase(D, w);
      }
      break;
    case 2020200 : 
      {
        D = Z; D.insert(ginfo.x,2);
        w=6.0*sw*ginfo.dx*ginfo.dx;
        global_deriv.increase(D, w);
      }
      break;
    case 3010000 : 
      {
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
      break;
    case 3010100 : 
      {
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
      break;
    case 3020000 : 
      {
        D = Z; D.insert(ginfo.x,2);
        w=1.0*sw*ginfo.dx*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,3);
        w=3.0*sw*ginfo.dx*ginfo.pxx;
        global_deriv.increase(D, w);
      }
      break;
    case 3020100 : 
      {
        D = Z; D.insert(ginfo.x,2);
        w=3.0*sw*ginfo.dx*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,3);
        w=12.0*sw*ginfo.dx*ginfo.pxx;
        global_deriv.increase(D, w);
      }
      break;
    case 3030000 : 
      {
        D = Z; D.insert(ginfo.x,3);
        w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
        global_deriv.increase(D, w);
      }
      break;
    case 3030100 : 
      {
        D = Z; D.insert(ginfo.x,3);
        w=4.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
        global_deriv.increase(D, w);
      }
      break;
    case 4010000 : 
      {
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
      break;
    case 4020000 : 
      {
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
      break;
    case 4030000 : 
      {
        D = Z; D.insert(ginfo.x,3);
        w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,4);
        w=6.0*sw*ginfo.dx*ginfo.dx*ginfo.pxx;
        global_deriv.increase(D, w);
      }
      break;
    case 4040000 : 
      {
        D = Z; D.insert(ginfo.x,4);
        w=1.0*sw*ginfo.dx*ginfo.dx*ginfo.dx*ginfo.dx;
        global_deriv.increase(D, w);
      }
      break;
    default:
      std::cout << "unrecongized case code = " << case_code << std::endl;
  }
}

inline void generator_binary (int case_code, const TensorIndex<locint>& Z, const double& sw, const TensorInfo<locint, double>& ginfo, TensorDeriv<locint, double>& global_deriv) {
  TensorIndex<locint> D;
  double w;
  switch (case_code) {
    case 1010000 : 
      {
        D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
        w=1.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
        w=1.0*sw*ginfo.dy;
        global_deriv.increase(D, w);
      }
      break;
    case 1010001 : 
      {
        D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
        w=1.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
        w=2.0*sw*ginfo.dy;
        global_deriv.increase(D, w);
      }
      break;
    case 1010002 : 
      {
        D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
        w=1.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
        w=3.0*sw*ginfo.dy;
        global_deriv.increase(D, w);
      }
      break;
    case 1010003 : 
      {
        D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
        w=1.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
        w=4.0*sw*ginfo.dy;
        global_deriv.increase(D, w);
      }
      break;
    case 1010100 : 
      {
        D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
        w=2.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
        w=1.0*sw*ginfo.dy;
        global_deriv.increase(D, w);
      }
      break;
    case 1010101 : 
      {
        D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
        w=2.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
        w=2.0*sw*ginfo.dy;
        global_deriv.increase(D, w);
      }
      break;
    case 1010102 : 
      {
        D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
        w=2.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
        w=3.0*sw*ginfo.dy;
        global_deriv.increase(D, w);
      }
      break;
    case 1010200 : 
      {
        D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
        w=3.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
        w=1.0*sw*ginfo.dy;
        global_deriv.increase(D, w);
      }
      break;
    case 1010201 : 
      {
        D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
        w=3.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
        w=2.0*sw*ginfo.dy;
        global_deriv.increase(D, w);
      }
      break;
    case 1010300 : 
      {
        D = Z; D.insert(ginfo.x,1); D.insert(ginfo.y,0);
        w=4.0*sw*ginfo.dx;
        global_deriv.increase(D, w);
        D = Z; D.insert(ginfo.x,0); D.insert(ginfo.y,1);
        w=1.0*sw*ginfo.dy;
        global_deriv.increase(D, w);
      }
      break;
    case 2010000 : 
      {
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
      break;
    case 2010001 : 
      {
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
      break;
    case 2010002 : 
      {
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
      break;
    case 2010100 : 
      {
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
      break;
    case 2010101 : 
      {
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
      break;
    case 2010200 : 
      {
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
      break;
    case 2020000 : 
      {
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
      break;
    case 2020001 : 
      {
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
      break;
    case 2020002 : 
      {
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
      break;
    case 2020100 : 
      {
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
      break;
    case 2020101 : 
      {
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
      break;
    case 2020200 : 
      {
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
      break;
    case 3010000 : 
      {
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
      break;
    case 3010001 : 
      {
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
      break;
    case 3010100 : 
      {
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
      break;
    case 3020000 : 
      {
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
      break;
    case 3020001 : 
      {
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
      break;
    case 3020100 : 
      {
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
      break;
    case 3030000 : 
      {
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
      break;
    case 3030001 : 
      {
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
      break;
    case 3030100 : 
      {
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
      break;
    case 4010000 : 
      {
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
      break;
    case 4020000 : 
      {
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
      break;
    case 4030000 : 
      {
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
      break;
    case 4040000 : 
      {
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
      break;
    default:
      std::cout << "unrecongized case code = " << case_code << std::endl;
  }
}

