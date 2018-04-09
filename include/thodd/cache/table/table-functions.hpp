#ifndef __thodd_table_table_functions_hpp__
#  define __thodd_table_table_functions_hpp__

#  include <thodd/cache/table/table.hpp>
#  include <thodd/cache/table/table-constraint.hpp>

#  include <algorithm>
#  include <iostream>
#  include <typeinfo>

namespace thodd::cache {
  
  constexpr unsigned one_inserted = 1 ;
  constexpr unsigned no_inserted = 0 ;

  inline column define_column (column_type type, 
                               auto && name, 
                               constraint_f const & constraints) {
    return {type, constraints, name} ;
  }

  inline column simple (auto && name, auto && constraint) {
    return define_column(column_type::simple, name, constraint) ;
  }

  inline column pk (auto && name, auto && constraint) {
    return define_column(column_type::primary_key, name, 
      [&constraint] (std::string const & data) {
        return nullable(false)(data) && constraint(data) ;
      }) ;
  }

  inline column fk (auto && name) {
    return define_column(column_type::foreign_key, name, valid()) ;
  }

  inline table define_table (auto && name, auto && ... columns) {
    return {name, {columns...}} ;
  }

  inline int insert_without_check (table & t, auto const & record) {
    t.data.push_back(record) ;
    t.pk_index[t.data.back()[0]] = &t.data.back() ;
    return one_inserted ;
  }

  inline auto join (auto const & l, auto const & r) {
    using join_item_t = decltype(std::make_tuple(&*std::begin(l), &*std::begin(r))) ;

    std::vector<join_item_t> joined ;
    
    auto lb = std::begin(l) ;
    auto rb = std::begin(r) ;

    while (lb != std::end(l) && rb != std::end(r)) {
      joined.push_back(std::make_tuple(&*lb, &*rb)) ;
      lb = std::next(lb) ;
      rb = std::next(rb) ;
    }

    return joined ;
  }

  inline int insert_one(table & t, auto const & record) {
    auto && joined = join(t.header, record) ;

    return t.header.size() == record.size() && 
      std::all_of(joined.begin(), joined.end(), [] (auto const & joined_item){
         return get_constraint(*std::get<0>(joined_item))(*std::get<1>(joined_item)) ;
      }) ? 
        insert_without_check(t, record) : 
        no_inserted ;
  }

  inline int insert (table & t, auto const & first_record, auto const & ... records) {    
    if constexpr (sizeof...(records) > 0) 
      return insert_one(t, first_record) + insert(t, records...) ;
    else 
      return insert_one(t, first_record);
  } 






}

#endif 