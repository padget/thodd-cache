#ifndef __thodd_iterator_list_hpp__
#  define __thodd_iterator_list_hpp__

#include <optional>
#include <memory>

namespace std {
  template <typename type_t>
  using ptr = std::shared_ptr<type_t> ;

  template <typename type_t>
  inline auto make_ptr(auto && ... args) {
    return std::make_shared<type_t>(static_cast<decltype(args)&&>(args)...) ;
  }
}

namespace container {
  
  template <typename type_t>
  struct node {
    type_t data ;
    std::ptr<node> next ;
  } ;

  template <typename type_t>
  struct list {
    using iterator = std::ptr<node<type_t>> ;
    iterator first ;
    iterator last ; 
    size_t size{0u} ; 
  } ;

  template <typename type_t>
  typename list<type_t>::iterator begin (list<type_t> const & l) {
    return l.first ;
  }

  template <typename type_t>
  typename list<type_t>::iterator end (list<type_t> const &) {
    return {} ;
  }

  size_t size(list<auto> const & l) {
    return l.size ;
  }

  template <typename type_t>
  auto next (std::ptr<node<type_t>> it) {
    return it ? it->next : it ;
  }

  template <typename type_t>
  type_t const & get (std::ptr<node<type_t>> it) {
    return it->data ;
  }

  template <typename type_t>
  list<type_t> const push (list<type_t> const & l, type_t const & item) {
    auto n     = std::make_ptr<node<type_t>>(node<type_t>{item, nullptr}) ;
    auto last  = l.last ;
    
    if (!l.first) {
      return {n, n, l.size + 1} ;
    } else {
      last->next = n ;
      return {l.first, n, l.size + 1} ;
    }
  }
}

#endif