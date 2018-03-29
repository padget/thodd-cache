#ifndef __thodd_cache_table_hpp__
#  define __thodd_cache_table_hpp__

#  include <list>
#  include <vector>
#  include <map>
#  include <string>

namespace thodd::cache {
  enum class column_type {primary_key, simple, foreign_key} ;

  using column = std::tuple<column_type, std::string> ;
  using record = std::vector<std::string> ;

  struct table  {
    std::string name ;
    std::vector<column> header ;
    std::list<record> data ;
    std::map<std::string, record*> pk_index ; 
  } ;

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

  inline int insert (table& t, auto && ... data) {
    auto && rec = record{data...} ;
    
    if (rec.size() == t.header.size() && t.pk_index.count(rec[0]) == 0) {
      t.data.push_back(record{data...}) ; // insertion dans la base 
      t.pk_index[t.data.back()[0]] = &t.data.back() ; // indexation
      return 1 ;
    }

    return 0 ;
  } 

  
}

#endif 