#ifndef __thodd_stream_list_hpp__
#  define __thodd_stream_list_hpp__

#  include <thodd/experimental/basic_collection.hpp>

namespace thodd::collection {

  template <typename type_t>
  struct list_constraint {
    inline auto operator () (type_t const &) const -> bool {
      return true ;
    }
  } ;

  /// Une list est un container pointant sur son premier et 
  /// son dernier élément. La dernier élément doit être atteignable 
  /// par navigation à partir du premier élément
  template <typename type_t>
  using list = basic_collection<type_t, list_constraint<type_t>> ; 
}

#endif