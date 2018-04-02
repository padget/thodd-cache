#ifndef __thodd_table_table_functions_hpp__
#  define __thodd_table_table_functions_hpp__

#  include <thodd/cache/table/table.hpp>

namespace thodd::cache {
  
  constexpr unsigned one_inserted = 1 ;
  constexpr unsigned no_inserted = 0 ;

  inline column define_column (column_type type, auto && name) {
    return {type, name} ;
  }

  inline column simple (auto && name) {
    return define_column(column_type::simple, name) ;
  }

  inline column pk (auto && name) {
    return define_column(column_type::primary_key, name) ;
  }

  inline column fk (auto && name) {
    return define_column(column_type::foreign_key, name) ;
  }

  inline table define_table (auto && name, auto && ... columns) {
    return {name, {columns...}} ;
  }

  inline int insert_without_check (table & t, auto const & record) {
    t.data.push_back(record) ;
    t.pk_index[t.data.back()[0]] = &t.data.back() ;
    return one_inserted ;
  }

  inline int insert (table & t, auto const & first_record, auto const & ... records) {
    unsigned const nb_inserted = 
      first_record.size() == t.header.size() ? 
        insert_without_check(t, first_record) : 
        no_inserted ;
    
    if constexpr (sizeof...(records) > 0) 
      return insert(t, records...) + nb_inserted;
    else 
      return nb_inserted ;
  } 






}

#endif 