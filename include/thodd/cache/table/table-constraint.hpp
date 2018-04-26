#ifndef __thodd_cache_table_table_constraint_hpp__
#  define __thodd_cache_table_table_constraint_hpp__

#  include <thodd/cache/table/table.hpp>
#  include <regex>

#  include <iostream> 

namespace thodd::cache {
  /** 
   * @brief  
   * @retval 
   */
  constexpr auto valid () {
    return [] (auto const & data) {
      return true ;
    } ;
  }
  
  /** 
   * @brief  
   * @param  nullble: 
   * @retval 
   */
  constexpr auto nullable (bool nullble) {
    return [=] (auto const & data) {
      return (nullble) || (!nullble && !data.empty()) ;
    } ;
  }

  /** 
    * @brief  
    * @param  fmt_reg: 
    * @retval 
    */
  constexpr auto format (auto const & fmt_reg) {
    return [fmt_reg] (auto const & data) {
      return std::regex_match(data, std::regex(fmt_reg)) ; 
    } ;
  }
}

#endif