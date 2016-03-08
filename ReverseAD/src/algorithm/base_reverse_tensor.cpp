#include "reversead/algorithm/base_reverse_tensor.hpp"

namespace ReverseAD {

#include "generator/tensor.ipp"

//#include "generator/generator.ipp"
int kOrderShift = 1000000;
int kRCountShift =  10000;
int kXCountShift =    100;
int kYCountShift =      1;

template <typename Base>
BaseReverseTensor<Base>::BaseReverseTensor(
    const std::shared_ptr<TrivialTrace<Base>>& trace,
    int order) : BaseReverseMode<Base>(trace) {
  if (order > REVERSEAD_MAX_TENSOR_ORDER) {
    std::cout << "Sorry, max order for tensor should be less than "
              << REVERSEAD_MAX_TENSOR_ORDER << "." << std::endl;
  }
  if (order <= 0) {
    std::cout << "Order(" << order << ") should be positive." << std::endl;
  }
  this->order = order;
  //std::cout << "in reverse tensor. order = " << order << std::endl;
  special_derivative_coeff();
}

template <typename Base>
void BaseReverseTensor<Base>::special_derivative_coeff() {
  for (int i=0;i<=REVERSEAD_MAX_TENSOR_ORDER; i++) {
    for (int j=0;j<=REVERSEAD_MAX_TENSOR_ORDER; j++) {
      for (int k=0;k<=REVERSEAD_MAX_TENSOR_ORDER; k++) {
        c_atan[i][j][k] = c_asin[i][j][k] =  0.0;
      }
    }
  }
  c_atan[1][1][0] = c_asin[1][1][0] = 1.0;
  for (int i=2; i <= REVERSEAD_MAX_TENSOR_ORDER; i++) {
    for (int j = REVERSEAD_MAX_TENSOR_ORDER; j >= 2; j--) {
      for (int k=0; k < REVERSEAD_MAX_TENSOR_ORDER; k++) {
        c_atan[i][j][k] = c_atan[i-1][j][k+1] * (k+1);
        c_asin[i][j][k] = c_asin[i-1][j][k+1] * (k+1);
      }
      for (int k=1; k <= REVERSEAD_MAX_TENSOR_ORDER; k++) {
        c_atan[i][j][k] += c_atan[i-1][j-1][k-1] * 2 * (1-j);
        c_asin[i][j][k] += c_asin[i-1][j-1][k-1] * -2 * (1.5 - j);
      }
    }
  }
}

template <typename Base>
void BaseReverseTensor<Base>::clear() {
  dep_deriv.clear();
  BaseReverseMode<Base>::clear();
}

template <typename Base>
void BaseReverseTensor<Base>::init_dep_deriv(locint dep, int dep_count) {
  TensorDeriv<locint, Base> d_deriv(order);
  TensorIndex<locint> t_index;
  t_index.insert(dep);
  d_deriv.increase(t_index, 1.0);
  dep_deriv.insert(std::pair<locint, TensorDeriv<locint, Base>>(dep, d_deriv));
  reverse_live[dep].insert(dep);
}

template <typename Base>
std::shared_ptr<DerivativeTensor<int, Base>>
    BaseReverseTensor<Base>::get_tensor() const {
  int* ttind = new int[order];
  int dep_size = dep_deriv.size();
  int ind_size = indep_index_map.size();
  std::shared_ptr<DerivativeTensor<int, Base>> ret =
      std::make_shared<DerivativeTensor<int, Base>>(dep_size, ind_size, order);
  BaseReverseMode<Base>::transcript_dep_value(ret);
  for (auto& kv : dep_deriv) {
    locint dep = dep_index_map.find(kv.first)->second - 1;
    for (int d = 1; d <= order; d++) {
      size = kv.second.tensor[d]->size();
      ret->init_single_tensor(dep, d, size);
      assign_pointers(d);
      kv.second.tensor[d]->to_array(tind, values, 0, 0);
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < d; j++) {ttind[j] = tind[i][j];}
        ret->put_value(dep, d, i, ttind, values[i]);
      }
      temp_memory.return_memory();
    }
  }
  delete[] ttind;
  return ret;
}

template <typename Base>
void BaseReverseTensor<Base>::process_sac(
    const DerivativeInfo<locint, Base>& info) {
  ginfo.clear();
  if (info.r != NULL_LOC) {
    fill_in_ginfo(info);
    std::set<locint> dep_set = std::move(reverse_live[info.r]);
    reverse_live.erase(info.r);
    for (const locint& dep : dep_set) {
      //std::cout << "dep = " << dep << std::endl;
      //dep_deriv[dep].debug();
      accumulate_deriv(dep_deriv[dep]);
      if (info.x != NULL_LOC) {
        reverse_live[info.x].insert(dep);
      }
      if (info.y != NULL_LOC) {
        reverse_live[info.y].insert(dep);
      }
      //dep_deriv[dep].debug();
    }
  }
}

template <typename Base>
void BaseReverseTensor<Base>::assign_pointers(int s_order) const {
  temp = (char*)temp_memory.get_memory(
      size * (sizeof(locint*) + sizeof(locint)*s_order + sizeof(double)));
  tind = (locint**)temp;
  temp += sizeof(locint*) * size;
  for (int i = 0; i < size; i++) {
    tind[i] = (locint*)temp;
    temp += sizeof(locint) * s_order;
  }
  values = (double*) temp;
}

