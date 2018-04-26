#ifndef __thodd_table_table_functions_hpp__
#  define __thodd_table_table_functions_hpp__

#  include <thodd/cache/table/table.hpp>
#  include <thodd/cache/table/table-constraint.hpp>
#  include <thodd/iterator/iterator.hpp>
#  include <thodd/iterator/fluent.hpp>

#  include <algorithm>
#  include <iostream>
#  include <typeinfo>

namespace thodd::cache {
  
  constexpr unsigned one_inserted = 1 ;
  constexpr unsigned no_inserted = 0 ;

  inline column define_column (column_type type, 
                               auto && name, 
                               constraint_f const & constraints, 
                               transformer_f const & transformer) {
    return {type, constraints, transformer, name} ;
  }

  inline column simple (auto && name, auto && constraint, auto && transformer) {
    return define_column(column_type::simple, name, constraint, transformer) ;
  }

  inline column pk (auto && name, auto && constraint, auto && transformer) {
    return define_column(column_type::primary_key, name, 
      [&constraint] (std::string const & data) {
        return nullable(false)(data) && constraint(data) ;
      }, transformer) ;
  }

  inline column fk (auto && name) {
    return define_column(column_type::foreign_key, name, valid(), [] (auto const & data) {return data ;}) ;
  }

  inline table define_table (auto && name, auto && ... columns) {
    return {name, {columns...}} ;
  }



  inline int insert_without_check (table & t, auto const & record) {
    t.data.push_back(record) ;
    t.pk_index[t.data.back()[0]] = &t.data.back() ;
    return one_inserted ;
  }

  namespace collectors {
    auto to_record () {
      return make_collector(
        meta::type<thodd::cache::record>{}, 
        [] (auto & collection, auto const & value) {
          collection.push_back(value) ;
        }) ;
    }
  }


  inline int insert_one(table & t, auto const & record) {
    auto && transformed_record = 
      thodd::as_stream(t.header)
        .join(make_range(record))
        .map_n([](auto const & head, auto const & value) {
          return get_transformer(head)(value) ;})
        .collect(collectors::to_record()) ; 
    
    auto && all_checked = 
      thodd::as_stream(t.header)
        .join(make_range(transformed_record))
        .reduce_n(
          [] (auto const & head, auto const & value, auto const & acc) {
            return acc && get_constraint(head)(value) ;
          }, true) ;

    return t.header.size() == transformed_record.size() && all_checked ? 
      insert_without_check(t, transformed_record) : no_inserted ;
  }


  inline int insert (table & t, auto const & first_record, auto const & ... records) {    
    if constexpr (sizeof...(records) > 0) 
      return insert_one(t, first_record) + insert(t, records...) ;
    else 
      return insert_one(t, first_record);
  } 
}

#endif 