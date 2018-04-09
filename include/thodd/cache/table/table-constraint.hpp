#ifndef __thodd_cache_table_table_constraint_hpp__
#  define __thodd_cache_table_table_constraint_hpp__

#  include <thodd/cache/table/table.hpp>

namespace thodd::cache {
  constexpr auto valid() {
    return [] (auto const & data) {
      return true ;
    } ;
  }
  constexpr auto nullable(bool nullble) {
    return [=] (auto const & data) {
      return (nullble) || (!nullble && !data.empty()) ;
    } ;
  }
}

#endif