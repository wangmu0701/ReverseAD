
void generator_binary(const ReverseADMultiSet& Z,
                      int r,
                      int x_count, int y_count,
                      int order, double sw,
                      const GeneratorInfo<locint, double>& ginfo,
                      GenericDeriv<locint, double>& global_deriv) {
}


void generator_unary(const ReverseADMultiSet& Z,
                     int r,
                     int x_count,
                     int order, double sw,
                     const GeneratorInfo<locint, double>& ginfo,
                     GenericDeriv<locint, double>& global_deriv) {
  switch (order) {
    case 1:
      generator_unary_1_1_0(Z, sw, ginfo, global_deriv);
      break;
    case 2:
      switch (r) {
        case 1:
          switch (x_count) {
            case 0:
              generator_unary_2_1_0(Z, sw, ginfo, global_deriv);
              break;
            case 1:
              generator_unary_2_1_1(Z, sw, ginfo, global_deriv);
              break;
            default:
              break;
          }
          break;
        case 2:
          generator_unary_2_2_0(Z, sw, ginfo, global_deriv);
          break;
        default:
          break;
      }
      break;
    case 3:
      break;
    default:
  }
}

//generator_unary_#order_#r_#xcount(Z, sw, ginfo, global_deriv)

