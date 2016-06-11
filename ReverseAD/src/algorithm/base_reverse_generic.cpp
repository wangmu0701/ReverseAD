#include <cmath>
#include <map>
#include <memory>

#include "reversead/common/reversead_type.hpp"
#include "reversead/common/reversead_core.hpp"
#include "reversead/common/opcodes.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/base_reverse_generic.hpp"
#include "reversead/forwardtype/single_forward.hpp"
#include "reversead/util/error_info.hpp"

namespace ReverseAD {

static const double kFactorial[REVERSEAD_MAX_GENERIC_ORDER + 1] =
{1.0, 1.0, 2.0, 6.0, 24.0, 120.0, 720.0,
  5040.0, 40320.0, 362880.0, 3628800.0};

template <typename Base>
BaseReverseGeneric<Base>::BaseReverseGeneric(
    const std::shared_ptr<TrivialTrace<Base>>& trace, size_t order)
        : BaseReverseMode<Base>(trace) {
  if (order > REVERSEAD_MAX_GENERIC_ORDER) {
    std::cout << "Sorry, max order should be less than "
    << REVERSEAD_MAX_GENERIC_ORDER << "." << std::endl;
    return;
  }
  if (order <= 0) {
    std::cout << "Order("<<order<<") should be positive." << std::endl;
  }
  this->order = order;
  special_derivative_coeff();
}

template <typename Base>
void BaseReverseGeneric<Base>::accumulate_deriv(
    const DerivativeInfo<locint, Base>& info,
    const GenericDeriv<locint, Base>& local_deriv,
    GenericDeriv<locint, Base>& global_deriv) {
  GenericDeriv<locint, Base> slice_deriv(order);
  global_deriv.get_and_erase(info.r, slice_deriv);
  //
  typename GenericDeriv<locint, Base>::enumerator s_enum =
      slice_deriv.get_enumerator();
  GenericMultiset<locint> s_set;
  Base sw;
  while (s_enum.has_next()) {
    s_enum.get_curr_pair(s_set, sw);
    s_enum.move_to_next();
    size_t t_size = s_set.count(info.r);
    for(size_t i = 0;i < t_size; i++) {s_set.remove(info.r);}
    clear_private_temps();
    max_level = t_size;
    max_order = order - s_set.size();
    if (info.y != NULL_LOC) {
      temp_x = info.x;
      temp_y = info.y;
      dx[0] = s_set.count(info.x);
      dy[0] = s_set.count(info.y);
      generate_binary_tuples(1, // curr_level
                             0, // curr_order
                             sw,
                             local_deriv.get_enumerator()); // initial enum)
      for (size_t i = 0; i <= order; i++) {
        GenericMultiset<locint> ss_set(s_set);
        for(size_t j=0; j<=order; j++) {
          if (!IsZero(ssw[i*(order+1)+j])) {
            global_deriv.increase(ss_set, ssw[i*(order+1)+j]);
          }
          ss_set.insert(info.y);
        }
        s_set.insert(info.x);
      }
    } else if (info.x != NULL_LOC){
      dx[0] = s_set.count(info.x);
      generate_unary_tuples(1, // curr_level
                            0, // curr_order
                            sw,
                            local_deriv.get_enumerator()); // initial enum
      for (size_t i = 1; i <= order; i++) {
        s_set.insert(info.x);
        if (!IsZero(ssw[i])) {
          global_deriv.increase(s_set, ssw[i]);
        }
      }
    }
  }
}

template <typename Base>
std::shared_ptr<DerivativeTensor<size_t, Base>>
    BaseReverseGeneric<Base>::get_tensor() const {
  size_t dep_size = dep_deriv.size();
  size_t ind_size = indep_index_map.size();
  std::shared_ptr<DerivativeTensor<size_t, Base>> ret =
      std::make_shared<DerivativeTensor<size_t, Base>>(dep_size, ind_size, order);
  BaseReverseMode<Base>::transcript_dep_value(ret);
  size_t* size = new size_t[order];
  size_t* curr_l = new size_t[order];
  locint* t = new locint[order];
  size_t* x = new size_t[order];
  for (auto& kv : dep_deriv) {
    size_t dep = dep_index_map.find(kv.first)->second;
    for (size_t i = 0; i < order; i++) {
      size[i] = kv.second.get_size(i);
      ret->init_single_tensor(dep, i+1, size[i]);
      curr_l[i] = 0;
    }
    GenericMultiset<locint> s_set;
    Base sw;
    typename GenericDeriv<locint, Base>::enumerator g_enum =
    kv.second.get_enumerator();
    while (g_enum.has_next()) {
      g_enum.get_curr_pair(s_set, sw);
      g_enum.move_to_next();
      size_t t_order = s_set.size();
      s_set.to_array(t);
      // The iterator of multiset puts small number fist
      // reverse the order so it gives lower half
      for (size_t i = 0; i < t_order; i++) {
        x[t_order - 1 - i] = indep_index_map.find(t[i])->second;
      }
      ret->put_value(dep, t_order, curr_l[t_order-1], x, sw);
      curr_l[t_order - 1]++;
    }
  }
  delete[] size;
  delete[] curr_l;
  delete[] t;
  delete[] x;

  return std::move(ret);
}

template <typename Base>
void BaseReverseGeneric<Base>::clear() {
  clear_private_temps();
  dep_deriv.clear();
  BaseReverseMode<Base>::clear();
}

template <typename Base>
void BaseReverseGeneric<Base>::init_dep_deriv(locint dep) {
  GenericDeriv<locint, Base> d_deriv(order);
  GenericMultiset<locint> d_set;
  d_set.insert(dep);
  d_deriv.increase(d_set, 1.0);
  dep_deriv.insert(std::pair<locint, GenericDeriv<locint, Base>>(dep, d_deriv));
  //d_deriv.debug();
  reverse_live[dep].insert(dep);
}

template <typename Base>
void BaseReverseGeneric<Base>::process_sac(
    const DerivativeInfo<locint, Base>& info) {
  if (info.r != NULL_LOC) {
    GenericDeriv<locint, Base> local_deriv(order);
    fill_in_local_deriv(info, local_deriv);
    //std::cout << "filling in : " << std::endl;
    //info.debug();
    //local_deriv.debug();
    std::set<locint> dep_set = std::move(reverse_live[info.r]);
    reverse_live.erase(info.r);
    //info.debug();
    for (const locint& dep : dep_set) {
      //std::cout << "dep : " << dep << std::endl;
      //dep_deriv[dep].debug();
      accumulate_deriv(info, local_deriv, dep_deriv[dep]);
      //std::cout << "after " << std::endl;
      //dep_deriv[dep].debug();
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
void BaseReverseGeneric<Base>::special_derivative_coeff() {
  for (size_t i = 0;i <= REVERSEAD_MAX_GENERIC_ORDER; i++) {
    for (size_t j = 0;j <= REVERSEAD_MAX_GENERIC_ORDER; j++) {
      for (size_t k = 0;k <= REVERSEAD_MAX_GENERIC_ORDER; k++) {
        c_atan[i][j][k] = c_asin[i][j][k] =  0.0;
      }
    }
  }
  c_atan[1][1][0] = c_asin[1][1][0] = 1.0;
  for (size_t i = 2; i <= REVERSEAD_MAX_GENERIC_ORDER; i++) {
    for (size_t j = REVERSEAD_MAX_GENERIC_ORDER; j >= 2; j--) {
      for (size_t k = 0; k < REVERSEAD_MAX_GENERIC_ORDER; k++) {
        c_atan[i][j][k] = c_atan[i-1][j][k+1] * (k+1.0);
        c_asin[i][j][k] = c_asin[i-1][j][k+1] * (k+1.0);
      }
      for (size_t k = 1; k <= REVERSEAD_MAX_GENERIC_ORDER; k++) {
        c_atan[i][j][k] += c_atan[i-1][j-1][k-1] * 2 * (1.0 - j);
        c_asin[i][j][k] += c_asin[i-1][j-1][k-1] * -2 * (1.5 - j);
      }
    }
  }
}

template <typename Base>
void BaseReverseGeneric<Base>::clear_private_temps() {
  temp_x = NULL_LOC;
  temp_y = NULL_LOC;
  max_level = 0;
  max_order = 0;
  cx = 0;
  cy = 0;
  for (size_t i = 0; i < order + 1; i++) {
    dx[i] = 0;dy[i] = 0;
    for(size_t j = 0; j < order+1; j++) {
      ssw[i*(order+1)+j] = 0;
    }
  }
}

template <typename Base>
void BaseReverseGeneric<Base>::generate_binary_tuples(
    size_t curr_level, size_t curr_order, Base pw,
    typename GenericDeriv<locint, Base>::enumerator curr_enum) {
  if (curr_level > max_level) {
    double coeff = binary_sym_coeff();
    ssw[cx*(order+1)+cy] += coeff * pw;
    return;
  }
  typename GenericDeriv<locint, Base>::enumerator s_enum = curr_enum;
  GenericMultiset<locint> dc;
  Base w;
  while(s_enum.has_next()) {
    s_enum.get_curr_pair(dc, w);
    //std::cout << "curr_pair : ";
    //dc.debug();
    //std::cout << " w = " << w << std::endl;
    if (!IsZero(w)) {
      size_t size = dc.size();
      if (size * (max_level - curr_level + 1) + curr_order <= max_order) {
        dx[curr_level] = dc.count(temp_x);
        dy[curr_level] = size - dx[curr_level];
        generate_binary_tuples(curr_level + 1,
                               curr_order + size,
                               pw * w,
                               s_enum);
      }
    }
    s_enum.move_to_next();
  }
}

template <typename Base>
void BaseReverseGeneric<Base>::generate_unary_tuples(
    size_t curr_level, size_t curr_order, Base pw,
    typename GenericDeriv<locint, Base>::enumerator curr_enum) {
  if (curr_level > max_level) {
    double coeff = unary_sym_coeff();
    ssw[curr_order] += coeff * pw;
    return;
  }
  typename GenericDeriv<locint, Base>::enumerator s_enum = curr_enum;
  GenericMultiset<locint> dc;
  Base w;
  while (s_enum.has_next()) {
    s_enum.get_curr_pair(dc, w);
    if (!IsZero(w)) {
      size_t size = dc.size();
      if (size * (max_level - curr_level + 1) + curr_order <= max_order) {
        dx[curr_level] = size;
        generate_unary_tuples(curr_level + 1,
                              curr_order + size,
                              pw * w,
                              s_enum);
      }
    }
    s_enum.move_to_next();
  }
}

template <typename Base>
double BaseReverseGeneric<Base>::binary_sym_coeff() {
  size_t n = 0;
  size_t m = 0;
  for(size_t i=0; i<=max_level; i++) {n+=dx[i]; m+=dy[i];}
  cx = n - dx[0];
  cy = m - dy[0];
  double ret = kFactorial[n];
  for(size_t i=0; i<=max_level; i++) {
    ret = ret / kFactorial[dx[i]];
  }
  ret = ret * kFactorial[m];
  for(size_t i=0; i<=max_level; i++) {
    ret = ret / kFactorial[dy[i]];
  }
  size_t count = 1;
  size_t l = 2;
  while (l <= max_level) {
    if (dx[l] == dx[l-1] && dy[l] == dy[l-1]) {
      count++;
    } else {
      ret = ret / kFactorial[count];
      count = 1;
    }
    l++;
  }
  ret = ret / kFactorial[count];
  return ret;
}

template <typename Base>
double BaseReverseGeneric<Base>::unary_sym_coeff() {
  size_t n = 0;
  for (size_t i=0; i<=max_level; i++){n+=dx[i];}
  double ret = kFactorial[n];
  for (size_t i=0; i<=max_level; i++) {
    ret = ret / kFactorial[dx[i]];
  }
  size_t count = 1;
  size_t l = 2;
  while (l<=max_level) {
    if (dx[l] == dx[l-1]) {
      count++;
    } else {
      ret = ret / kFactorial[count];
      count = 1;
    }
    l++;
  }
  ret = ret / kFactorial[count];
  return ret;
}

template <typename Base>
void BaseReverseGeneric<Base>::check_and_increase(
    const GenericMultiset<locint>& term,
    const Base& value,
    GenericDeriv<locint, Base>& local_deriv) {
  if (!IsZero(value)) {
    local_deriv.increase(term, value);
  }
}

// fill in a generic derivative table for SACs
template <typename Base>
void BaseReverseGeneric<Base>::fill_in_local_deriv(
    const DerivativeInfo<locint, Base>& info,
    GenericDeriv<locint, Base>& local_deriv) {
  using std::sin;
  using std::cos;
  using std::sqrt;
  using std::pow;
  using std::log;
  using std::exp;
  
  if (order <= 3) { // simple fill
    GenericMultiset<locint> term;
    // dx
    term.insert(info.x);
    check_and_increase(term, info.dx, local_deriv);
    term.clear();
    // dy
    term.insert(info.y);
    check_and_increase(term, info.dy, local_deriv);
    term.clear();
    if (order >= 2) {
      //pxx
      term.insert(info.x); term.insert(info.x);
      check_and_increase(term, info.pxx, local_deriv);
      term.clear();
      //pxy
      term.insert(info.x); term.insert(info.y);
      check_and_increase(term, info.pxy, local_deriv);
      term.clear();
      //pyy
      term.insert(info.y); term.insert(info.y);
      check_and_increase(term, info.pyy, local_deriv);
      term.clear();
      if (order >= 3){
        // pxxx
        term.insert(info.x); term.insert(info.x); term.insert(info.x);
        check_and_increase(term, info.pxxx, local_deriv);
        term.clear();
        // pxxy
        term.insert(info.x); term.insert(info.x); term.insert(info.y);
        check_and_increase(term, info.pxxy, local_deriv);
        term.clear();
        // pxyy
        term.insert(info.x); term.insert(info.y); term.insert(info.y);
        check_and_increase(term, info.pxyy, local_deriv);
        term.clear();
        // pyyy
        term.insert(info.y); term.insert(info.y); term.insert(info.y);
        check_and_increase(term, info.pyyy, local_deriv);
        term.clear();
      }
    }
    return;
  }
  GenericMultiset<locint> term;
  switch(info.opcode) {
    case assign_ind:
    case assign_dep:
    case assign_d:
    case assign_param:
      break;
    case assign_a:
    case eq_plus_d:
    case plus_d_a:
    case minus_d_a:
    case eq_mult_d:
    case mult_d_a:
    case fabs_a:
      term.insert(info.x);
      check_and_increase(term, info.dx, local_deriv);
      break;
    case eq_plus_a:
    case plus_a_a:
    case eq_minus_a:
    case minus_a_a:
      term.insert(info.x);
      check_and_increase(term, info.dx, local_deriv);
      if (info.y != NULL_LOC) {
        term.clear();
        term.insert(info.y);
        check_and_increase(term, info.dy, local_deriv);
      }
      break;
    case eq_mult_a:
    case mult_a_a:
      term.insert(info.x);
      check_and_increase(term, info.dx, local_deriv);
      if (info.y != NULL_LOC) {
        term.clear();
        term.insert(info.y);
        check_and_increase(term, info.dy, local_deriv);
        term.insert(info.x);
        check_and_increase(term, info.pxy, local_deriv);
      } else {
        term.insert(info.x);
        check_and_increase(term, info.pxx, local_deriv);
      }
      break;
    case eq_div_a:
    case div_a_a:
      term.insert(info.x);
      check_and_increase(term, info.dx, local_deriv);
      term.clear();
      if (info.y != NULL_LOC) {
        Base t = 1.0 / info.vy;
        term.insert(info.x);
        for(size_t i = 2;i <= order; i++) {
          t = t * (1.0 - i) / info.vy;
          term.insert(info.y);
          check_and_increase(term, t, local_deriv);
        }
        term.clear();
        t = info.vx / info.vy;
        for(size_t i = 1;i <= order; i++) {
          t = t * (0.0 - i) / info.vy;
          term.insert(info.y);
          check_and_increase(term, t, local_deriv);
        }
        term.clear();
      }
      break;
    case div_d_a:
      term.insert(info.x);
      check_and_increase(term, info.dx, local_deriv);
    {
      Base t = info.dx;
      for (size_t i = 2; i <= order; i++) {
        t *= (0.0 - i) / info.vx;
        term.insert(info.x);
        check_and_increase(term, t, local_deriv);
      }
    }
      break;
    case sin_a:
    {
      Base dsin[4] = {sin(info.vx), cos(info.vx),
        -sin(info.vx), -cos(info.vx)};
      for(size_t i=1; i<=order; i++) {
        term.insert(info.x);
        check_and_increase(term, dsin[i % 4], local_deriv);
      }
    }
      break;
    case cos_a:
    {
      Base dcos[4] = {cos(info.vx), -sin(info.vx),
        -cos(info.vx), sin(info.vx)};
      for(size_t i = 1; i <= order; i++) {
        term.insert(info.x);
        check_and_increase(term, dcos[i % 4], local_deriv);
      }
    }
      break;
    case asin_a:
    case acos_a:
    {
      Base c = 1.0 / (1.0 - info.vx * info.vx);
      Base sw = 0;
      Base w = 0;
      Base s = 0;
      for (size_t i = 1; i <= order; i++) {
        term.insert(info.x);
        sw = 0;
        s = sqrt(1.0 - info.vx * info.vx);
        for (size_t j = 0; j <= i; j++) {
          w = 1;
          for (size_t k = 0; k <= j; k++) {
            sw += c_asin[i][j][k] * w * s;
            w = w * info.vx;
          }
          s = s * c;
        }
        if (info.opcode == asin_a) {
          check_and_increase(term, sw, local_deriv);
        } else {
          check_and_increase(term, -sw, local_deriv);
        }
      }
    }
      break;
    case atan_a:
    {
      Base c = 1.0 / (1.0 + info.vx * info.vx);
      Base sw = 0;
      Base w = 0;
      Base s = 0;
      for (size_t i = 1; i <= order; i++) {
        term.insert(info.x);
        sw = 0;
        s = 1;
        for (size_t j = 0; j <= i; j++) {
          w = 1;
          for (size_t k = 0; k <= j; k++) {
            sw += c_atan[i][j][k] * w * s;
            w = w * info.vx;
          }
          s = s * c;
        }
        check_and_increase(term, sw, local_deriv);
      }
    }
      break;
    case exp_a:
      for (size_t i=1; i<=order; i++) {
        term.insert(info.x);
        check_and_increase(term, info.dx, local_deriv);
      }
      break;
    case log_a:
    {
      term.insert(info.x);
      check_and_increase(term, info.dx, local_deriv);
      Base t = info.dx;
      for(size_t i = 2; i <= order; i++) {
        t = t * (1.0 - i) / info.vx;
        term.insert(info.x);
        check_and_increase(term, t, local_deriv);
      }
    }
      break;
    case sqrt_a:
    {
      Base t = sqrt(info.vx);
      for (size_t i = 1; i <= order; i++) {
        t = t * (1.5 - i) / info.vx;
        term.insert(info.x);
        check_and_increase(term, t, local_deriv);
      }
    }
      break;
    case pow_d_a:
    {
      Base t = info.dx;
      for (size_t i = 1; i <= order; i++) {
        term.insert(info.x);
        check_and_increase(term, t, local_deriv);
        t = t * log(info.coval);
      }
    }
      info.coval = 0.0;
      break;
    case pow_a_d:
    {
      Base t = pow(info.vx, info.coval);
      for (size_t i = 1; i <= order; i++) {
        t = t * (info.coval + 1.0 - i) / info.vx;
        term.insert(info.x);
        check_and_increase(term, t, local_deriv);
      }
    }
      info.coval = 0.0;
      break;
    case pow_a_a:
      break;
    default:
      // We should not see this as it passed tha check in BaseReverseMode
      warning_UnrecognizedOpcode((int)info.opcode);
  }
}

} // namespace ReverseAD

template class ReverseAD::BaseReverseGeneric<double>;
template class ReverseAD::BaseReverseGeneric<ReverseAD::SingleForward>;
