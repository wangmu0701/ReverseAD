#ifndef REVERSEAD_GENERIC_DERIV_H_
#define REVERSEAD_GENERIC_DERIV_H_

#include <vector>
#include <map>

#include "reversead/algorithm/algorithm_common.hpp"
#include "reversead/algorithm/generic_multiset.hpp"

namespace ReverseAD {

template <typename LocType, typename Base>
class GenericDeriv {
 public:
  GenericDeriv(): _order(0) {};
  GenericDeriv(int order): _order(order) {_data.resize(_order);};
  void clear() {
    _data.clear();
    _data.resize(_order);
  }
  void increase(const GenericMultiset<LocType>& set, Base v) {
    if (IsZero(v)) {
      return;
    }
    int order = set.size();
    if (check_size_fail(order)) {
      return;
    }
    _data[order-1][set] += v;
  }

  int get_size(int order) const {
    return _data[order].size();
  }

  Base get(const GenericMultiset<LocType>& set) {
    int order = set.size();
    if (check_size_fail(order)) {
      return;
    }
    if (_data[order - 1].find(set) == _data[order-1].end()) {
      return 0.0;
    }
    return _data[order - 1][set];
  }
  void debug() const {
    typename std::vector<std::map<GenericMultiset<LocType>, Base> >::const_iterator v_iter;
    typename std::map<GenericMultiset<LocType>, Base >::const_iterator m_iter;
    v_iter = _data.begin();
    while(v_iter != _data.end()) {
      m_iter = (*v_iter).begin();
      while(m_iter != (*v_iter).end()) {
        std::cout << "T ";
        m_iter->first.debug();
        std::cout << " = " << m_iter->second << std::endl;
        ++m_iter;
      }
      ++v_iter;
    }
  }

  void get_and_erase(LocType target, GenericDeriv& gd) {
    gd.clear();
    typename std::vector<std::map<GenericMultiset<LocType>, Base> >::iterator v_iter;
    typename std::map<GenericMultiset<LocType>, Base>::iterator m_iter;
    v_iter = _data.begin();
    while(v_iter != _data.end()) {
      m_iter = v_iter->begin();
      while(m_iter != v_iter->end()) {
        if (m_iter->first.find(target)) {
          gd.increase(m_iter->first, m_iter->second);
          m_iter = (*v_iter).erase(m_iter);
        } else {
          ++m_iter;
        }
      }
      ++v_iter;
    }
  }

  class enumerator {
   public:
    void get_curr_pair(GenericMultiset<LocType>& multi_set, Base& w) const {
      multi_set = m_iter->first;
      w = m_iter->second;
    }

    bool has_next() const {
      return (v_iter != _p_data->end());
    }

    typename GenericDeriv<LocType, Base>::enumerator& operator = (
      const GenericDeriv<LocType, Base>::enumerator& rhs) {
      this->_p_data = rhs._p_data;
      this->v_iter = rhs.v_iter;
      this->m_iter = rhs.m_iter;
      return (*this);
    }

    bool move_to_next() const {
      ++m_iter;
      while(v_iter != _p_data->end()) {
        if (m_iter != v_iter->end()) {
          return true;
        } else {
          ++v_iter;
          if (v_iter != _p_data->end()) {
            m_iter = (*v_iter).begin();
          }
        }
      }
      return false;
    }

   private:

    enumerator(const typename std::vector<std::map<GenericMultiset<LocType>, Base> > * const p_data) {
      this->_p_data = p_data;
      this->v_iter = _p_data->begin();
      while (v_iter != _p_data->end()) {
        m_iter = v_iter->begin();
        if (m_iter != v_iter->end()) {
          break;
        }
        ++v_iter;
      }
    }

    const std::vector<std::map<GenericMultiset<LocType>, Base> > * _p_data;
    mutable typename std::vector<std::map<GenericMultiset<LocType>, Base> >::const_iterator v_iter;
    mutable typename std::map<GenericMultiset<LocType>, Base>::const_iterator m_iter;

   friend class GenericDeriv<LocType, Base>;
  };
 
 GenericDeriv<LocType, Base>::enumerator get_enumerator() const {
   GenericDeriv<LocType, Base>::enumerator ret(&_data);
   return ret; 
 }

 private:
  int _order; // LocTypehe highest order
  std::vector<std::map<GenericMultiset<LocType>, Base> > _data;
  
  bool check_size_fail(int order) {
    if (order < 1 || order > _order) {
      std::cout << "Max order = " << _order
                << ", Input size = " << order << std::endl;
      return true;
    }
    return false;
  }
};

} // namespace ReverseAD

#endif // REVERSEAD_GENERIC_DERIV_H_
