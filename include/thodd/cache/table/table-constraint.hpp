#ifndef __thodd_cache_table_table_constraint_hpp__
#  define __thodd_cache_table_table_constraint_hpp__

#  include <thodd/cache/table/table.hpp>
#  include <regex>

#  include <iostream> 

namespace thodd::cache {
  constexpr auto valid () {
    return [] (auto const & data) {
      return true ;
    } ;
  }
  
  constexpr auto nullable (bool nullble) {
    return [=] (auto const & data) {
      return (nullble) || (!nullble && !data.empty()) ;
    } ;
  }

  auto format (auto const & fmt_reg) {
    return [fmt_reg] (auto const & data) {
      return std::regex_match(data, std::regex(fmt_reg)) ; 
    } ;
  }
}

#endif