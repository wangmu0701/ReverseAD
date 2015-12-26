#ifndef REVERSEAD_BASE_REVERSE_GENERIC_H_
#define REVERSEAD_BASE_REVERSE_GENERIC_H_

#include <map>

#include "reversead/common/reversead_type.hpp"
#include "reversead/algorithm/base_reverse_mode.hpp"
#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/reversead_multiset.hpp"
#include "reversead/algorithm/single_derivative.hpp"
#include "reversead/algorithm/generic_deriv.hpp"

#define REVERSEAD_MAX_GENERIC_ORDER 10

namespace ReverseAD {

static const double kFactorial[REVERSEAD_MAX_GENERIC_ORDER + 1] =
    {1.0, 1.0, 2.0, 6.0, 24.0, 120.0, 720.0, 
     5040.0, 40320.0, 362880.0, 3628800.0};

template <typename Base>
class BaseReverseGeneric : public BaseReverseMode<Base> {
 public:
  typedef SingleDerivative<Base> SingleDeriv;

  using BaseReverseMode<Base>::trace;
  using BaseReverseMode<Base>::reverse_live;
  using BaseReverseMode<Base>::indep_index_map;
  using BaseReverseMode<Base>::dep_index_map;

  BaseReverseGeneric(AbstractTrace<Base>* trace, int order) :
      BaseReverseMode<Base>(trace) {
    if (order > REVERSEAD_MAX_GENERIC_ORDER) {
      std::cout << "Sorry, max order should be less than " 
                << REVERSEAD_MAX_GENERIC_ORDER << "." << std::endl;
      return;
    }
    if (order <= 0) {
      std::cout << "Order("<<order<<") should be positive." << std::endl;
    }
    this->order = order;
  }

  void compute(int ind_num, int dep_num) {

    BaseReverseMode<Base>::compute(ind_num, dep_num);
    for(const auto& kv : dep_deriv) {
      locint dep = kv.first;
      std::cout << "Dep : " << dep << std::endl;
      kv.second.debug();
      std::cout << std::endl;
    }
  }

  int retrieve_generic_values(int t_order, int** ssize, locint**** tind, Base*** values) {
    int dep_size = dep_deriv.size();
    (*ssize) = new int[dep_size];
    (*tind) = new locint**[dep_size];
    (*values) = new Base*[dep_size];
    for (auto& kv : dep_deriv) {
      locint dep = dep_index_map[kv.first] - 1;
      typename GenericDeriv<locint, Base>::enumerator g_enum =
        kv.second.get_enumerator();
      ReverseADMultiSet<locint> s_set;
      Base sw;
      int size = 0;
      while(g_enum.has_next()) {
        g_enum.get_curr_pair(s_set, sw);
        g_enum.move_to_next();
        if (s_set.size() == t_order) {
          size++;
        }
      }
      (*ssize)[dep] = size;
      (*tind)[dep] = new locint*[size];
      (*values)[dep] = new Base[size];
      g_enum = kv.second.get_enumerator();
      int l = 0;
      while (g_enum.has_next()) {
        g_enum.get_curr_pair(s_set, sw);
        g_enum.move_to_next();
        if (s_set.size() == t_order) {
          (*values)[dep][l] = sw;
          (*tind)[dep][l] = s_set.to_array();
          for (int i=0; i<t_order; i++) {
            (*tind)[dep][l][i] = indep_index_map[(*tind)[dep][l][i]];
          }
          l++;
        }
      } 
    }
    return dep_size;
  }

  // here we're NOT touching SingleDeriv, will change interface later
  void init_dep_deriv(SingleDeriv& deriv, locint dep) {
    GenericDeriv<locint, Base> d_deriv(order);
    ReverseADMultiSet<locint> d_set;
    d_set.insert(dep);
    d_deriv.increase(d_set, 1.0);
    dep_deriv.insert(std::pair<locint, GenericDeriv<locint, Base>>(dep, d_deriv));
    d_deriv.debug();
  }