template <typename Base>
void BaseReverseTensor<Base>::unary_generator(
    int s_order, TensorDeriv<locint, Base>& global_deriv) {
  //std::cout << "s_order = " << s_order << std::endl;
  //std::cout << "size = " << size << std::endl;
  TensorIndex<locint> t_index;
  for (int i = 0; i < size; i++) {
    t_index.clear();
    r_count = 1; x_count = 0; y_count = 0;
    for (int j = 0; j < s_order; j++) {
      if (tind[i][j] == ginfo.r) {
        r_count++;
      } else {
        t_index.insert(tind[i][j]);
        if (tind[i][j] == ginfo.x) {x_count++;}
      }
    }
    if (order > t_index.size()) {
      case_code = (order - t_index.size()) * kOrderShift
                + r_count * kRCountShift
                + x_count * kXCountShift;
      //std::cout << "unary case_code = " << case_code << std::endl;
      generator_unary(case_code, t_index, values[i], ginfo, global_deriv);
    }
  }
}

template <typename Base>
void BaseReverseTensor<Base>::binary_generator(
    int s_order, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> t_index;
  for (int i = 0; i < size; i++) {
    t_index.clear();
    r_count = 1; x_count = 0; y_count = 0;
    for (int j = 0; j < s_order; j++) {
      if (tind[i][j] == ginfo.r) {
        r_count++;
      } else {
        t_index.insert(tind[i][j]);
        if (tind[i][j] == ginfo.x) {x_count++;}
        if (tind[i][j] == ginfo.y) {y_count++;}
      }
    }
    if (order > t_index.size()) {
      case_code = (order - t_index.size()) * kOrderShift
                + r_count * kRCountShift
                + x_count * kXCountShift
                + y_count * kYCountShift;
      generator_binary(case_code, t_index, values[i], ginfo, global_deriv);
    }
  }
}

template <typename Base>
void BaseReverseTensor<Base>::accumulate_deriv(
    TensorDeriv<locint, Base>& global_deriv) {
  // here we use the generated code
  TensorDeriv<locint, Base> slice_deriv(order);
  global_deriv.get_and_erase(ginfo.r, slice_deriv);
  TensorIndex<locint> t_index;
  for (int d = 0; d < order; d++) {
    size = slice_deriv.tensor[d]->size();
    assign_pointers(d);
    slice_deriv.tensor[d]->to_array(tind, values, 0, 0);
    if (ginfo.y != NULL_LOC) {
      binary_generator(d, global_deriv);
    } else if (ginfo.x != NULL_LOC) {
      unary_generator(d, global_deriv);
    }
    temp_memory.return_memory();
  }
}

template <typename Base>
void BaseReverseTensor<Base>::fill_in_ginfo(
    const DerivativeInfo<locint, Base>& dinfo) {
  using std::sqrt;
  using std::log;

  switch (order) {
    case 4:
      switch (dinfo.opcode) {
        case eq_div_a:
        case div_a_a:
          ginfo.pxyyy = -3.0 * dinfo.pxyy / dinfo.vy;
          ginfo.pyyyy = -4.0 * dinfo.pyyy / dinfo.vy;
          break;
        case div_d_a:
          ginfo.pxxxx = -4.0 * dinfo.pxxx / dinfo.vx;
          break;
        case sin_a:
        case cos_a:
          ginfo.pxxxx = -dinfo.pxx;
          break;
        case asin_a:
        case acos_a:
          {
            Base c = 1.0 / (1.0 - dinfo.vx * dinfo.vx);
            Base sw = 0;
            Base w = 0;
            Base s = sqrt(1.0 - dinfo.vx * dinfo.vx);
            for (int i = 0; i <= 4; i++) {
              w = 1.0;
              for (int j = 0; j <=i; j++) {
                sw += c_asin[4][i][j] * w * s;
                w = w * dinfo.vx;
              }
              s = s * c;
            }
            if (dinfo.opcode == asin_a) {
              ginfo.pxxxx = sw;
            } else {
              ginfo.pxxxx = -sw;
            }
          }
          break;
        case atan_a:
          {
            Base c = 1.0 / (1.0 + dinfo.vx * dinfo.vx);
            Base sw = 0;
            Base w = 0;
            Base s = 1.0;
            for (int i = 0; i <= 4; i++) {
              w = 1.0;
              for (int j = 0; j <=i; j++) {
                sw += c_atan[4][i][j] * w * s;
                w = w * dinfo.vx;
              }
              s = s * c;
            }
            ginfo.pxxxx = sw;
          }
          break;
        case exp_a:
          ginfo.pxxxx = dinfo.pxxx;
          break;
        case log_a:
          ginfo.pxxxx = -3.0 * dinfo.pxxx / dinfo.vx;
          break;
        case sqrt_a:
          ginfo.pxxxx = -2.5 * dinfo.pxxx / dinfo.vx;
          break;
        case pow_d_a:
          ginfo.pxxxx = log(dinfo.coval) * dinfo.pxxx;
          break;
        case pow_a_d:
          ginfo.pxxxx = (dinfo.coval - 3.0) * dinfo.pxxx / dinfo.vx;
          break;
      }
    default:
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
}

} // namespace ReverseAD

template class ReverseAD::BaseReverseTensor<double>;
//template class ReverseAD::BaseReverseTensor<ReverseAD::SingleForward>;
