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
  std::cout << "in reverse tensor. order = " << order << std::endl;
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
  int dep_size = dep_deriv.size();
  int ind_size = indep_index_map.size();
  std::shared_ptr<DerivativeTensor<int, Base>> ret =
      std::make_shared<DerivativeTensor<int, Base>>(dep_size, ind_size, order);
  for (const auto& kv : dep_deriv) {
    std::cout << "Dep : " << kv.first << std::endl;
    kv.second.tensor1.dump();
    kv.second.tensor2.dump();
    kv.second.tensor3.dump();
  }
  return ret;
}

template <typename Base>
void BaseReverseTensor<Base>::process_sac(
    const DerivativeInfo<locint, Base>& info) {
  if (info.r != NULL_LOC) {
    fill_in_ginfo(info);
    std::set<locint> dep_set = std::move(reverse_live[info.r]);
    reverse_live.erase(info.r);
    for (const locint& dep : dep_set) {
      accumulate_deriv(dep_deriv[dep]);
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
void BaseReverseTensor<Base>::assign_pointers(int s_order) {
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
  TensorIndex<locint> t_index;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < s_order; j++) {
      t_index.clear();
      r_count = 1; x_count = 0; y_count = 0;
      if (tind[i][j] == ginfo.r) {
        r_count++;
      } else {
        t_index.insert(tind[i][j]);
        if (tind[i][j] == ginfo.x) {x_count++;}
      }
      if (order > t_index.size()) {
        case_code = (order - t_index.size()) * kOrderShift
                  + r_count * kRCountShift
                  + x_count * kXCountShift;
        generator_unary(case_code, t_index, values[i], ginfo, global_deriv);
      }
    }
  }
}

template <typename Base>
void BaseReverseTensor<Base>::binary_generator(
    int s_order, TensorDeriv<locint, Base>& global_deriv) {
  TensorIndex<locint> t_index;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < s_order; j++) {
      t_index.clear();
      r_count = 1; x_count = 0; y_count = 0;
      if (tind[i][j] == ginfo.r) {
        r_count++;
      } else {
        t_index.insert(tind[i][j]);
        if (tind[i][j] == ginfo.x) {x_count++;}
        if (tind[i][j] == ginfo.y) {y_count++;}
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
}

template <typename Base>
void BaseReverseTensor<Base>::accumulate_deriv(
    TensorDeriv<locint, Base>& global_deriv) {
  // here we use the generated code
  TensorDeriv<locint, Base> slice_deriv(order);
  global_deriv.get_and_erase(ginfo.r, slice_deriv);
  TensorIndex<locint> t_index;
  // 0th order
  w = slice_deriv.tensor0;
  t_index.clear();
  case_code = order * kOrderShift + 1 * kRCountShift; // x_count=y_count=0
  if (ginfo.y != NULL_LOC) {
    generator_binary(case_code, t_index, w, ginfo, global_deriv);
  } else if (ginfo.x != NULL_LOC) {
    generator_unary(case_code, t_index, w, ginfo, global_deriv);
  }
  // 1st order;
  size = slice_deriv.tensor1.size();
  assign_pointers(1);
  slice_deriv.tensor1.to_array(tind, values, 0, 0);
  if (ginfo.y != NULL_LOC) {
    binary_generator(1, global_deriv);
  } else if (ginfo.x != NULL_LOC) {
    unary_generator(1, global_deriv);
  }
  temp_memory.return_memory();
  // 2st order;
  size = slice_deriv.tensor2.size();
  assign_pointers(2);
  slice_deriv.tensor2.to_array(tind, values, 0, 0);
  if (ginfo.y != NULL_LOC) {
    binary_generator(2, global_deriv);
  } else if (ginfo.x != NULL_LOC) {
    unary_generator(2, global_deriv);
  }
  temp_memory.return_memory();
}

template <typename Base>
void BaseReverseTensor<Base>::fill_in_ginfo(
    const DerivativeInfo<locint, Base>& dinfo) {
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

template class ReverseAD::BaseReverseTensor<double>;
//template class ReverseAD::BaseReverseTensor<ReverseAD::SingleForward>;
