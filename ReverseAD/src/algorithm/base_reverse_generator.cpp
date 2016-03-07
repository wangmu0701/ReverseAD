#include "reversead/algorithm/base_reverse_generator.hpp"

namespace ReverseAD {

#include "generator/generator.ipp"

template <typename Base>
BaseReverseGenerator<Base>::BaseReverseGenerator(
    const std::shared_ptr<TrivialTrace<Base>>& trace,
    int order) : BaseReverseGeneric<Base>(trace, order) {
  if (order > REVERSEAD_MAX_GENERATOR_ORDER) {
    std::cout << "Sorry, max order for generator should be less than "
              << REVERSEAD_MAX_GENERATOR_ORDER << "." << std::endl;
  }
  if (order <= 0) {
    std::cout << "Order(" << order << ") should be positive." << std::endl;
  }
}

template <typename Base>
void BaseReverseGenerator<Base>::process_sac(
    const DerivativeInfo<locint, Base>& info) {
  if (info.r != NULL_LOC) {
    GeneratorInfo<locint, Base> ginfo;
    fill_in_ginfo(info, ginfo);
    std::set<locint> dep_set = std::move(reverse_live[info.r]);
    reverse_live.erase(info.r);
    for (const locint& dep : dep_set) {
      accumulate_deriv(ginfo, dep_deriv[dep]);
      if (info.x != NULL_LOC) {
        reverse_live[info.x].insert(dep);
      }
      if (info.y != NULL_LOC) {
        reverse_live[info.y].insert(dep);
      }
    }
  }
}

template <typename Base>
void BaseReverseGenerator<Base>::accumulate_deriv(
    const GeneratorInfo<locint, Base>& ginfo,
    GenericDeriv<locint, Base>& global_deriv) {
  // here we use the generated code
  GenericDeriv<locint, Base> slice_deriv(order);
  global_deriv.get_and_erase(ginfo.r, slice_deriv);
  typename GenericDeriv<locint, Base>::enumerator s_enum =
      slice_deriv.get_enumerator();
  ReverseADMultiSet<locint> s_set;
  Base sw;
  while (s_enum.has_next()) {
    s_enum.get_curr_pair(s_set, sw);
    s_enum.move_to_next();
    int t_size = s_set.count(ginfo.r);
    for (int i = 0; i < t_size; i++) {s_set.remove(ginfo.r);}
    // This is sooo ugly...
    if (ginfo.y != NULL_LOC) {
      switch (order - s_set.size()) {
        case 1:
          switch (s_set.count(ginfo.x)) {
            case 0:
              switch (s_set.count(ginfo.y)) {
                case 0:
                  generator_binary_1_1_0_0(s_set, sw, ginfo, global_deriv);
                  break;
                case 1:
                  generator_binary_1_1_0_1(s_set, sw, ginfo, global_deriv);
                  break;
                case 2:
                  generator_binary_1_1_0_2(s_set, sw, ginfo, global_deriv);
                  break;
              }
              break;
            case 1:
              switch (s_set.count(ginfo.y)) {
                case 0:
                  generator_binary_1_1_1_0(s_set, sw, ginfo, global_deriv);
                  break;
                case 1:
                  generator_binary_1_1_1_1(s_set, sw, ginfo, global_deriv);
                  break;
              }
              break;
            case 2:
              switch (s_set.count(ginfo.y)) {
                case 0:
                  generator_binary_1_1_2_0(s_set, sw, ginfo, global_deriv);
                  break;
              }
          }
          break;
        case 2:
          switch (t_size) {
            case 1:
              switch (s_set.count(ginfo.x)) {
                case 0:
                  switch (s_set.count(ginfo.y)) {
                    case 0:
                      generator_binary_2_1_0_0(s_set, sw, ginfo, global_deriv);
                      break;
                    case 1:
                      generator_binary_2_1_0_1(s_set, sw, ginfo, global_deriv);
                      break;
                  }
                  break;
                case 1:
                  switch (s_set.count(ginfo.y)) {
                    case 0:
                      generator_binary_2_1_1_0(s_set, sw, ginfo, global_deriv);
                      break;
                  }
                  break;
              }
              break;
            case 2:
              switch (s_set.count(ginfo.x)) {
                case 0:
                  switch (s_set.count(ginfo.y)) {
                    case 0:
                      generator_binary_2_2_0_0(s_set, sw, ginfo, global_deriv);
                      break;
                    case 1:
                      generator_binary_2_2_0_1(s_set, sw, ginfo, global_deriv);
                      break;
                  }
                  break;
                case 1:
                  switch (s_set.count(ginfo.y)) {
                    case 0:
                      generator_binary_2_2_1_0(s_set, sw, ginfo, global_deriv);
                      break;
                  }
                  break;
              }
              break;
          }
          break;
        case 3:
          switch (t_size) {
            case 1:
              switch (s_set.count(ginfo.x)) {
                case 0:
                  switch (s_set.count(ginfo.y)) {
                    case 0:
                      generator_binary_3_1_0_0(s_set, sw, ginfo, global_deriv);
                      break;
                  }
                  break;
              }
              break;
            case 2:
              switch (s_set.count(ginfo.x)) {
                case 0:
                  switch (s_set.count(ginfo.y)) {
                    case 0:
                      generator_binary_3_2_0_0(s_set, sw, ginfo, global_deriv);
                      break;
                  }
                  break;
              }
              break;
            case 3:
              switch (s_set.count(ginfo.x)) {
                case 0:
                  switch (s_set.count(ginfo.y)) {
                    case 0:
                      generator_binary_3_3_0_0(s_set, sw, ginfo, global_deriv);
                      break;
                  }
                  break;
              }
              break;
          }
          break;
      }
    } else if (ginfo.x != NULL_LOC) {
      switch (order - s_set.size()) {    // d-z
        case 1:
          switch (s_set.count(ginfo.x)) {
            case 0:
              generator_unary_1_1_0(s_set, sw, ginfo, global_deriv);
              break;
            case 1:
              generator_unary_1_1_1(s_set, sw, ginfo, global_deriv);
              break;
            case 2:
              generator_unary_1_1_2(s_set, sw, ginfo, global_deriv);
              break;
          }
          break;
        case 2:
          switch (t_size) { // r
            case 1:
              switch (s_set.count(ginfo.x)) { // x_count
                case 0:
                  generator_unary_2_1_0(s_set, sw, ginfo, global_deriv);
                  break;
                case 1:
                  generator_unary_2_1_1(s_set, sw, ginfo, global_deriv);
                  break;
              }
              break;
            case 2:
              switch (s_set.count(ginfo.x)) { // x_count
                case 0:
                  generator_unary_2_2_0(s_set, sw, ginfo, global_deriv);
                  break;
                case 1:
                  generator_unary_2_2_1(s_set, sw, ginfo, global_deriv);
                  break;
              }
              break;
          }
          break;
        case 3:
          switch (t_size) { // r
            case 1:
              switch (s_set.count(ginfo.x)) { // x_count
                case 0:
                  generator_unary_3_1_0(s_set, sw, ginfo, global_deriv);
                  break;
              }
              break;
            case 2:
              switch (s_set.count(ginfo.x)) { // x_count
                case 0:
                  generator_unary_3_2_0(s_set, sw, ginfo, global_deriv);
                  break;
              }
              break;
            case 3:
              switch (s_set.count(ginfo.x)) { // x_count
                case 0:
                  generator_unary_3_3_0(s_set, sw, ginfo, global_deriv);
                  break;
              }
              break;
          }
          break;
      }
    }
  }
}

template <typename Base>
void BaseReverseGenerator<Base>::fill_in_ginfo(
    const DerivativeInfo<locint, Base>& dinfo,
    GeneratorInfo<locint, Base>& ginfo) {
  // direct copy for order <= 3
  // locs
  ginfo.r = dinfo.r;
  ginfo.x = dinfo.x;
  ginfo.y = dinfo.y;
  // 1st
  ginfo.dx = dinfo.dx;
  ginfo.dy = dinfo.dy;
  // 2nd
  ginfo.pxx = dinfo.pxx;
  ginfo.pxy = dinfo.pxy;
  ginfo.pyy = dinfo.pyy;
  // 3rd
  ginfo.pxxx = dinfo.pxxx;
  ginfo.pxxy = dinfo.pxxy;
  ginfo.pxyy = dinfo.pxyy;
  ginfo.pyyy = dinfo.pyyy;
}

} // namespace ReverseAD

template class ReverseAD::BaseReverseGenerator<double>;
//template class ReverseAD::BaseReverseGenerator<ReverseAD::SingleForward>;