  void accumulate_deriv(const DerivativeInfo<locint, Base>& info,
                        const GenericDeriv<locint, Base>& local_deriv,
                        GenericDeriv<locint, Base>& global_deriv) {
    GenericDeriv<locint, Base> slice_deriv(order);
    global_deriv.find_and_erase(info.r, slice_deriv);
    //
    typename GenericDeriv<locint, Base>::enumerator s_enum =
      slice_deriv.get_enumerator();
    ReverseADMultiSet<locint> s_set;
    Base sw;
    while (s_enum.has_next()) {
      s_enum.get_curr_pair(s_set, sw);
      s_enum.move_to_next();
      int t_size = s_set.count(info.r);
      for(int i=0;i<t_size;i++) {s_set.remove(info.r);}
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
        for (int i=0; i<= order; i++) {
          ReverseADMultiSet<locint> ss_set(s_set);
          for(int j=0; j<=order; j++) {
            if (ssw[i*(order+1)+j] != 0.0) {
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
        for (int i=1; i<=order; i++) {
          s_set.insert(info.x);
          if (ssw[i] != 0.0) {
            global_deriv.increase(s_set, ssw[i]);
          }
        }
      }
    }
  }

  void process_sac(const DerivativeInfo<locint, Base>& info) {
    if (info.r != NULL_LOC) {
      GenericDeriv<locint, Base> local_deriv(order);
      fill_in_local_deriv(info, local_deriv);
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

 private:
  int order;
  std::map<locint, GenericDeriv<locint, Base> > dep_deriv;

  // some private temps used when accumulating, avoid pointers on stack
  int dx[100];
  int dy[100];
  Base ssw[100];
  int max_level;
  int max_order;
  int cx;
  int cy;
  locint temp_x;
  locint temp_y;
  
  void clear_private_temps() {
    temp_x = NULL_LOC;
    temp_y = NULL_LOC;
    max_level = 0;
    max_order = 0;
    for (int i=0; i<order+1; i++) {
      dx[i] = 0;dy[i] = 0;
      for(int j=0; j<order+1; j++) {
        ssw[i*(order+1)+j] = 0;
      }
    }
  }
  void generate_binary_tuples(int curr_level, int curr_order, Base pw,
    typename GenericDeriv<locint, Base>::enumerator curr_enum) {
    if (curr_level > max_level) {
      double coeff = binary_sym_coeff();
      ssw[cx*(order+1)+cy] += coeff * pw;
      return;
    }
    typename GenericDeriv<locint, Base>::enumerator s_enum = curr_enum;
    ReverseADMultiSet<locint> dc;
    Base w;
    while(s_enum.has_next()) {
      s_enum.get_curr_pair(dc, w);
      std::cout << "curr_pair : ";
      dc.debug();
      std::cout << " w = " << w << std::endl;
      if (w != 0.0) {
        int size = dc.size();
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
  void generate_unary_tuples(int curr_level, int curr_order, Base pw,
    typename GenericDeriv<locint, Base>::enumerator curr_enum) {
    if (curr_level > max_level) {
      double coeff = unary_sym_coeff();
      ssw[curr_order] += coeff * pw;
      return;
    }
    typename GenericDeriv<locint, Base>::enumerator s_enum = curr_enum;
    ReverseADMultiSet<locint> dc;
    Base w;
    while (s_enum.has_next()) {
      s_enum.get_curr_pair(dc, w);
      if (w != 0.0) {
        int size = dc.size();
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
  double binary_sym_coeff() {
    int n = 0;
    int m = 0;
    for(int i=0; i<=max_level; i++) {n+=dx[i]; m+=dy[i];}
    cx = n - dx[0];
    cy = m - dy[0];
    double ret = kFactorial[n];
    for(int i=0; i<=max_level; i++) {
      ret = ret / kFactorial[dx[i]];
    }
    ret = ret * kFactorial[m];
    for(int i=0; i<=max_level; i++) {
      ret = ret / kFactorial[dy[i]];
    }
    int count = 1;
    int l = 2;
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

  double unary_sym_coeff() {
    int n = 0;
    for (int i=0; i<=max_level; i++){n+=dx[i];}
    double ret = kFactorial[n];
    for (int i=0; i<=max_level; i++) {
      ret = ret / kFactorial[dx[i]];
    }
    int count = 1;
    int l = 2;
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

  void check_and_increase(const ReverseADMultiSet<locint>& term,
                        const Base& value,
                        GenericDeriv<locint, Base>& local_deriv) {
    if (value != 0.0) {
      local_deriv.increase(term, value);
    }
  }
  // fill in a generic derivative table for SACs
  void fill_in_local_deriv(const DerivativeInfo<locint, Base>& info,
                           GenericDeriv<locint, Base>& local_deriv) {

    if (order <= 3) { // simple fill
      ReverseADMultiSet<locint> term;
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
    ReverseADMultiSet<locint> term;
    switch(info.opcode) {
      case assign_a:
      case eq_plus_d:
      case plus_d_a:
      case minus_d_a:
      case eq_mult_d:
      case mult_d_a:
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
          for(int i=2;i<=order; i++) {
            t = t * (1-i) / info.vy;
            term.insert(info.y);
            check_and_increase(term, t, local_deriv);
          }
          term.clear();
          t = info.vx / info.vy;
          for(int i=1;i<=order; i++) {
            t = t * (-i) / info.vy;
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
          for (int i=2; i<=order; i++) {
            t *= (-i) / info.vx;
            check_and_increase(term, t, local_deriv);
          }
        }
        break;
      default:
        logger.warning << "Unrecongized opcode : " << (int)info.opcode
                    << std::endl;
    }
    std::cout << "filling in for :" << std::endl;
    info.debug();
    local_deriv.debug(); 
  } 
};

} // namespace ReverseAD

#endif
